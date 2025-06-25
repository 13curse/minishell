/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:34:41 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/08 12:34:41 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_redirections(t_minishell *shell);
void	move_to_end(char **cmd, int i);
int		reset_stdio(t_minishell *shell);
int		connect_heredoc(t_minishell *shell);

void	remove_redirections(t_minishell *shell)
{
	int		i;
	char	**cmd;

	cmd = shell->cmds[shell->cmd_id - 1];
	i = -1;
	while (cmd[++i])
	{
		if (is_op(cmd[i], shell->op))
		{
			move_to_end(cmd, i);
			i = -1;
		}
	}
}

void	move_to_end(char **cmd, int i)
{
	int		j;

	free(cmd[i]);
	free(cmd[i + 1]);
	cmd[i] = NULL;
	cmd[i + 1] = NULL;
	j = -1;
	while (cmd[i + ++j + 2])
	{
		cmd[i + j] = cmd[i + j + 2];
		cmd[i + j + 2] = NULL;
	}
}

int	reset_stdio(t_minishell *shell)
{
	if (dup2(shell->stdin, STDIN_FILENO) == -1
		|| dup2(shell->stdout, STDOUT_FILENO) == -1)
	{
		perror("");
		return (1);
	}
	return (0);
}

int	connect_heredoc(t_minishell *shell)
{
	int	i;

	i = shell->heredocs->i;
	close(shell->heredocs->fds[i]);
	shell->heredocs->fds[i] = open(shell->heredocs->names[i], O_RDONLY);
	if (shell->heredocs->fds[i] == -1)
	{
		perror("");
		return (1);
	}
	if (shell->heredocs->names[i] == NULL)
		return (0);
	if (dup2(shell->heredocs->fds[i], 0))
		return (1);
	return (0);
}
