/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:12:50 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/25 22:27:06 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*create_node(const char *key, const char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		exit(EXIT_FAILURE);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	append_node(t_minishell *shell, const char *key, const char *value)
{
	t_env	*new_env_node;
	t_env	*new_export_node;
	t_env	*current;

	new_env_node = create_node(key, value);
	if (!shell->env_list)
		shell->env_list = new_env_node;
	else
	{
		current = shell->env_list;
		while (current->next)
			current = current->next;
		current->next = new_env_node;
	}
	new_export_node = create_node(key, value);
	if (!shell->export_list)
		shell->export_list = new_export_node;
	else
	{
		current = shell->export_list;
		while (current->next)
			current = current->next;
		current->next = new_export_node;
	}
}

void	fill_env(t_minishell *shell, char **envp)
{
	int		i;
	char	*sep;
	char	*value;
	size_t	key_len;
	char	*key;

	i = 0;
	while (envp[i])
	{
		sep = ft_strchr(envp[i], '=');
		if (sep)
		{
			key_len = sep - envp[i];
			key = malloc(key_len + 1);
			ft_strncpy(key, envp[i], key_len);
			key[key_len] = '\0';
			value = sep + 1;
			append_node(shell, key, value);
			free(key);
		}
		i++;
	}
}

char	*get_env_value(t_minishell *shell, const char *key)
{
	t_env	*env;

	env = shell->env_list;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	set_env_value(t_minishell *shell, const char *key, const char *value)
{
	t_env	*curr;

	curr = shell->env_list;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			curr->value = ft_strdup(value);
			return ;
		}
		curr = curr->next;
	}
	append_node(shell, key, value);
}
