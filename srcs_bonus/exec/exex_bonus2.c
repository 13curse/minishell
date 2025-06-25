/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exex_bonus2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:45:23 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:26:40 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	exec2(t_minishell *shell, int cmdc)
{
	int	i;

	i = -1;
	while (cmdc > 1 && shell->pipes[++i])
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
	}
	waitpid(shell->pids[cmdc - 1], &shell->status, 0);
	if (WIFEXITED(shell->status))
		shell->status = WEXITSTATUS(shell->status);
	free (shell->pids);
	shell->pids = NULL;
	i = -1;
	while (cmdc > 1 && ++i < cmdc)
	{
		if (i <= cmdc - 1)
			free(shell->pipes[i]);
	}
	if (shell->pipes != NULL)
		free (shell->pipes);
	shell->pipes = NULL;
}
