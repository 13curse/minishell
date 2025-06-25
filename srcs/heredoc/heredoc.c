/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:08:11 by van-nguy          #+#    #+#             */
/*   Updated: 2025/06/10 18:33:07 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		heredoc(t_minishell *shell, char *limiter);
int		create_and_fill_heredoc(t_minishell *shell, char *limiter, char *n);
int		finalize_heredoc_redir(t_minishell *shell, char *name);
int		find_unique_filename(char *name);
void	expand_quotes_inner_while(t_minishell *sh,
			t_exp_quotes *v, char **cmd);

int	heredoc_part_1(t_minishell *shell, char *name)
{
	if (find_unique_filename(name))
		return (1);
	while (shell->heredocs->i < MAX_HEREDOCS
		&& shell->heredocs->fds[shell->heredocs->i] != -1)
		shell->heredocs->i++;
	if (shell->heredocs->i == MAX_HEREDOCS)
	{
		write(2, "Too many heredocs created\n", 26);
		return (1);
	}
	shell->heredocs->fds[shell->heredocs->i]
		= open(name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (shell->heredocs->fds[shell->heredocs->i] == -1)
	{
		perror("");
		return (1);
	}
	shell->heredocs->names[shell->heredocs->i]
		= malloc(sizeof(char) * ft_strlen(name) + 1);
	if (shell->heredocs->names[shell->heredocs->i] == NULL)
		return (err_malloc(1));
	ft_strlcpy(shell->heredocs->names[shell->heredocs->i],
		name, ft_strlen(name) + 1);
	return (0);
}

void	expand_quotes_heredoc(t_minishell *shell, char **limiter_dup)
{
	t_exp_quotes	v;

	v.ign_i = -1;
	if (limiter_dup[0])
	{
		v.ign_i++;
		v.l = 0;
		v.rem = 0;
		expand_quotes_inner_while(shell, &v, limiter_dup);
	}
}

int	heredoc_part1_2(t_minishell *shell, char **limiter_dup,
		char *name, char *limiter)
{
	shell->heredocs->expand_var = 1;
	*limiter_dup = ft_strdup(limiter);
	if (!*limiter_dup)
		return (err_malloc(1));
	expand_quotes_heredoc(shell, limiter_dup);
	if (ft_strchr(limiter, '"') || ft_strchr(limiter, '\''))
		shell->heredocs->expand_var = 0;
	if (heredoc_part_1(shell, name))
	{
		free(*limiter_dup);
		return (1);
	}
	return (0);
}

int	heredoc_final_part(t_minishell *shell)
{
	if (shell->last_redir_in[shell->cmd_id - 1] > 0)
		close(shell->last_redir_in[shell->cmd_id - 1]);
	else if (shell->last_redir_in[shell->cmd_id - 1] < -1)
		return (0);
	shell->last_redir_in[shell->cmd_id - 1]
		= shell->heredocs->fds[shell->heredocs->i];
	return (0);
}

int	heredoc(t_minishell *shell, char *limiter)
{
	char	name[23];
	int		ret;
	char	*limiter_dup[2];

	limiter_dup[1] = NULL;
	if (heredoc_part1_2(shell, limiter_dup, name, limiter))
		return (1);
	ret = write_to_heredoc(shell, *limiter_dup);
	free(*limiter_dup);
	if (ret == 666)
		return (666);
	if (ret)
		return (1);
	close(shell->heredocs->fds[shell->heredocs->i]);
	shell->heredocs->fds[shell->heredocs->i] = open(name, O_RDONLY);
	if (shell->heredocs->fds[shell->heredocs->i] == -1)
	{
		perror("");
		return (1);
	}
	return (heredoc_final_part(shell));
}
