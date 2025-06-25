/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections3_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:18:45 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:23:23 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	expand_filename(t_minishell *shell, char **filename);
int	expand_filename_var(t_minishell *shell,
		char *filename, char *new, int *uninterpreted);
int	var_expanded_len(t_minishell *shell, char *cmd);
int	expand_filename_quote(char *filename, int *uninterpreted);

int	redirection_append(t_minishell *shell, char ***cmd)
{
	int		to_redirect;
	char	*file;
	int		fd;

	to_redirect = ft_atoi(**cmd);
	if (***cmd == '>')
		to_redirect = 1;
	(*cmd)++;
	file = **cmd;
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (1);
	if (dup2(fd, to_redirect) == -1)
		return (1);
	return (0);
	(void)shell;
}

int	redirection_out(t_minishell *shell, char ***cmd)
{
	int		to_redirect;
	int		fd;

	to_redirect = ft_atoi(**cmd);
	if (***cmd == '>')
		to_redirect = 1;
	(*cmd)++;
	if (expand_filename(shell, *cmd))
		return (1);
	fd = open(**cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	if (dup2(fd, to_redirect) == -1)
		return (1);
	return (0);
	(void)shell;
}

int	redirection_in(t_minishell *shell, char **cmd, int i, int *tkn_i)
{
	int		fd;

	(*tkn_i)++;
	cmd++;
	if (shell->last_redir_in[shell->cmd_id - 1][i] < -1)
		return (0);
	if (expand_filename(shell, cmd))
		return (1);
	fd = open(*cmd, O_RDONLY);
	if (fd == -1)
	{
		shell->last_redir_in[shell->cmd_id - 1][i] = -3;
		return (2);
	}
	if (shell->last_redir_in[shell->cmd_id - 1][i] > 0)
		close(shell->last_redir_in[shell->cmd_id - 1][i]);
	shell->last_redir_in[shell->cmd_id - 1][i] = fd;
	return (0);
}

int	expand_filename(t_minishell *shell, char **filename)
{
	int		uninterpreted[MAX_UNINTERPRETED + 1];
	int		expanded_len;
	char	*new;

	expanded_len = var_expanded_len(shell, *filename);
	if (expanded_len == -1)
		return (1);
	if ((expanded_len == -2 || expanded_len == 0)
		&& !ft_strchr(*filename, '"') && !ft_strchr(*filename, '\''))
		return (0);
	if (expanded_len < 0)
		expanded_len = ft_strlen(*filename);
	new = malloc(sizeof(char) * (expanded_len + 1));
	if (new == NULL)
		return (err_malloc(1));
	ft_memset(uninterpreted, -1, sizeof(uninterpreted));
	expand_filename_var(shell, *filename, new, uninterpreted);
	expand_filename_quote(new, uninterpreted);
	free(*filename);
	*filename = new;
	return (0);
}
