/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abort_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:42:49 by van-nguy          #+#    #+#             */
/*   Updated: 2025/06/13 11:27:13 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	free_pipes(int ***pipes);
void	free_heredocs(t_heredocs **heredocs);
void	free_operators(t_operators **op);
void	free_paths(char ***paths);

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
