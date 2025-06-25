/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:42:49 by van-nguy          #+#    #+#             */
/*   Updated: 2025/06/09 13:33:23 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_pipes(int ***pipes);
void	free_heredocs(t_heredocs **heredocs);
void	free_operators(t_operators **op);
void	free_paths(char ***paths);
void	free_uninterpreted(t_minishell *shell, int ***uninterpreted);

void	free_pipes(int ***pipes)
{
	int	i;

	if (*pipes == NULL)
		return ;
	i = -1;
	while ((*pipes)[++i])
		free((*pipes)[i]);
	free(*pipes);
	*pipes = NULL;
}

void	free_heredocs(t_heredocs **heredocs)
{
	int	i;

	i = -1;
	while ((*heredocs)->names[++i])
	{
		if ((*heredocs)->fds[i] > 2)
			close((*heredocs)->fds[i]);
		unlink((*heredocs)->names[i]);
		free((*heredocs)->names[i]);
	}
	free(*heredocs);
	*heredocs = NULL;
}

void	free_operators(t_operators **op)
{
	if (*op == NULL)
		return ;
	free(*op);
	*op = NULL;
}

void	free_paths(char ***paths)
{
	int	i;

	if (*paths == NULL)
		return ;
	i = -1;
	while ((*paths)[++i])
		free((*paths)[i]);
	free(*paths);
	*paths = NULL;
}

void	free_uninterpreted(t_minishell *shell, int ***uninterpreted)
{
	int	i;
	int	len;

	if (shell->cmds == NULL)
		write(2, "err: cmds is NULL\n", 19);
	len = arr_len(shell->cmds[shell->cmd_id - 1]);
	i = -1;
	while (++i < len)
	{
		if ((*uninterpreted)[i])
			free ((*uninterpreted)[i]);
	}
	free(*uninterpreted);
	*uninterpreted = NULL;
}
