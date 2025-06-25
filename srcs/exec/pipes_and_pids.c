/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_pids.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:13:04 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/09 16:15:00 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	alloc_pipes(t_minishell *shell, int ***pipes, int *pids);
int	abort_alloc_pipes(int ***pipes, int *pids);
int	alloc_pids(t_minishell *shell, int **pids);

// alloc pipes, NULL terminate, to call after alloc_pids
// free pids to in case of error, 

int	alloc_pipes(t_minishell *shell, int ***pipes, int *pids)
{
	int	i;

	if (shell->cmdc == 1)
	{
		*pipes = NULL;
		return (0);
	}
	*pipes = malloc(sizeof(int *) * shell->cmdc);
	if (*pipes == NULL)
	{
		free(pids);
		return (err_malloc(1));
	}
	i = -1;
	while (++i < shell->cmdc)
		(*pipes)[i] = NULL;
	i = -1;
	while (++i < shell->cmdc - 1)
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if ((*pipes)[i] == NULL)
			return (abort_alloc_pipes(pipes, pids));
	}
	return (0);
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

int	alloc_pids(t_minishell *shell, int **pids)
{
	*pids = malloc(sizeof(pid_t) * shell->cmdc);
	if (*pids == NULL)
		return (err_malloc(1));
	return (0);
}
