/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abort2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:46:10 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/12 16:46:10 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	free_env_list2(t_env **env_list);
void	free_uninterpreted(int ***uninterpreted);
void	free_cmds_seps(int **cmds_seps);
void	free_split(char **split);

void	free_env_list2(t_env **env_list)
{
	t_env	*tmp;

	if (*env_list == NULL)
		return ;
	while (*env_list)
	{
		tmp = *env_list;
		*env_list = (*env_list)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	*env_list = NULL;
}

void	free_uninterpreted(int ***uninterpreted)
{
	int	i;

	i = -1;
	while ((*uninterpreted)[++i])
		free ((*uninterpreted)[i]);
	free(*uninterpreted);
	*uninterpreted = NULL;
}

void	free_cmds_seps(int **cmds_seps)
{
	free (*cmds_seps);
	*cmds_seps = NULL;
}

void	free_split(char **split)
{
	int	i;

	if (split == NULL)
		return ;
	i = 0;
	while (split[i])
	{
		free (split[i]);
		i++;
	}
	free (split);
}
