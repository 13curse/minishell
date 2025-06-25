/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:31:34 by sbehar            #+#    #+#             */
/*   Updated: 2025/05/10 19:31:34 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	unset_var(t_env **lst, const char *key);
int			builtin_unset(char **args, t_minishell *shell);

static int	unset_var(t_env **lst, const char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *lst;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*lst = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return (1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

int	builtin_unset(char **args, t_minishell *shell)
{
	int	i;
	int	exit_code;

	i = 1;
	exit_code = 0;
	if (!args[1])
		return (0);
	while (args[i])
	{
		if (is_invalid_opt(args[i]))
		{
			ft_printf(2, "minishell: unset: `%s': not a valid identifier\n",
				args[i]);
			exit_code = 2;
		}
		else
		{
			unset_var(&shell->env_list, args[i]);
			unset_var(&shell->export_list, args[i]);
		}
		i++;
	}
	return (exit_code);
}
