/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:04:15 by van               #+#    #+#             */
/*   Updated: 2025/06/09 16:15:07 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	alloc_pids(t_minishell *shell, int **pids);
int	alloc_pipes(t_minishell *shell, int ***pipes, int *pids);
int	abort_alloc_pipes(int ***pipes, int *pids);

int	prepare_and_launch(t_minishell *shell)
{
	int	i;

	i = -1;
	while (++i < shell->cmdc - 1)
		pipe(shell->pipes[i]);
	i = -1;
	while (++i < shell->cmdc)
	{
		shell->cmd_id = i + 1;
		shell->pids[i] = fork();
		if (shell->pids[i] == -1)
		{
			perror("exec:\n\tfork");
			exit (1);
		}
		else if (shell->pids[i] == 0)
			child_routine(shell);
	}
	return (0);
}

void	sync_and_clean(t_minishell *shell)
{
	int	i;

	i = -1;
	while (shell->cmdc > 1 && shell->pipes[++i])
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
	}
	waitpid(shell->pids[shell->cmdc - 1], &shell->status, 0);
	if (WIFEXITED(shell->status))
		shell->status = WEXITSTATUS(shell->status);
	i = -1;
	while (++i < shell->cmdc - 1)
		waitpid(shell->pids[i], NULL, 0);
	free(shell->pids);
	shell->pids = NULL;
	i = -1;
	while (shell->cmdc > 1 && ++i < shell->cmdc)
	{
		if (i <= shell->cmdc - 1)
			free(shell->pipes[i]);
	}
	if (shell->pipes != NULL)
		free(shell->pipes);
	shell->pipes = NULL;
}

void	exec(t_minishell *shell)
{
	pid_t	*pids;
	int		**pipes;

	if (alloc_pids(shell, &pids) || alloc_pipes(shell, &pipes, pids))
		return ;
	shell->pids = pids;
	shell->pipes = pipes;
	prepare_and_launch(shell);
	sync_and_clean(shell);
}
