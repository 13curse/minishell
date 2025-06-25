/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:35:57 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/08 12:35:57 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirection_heredoc(t_minishell *shell, char ***cmd);
int	redirection_append(t_minishell *shell, char ***cmd);
int	redirection_out(t_minishell *shell, char ***cmd);
int	redirection_in(t_minishell *shell, char ***cmd);

int	redirection_heredoc(t_minishell *shell, char ***cmd)
{
	char	*limiter;
	int		ret;

	(*cmd)++;
	limiter = **cmd;
	ret = heredoc(shell, limiter);
	if (ret == 666)
		return (666);
	if (ret)
		return (1);
	return (0);
	(void)shell;
}

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

int	redirection_in(t_minishell *shell, char ***cmd)
{
	int		fd;

	(*cmd)++;
	if (shell->last_redir_in[shell->cmd_id - 1] < -1)
		return (0);
	if (expand_filename(shell, *cmd))
		return (1);
	fd = open(**cmd, O_RDONLY);
	if (fd == -1)
	{
		shell->last_redir_in[shell->cmd_id - 1] = -2;
		return (2);
	}
	if (shell->last_redir_in[shell->cmd_id - 1] > 0)
		close(shell->last_redir_in[shell->cmd_id - 1]);
	shell->last_redir_in[shell->cmd_id - 1] = fd;
	return (0);
	(void)shell;
}
