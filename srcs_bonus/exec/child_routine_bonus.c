/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:53:14 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:26:57 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	connect_pipes(t_minishell *shell, int cmdc);
void	abort_child_routine(t_minishell *shell);

void	child_routine(t_minishell *shell, char **cmd, int cmdc, int cmds_lst_i)
{
	setup_signal_handlers(2);
	connect_pipes(shell, cmdc);
	if (redirections(shell, cmd, cmds_lst_i))
		abort_child_routine(shell);
	remove_redirections(shell, cmd);
	expand_vars(shell, cmd);
	expand_quotes(shell, cmd);
	if (*cmd == NULL)
	{
		free_shell(shell);
		exit (0);
	}
	exec_cmd(shell, cmd);
}

// links STDIN/STDOUT to pipes, closes pipes
void	connect_pipes(t_minishell *shell, int cmdc)
{
	int	i;

	if (cmdc <= 1)
		return ;
	if (shell->cmd_id == 1)
		dup2(shell->pipes[0][1], STDOUT_FILENO);
	else if (shell->cmd_id == cmdc)
		dup2(shell->pipes[cmdc - 2][0], STDIN_FILENO);
	else
	{
		dup2(shell->pipes[shell->cmd_id - 2][0], STDIN_FILENO);
		dup2(shell->pipes[shell->cmd_id - 1][1], STDOUT_FILENO);
	}
	i = -1;
	while (++i < cmdc - 1)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
	}
}

void	abort_child_routine(t_minishell *shell)
{
	free_shell(shell);
	exit (shell->status);
}
