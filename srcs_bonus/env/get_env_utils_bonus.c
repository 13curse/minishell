/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:28:31 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/07 18:28:31 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	env_lst_size(t_minishell *shell)
{
	int		len;
	t_env	*env;

	env = shell->env_list;
	if (!env)
		return (0);
	len = 1;
	while (env)
	{
		env = env->next;
		len++;
	}
	return (len);
}

void	free_env_list(t_minishell *shell)
{
	t_env	*tmp;

	while (shell->env_list)
	{
		tmp = shell->env_list;
		shell->env_list = shell->env_list->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
