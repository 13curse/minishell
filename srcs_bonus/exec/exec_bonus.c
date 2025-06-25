/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:04:15 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:26:53 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int		exec(t_minishell *shell, char ***cmds, int cmds_lst_i);
void	exec2(t_minishell *shell, int cmdc);

void	exec_all(t_minishell *shell)
{
	int	i;

	i = 0;
	shell->status = exec(shell, shell->cmds_lst[i], i);
	while (shell->cmds_lst[++i])
	{
		if (shell->cmds_seps[i] == OR && shell->status)
			shell->status = exec(shell, shell->cmds_lst[i], i);
		else if (shell->cmds_seps[i] == AND && shell->status == 0)
			shell->status = exec(shell, shell->cmds_lst[i], i);
	}
}

int	alloc_pids(t_minishell *shell, int **pids, char ***cmds)
{
	*pids = malloc(sizeof(pid_t) * arr_len((void *)cmds));
	if (*pids == NULL)
		return (err_malloc(1));
	return (0);
	(void)shell;
}

int	abort_alloc_pipes(int ***pipes, int *pids)
{
	int	i;

	free(pids);
	i = -1;
	while ((*pipes)[++i])
		free((*pipes)[i]);
	free(*pipes);
	return (err_malloc(1));
}

// alloc pipes, NULL terminate, to call after alloc_pids
// free pids to in case of error, 
int	alloc_pipes(t_minishell *shell, int ***pipes, char ***cmds, int *pids)
{
	int	i;
	int	cmdc;

	cmdc = arr_len((void *)cmds);
	if (cmdc == 1)
		return (*pipes = NULL, 0);
	*pipes = malloc(sizeof(int *) * cmdc);
	if (*pipes == NULL)
	{
		free(pids);
		return (err_malloc(1));
	}
	i = -1;
	while (++i < cmdc)
		(*pipes)[i] = NULL;
	i = -1;
	while (++i < cmdc - 1)
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if ((*pipes)[i] == NULL)
			return (abort_alloc_pipes(pipes, pids));
	}
	return (0);
	(void)shell;
}

int	exec(t_minishell *shell, char ***cmds, int cmds_lst_i)
{
	int		i;
	int		cmdc;

	cmdc = arr_len((void *)cmds);
	if (alloc_pids(shell, &shell->pids, cmds)
		|| alloc_pipes(shell, &shell->pipes, cmds, shell->pids))
		return (1);
	i = -1;
	while (++i < cmdc - 1)
		pipe(shell->pipes[i]);
	i = -1;
	while (++i < cmdc)
	{
		shell->cmd_id = i + 1;
		shell->pids[i] = fork();
		if (shell->pids[i] == -1)
		{
			perror("exec:\n\tfork");
			exit (1);
		}
		else if (shell->pids[i] == 0)
			child_routine(shell, cmds[i], cmdc, cmds_lst_i);
	}
	exec2(shell, cmdc);
	return (shell->status);
}
