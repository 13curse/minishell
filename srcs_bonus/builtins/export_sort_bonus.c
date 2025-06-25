/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:43:29 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/10 11:43:29 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	set_var(t_env **lst, const char *key, const char *value);
char	**get_sorted_exp(t_minishell *shell);
void	append_var(t_env **lst, const char *key, const char *value);
void	extract_exp_key(const char *arg, char *key, int *append);
void	print_export_var(t_env *var);

void	set_var(t_env **lst, const char *key, const char *value)
{
	t_env	*curr;

	curr = *lst;
	while (curr && ft_strcmp(curr->key, key) != 0)
		curr = curr->next;
	if (curr)
	{
		free(curr->value);
		if (value)
			curr->value = ft_strdup(value);
		else
			curr->value = NULL;
	}
	else
	{
		curr = malloc(sizeof(t_env));
		curr->key = ft_strdup(key);
		if (value)
			curr->value = ft_strdup(value);
		else
			curr->value = NULL;
		curr->next = *lst;
		*lst = curr;
	}
}

char	**get_sorted_exp(t_minishell *shell)
{
	char	**keys;
	t_env	*curr;
	int		i;
	int		size;

	size = export_lst_size(shell);
	keys = malloc(sizeof(char *) * (size + 1));
	if (!keys)
		return (NULL);
	curr = shell->export_list;
	i = 0;
	while (curr)
	{
		keys[i++] = curr->key;
		curr = curr->next;
	}
	keys[i] = NULL;
	ft_sort_str_tab(keys);
	return (keys);
}

void	append_var(t_env **lst, const char *key, const char *value)
{
	t_env	*curr;
	char	*new_value;

	curr = *lst;
	while (curr && ft_strcmp(curr->key, key) != 0)
		curr = curr->next;
	if (curr && curr->value)
	{
		new_value = malloc(ft_strlen(curr->value) + ft_strlen(value) + 1);
		if (!new_value)
			return ;
		ft_strcpy(new_value, curr->value);
		ft_strcat(new_value, value);
	}
	else
		new_value = ft_strdup(value);
	set_var(lst, key, new_value);
	free(new_value);
}

void	extract_exp_key(const char *arg, char *key, int *append)
{
	char	*equal;
	int		key_len;

	equal = ft_strchr(arg, '=');
	key_len = 0;
	*append = 0;
	if (equal)
	{
		key_len = equal - arg;
		if (key_len > 0 && arg[key_len - 1] == '+')
		{
			*append = 1;
			key_len--;
		}
		ft_strncpy(key, arg, key_len);
		key[key_len] = '\0';
	}
}

void	print_export_var(t_env *var)
{
	if (var->value)
		printf("declare -x %s=\"%s\"\n", var->key, var->value);
	else
		printf("declare -x %s\n", var->key);
}
