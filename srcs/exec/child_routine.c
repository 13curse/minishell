/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:53:14 by van               #+#    #+#             */
/*   Updated: 2025/06/11 13:48:25 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	connect_pipes(t_minishell *shell);
void	abort_child_routine(t_minishell *shell);

int	prepare_child_routine(t_minishell *shell, char ***cmd2)
{
	int	count;
	int	i;

	setup_signal_handlers(2);
	connect_pipes(shell);
	if (redirections(shell))
		return (abort_child_routine(shell), 1);
	remove_redirections(shell);
	count = count_tokens_after_expand(shell);
	if (alloc_uninterpreted(shell, count))
		kill_shell(shell);
	*cmd2 = malloc(sizeof(char *) * (count + 1));
	if (*cmd2 == NULL)
	{
		err_malloc(1);
		kill_shell(shell);
	}
	i = -1;
	while (++i < count + 1)
		(*cmd2)[i] = NULL;
	expand_vars(shell, *cmd2);
	free (shell->cmds[shell->cmd_id - 1]);
	shell->cmds[shell->cmd_id - 1] = *cmd2;
	expand_quotes(shell);
	return (0);
}

void	child_routine(t_minishell *shell)
{
	char	**cmd2;

	shell->in_fork = 1;
	if (prepare_child_routine(shell, &cmd2))
		return ;
	if (cmd2 == NULL || *cmd2 == NULL)
	{
		free_shell(shell);
		exit (0);
	}
	exec_cmd(shell);
}

// links STDIN/STDOUT to pipes, closes pipes
void	connect_pipes(t_minishell *shell)
{
	int	i;

	if (shell->cmdc <= 1)
		return ;
	if (shell->cmd_id == 1)
		dup2(shell->pipes[0][1], STDOUT_FILENO);
	else if (shell->cmd_id == shell->cmdc)
		dup2(shell->pipes[shell->cmdc - 2][0], STDIN_FILENO);
	else
	{
		dup2(shell->pipes[shell->cmd_id - 2][0], STDIN_FILENO);
		dup2(shell->pipes[shell->cmd_id - 1][1], STDOUT_FILENO);
	}
	i = -1;
	while (++i < shell->cmdc - 1)
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
