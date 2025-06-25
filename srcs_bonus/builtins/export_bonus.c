/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:34:50 by sbehar            #+#    #+#             */
/*   Updated: 2025/05/09 21:34:50 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static void	update_exp_env(t_minishell *shell, const char *key,
				const char *value, int append);
static int	print_invalid_id(const char *arg);
static int	handle_exp_arg(t_minishell *shell, const char *arg);
static void	print_export_sorted(t_minishell *shell);
int			builtin_export(char **args, t_minishell *shell);

static void	print_export_sorted(t_minishell *shell)
{
	char	**keys;
	t_env	*curr;
	int		i;

	keys = get_sorted_exp(shell);
	if (!keys)
		return ;
	i = 0;
	while (keys[i])
	{
		curr = shell->export_list;
		while (curr && ft_strcmp(curr->key, keys[i]) != 0)
			curr = curr->next;
		if (curr && ft_strcmp(curr->key, "_") != 0)
			print_export_var(curr);
		i++;
	}
	free(keys);
}

static void	update_exp_env(t_minishell *shell, const char *key,
	const char *value, int append)
{
	if (append)
	{
		append_var(&shell->export_list, key, value);
		append_var(&shell->env_list, key, value);
	}
	else
	{
		set_var(&shell->export_list, key, value);
		set_var(&shell->env_list, key, value);
	}
}

static int	print_invalid_id(const char *arg)
{
	ft_printf(2, "minishell: export: `%s': not a valid identifier\n", arg);
	return (1);
}

static int	handle_exp_arg(t_minishell *shell, const char *arg)
{
	char	key[1024];
	char	*equal;
	int		append;

	append = 0;
	equal = ft_strchr(arg, '=');
	if (equal)
		extract_exp_key(arg, key, &append);
	if (!is_valid_id(arg))
		return (print_invalid_id(arg));
	else if (equal)
		update_exp_env(shell, key, equal + 1, append);
	else
		set_var(&shell->export_list, arg, NULL);
	return (0);
}

int	builtin_export(char **args, t_minishell *shell)
{
	int		i;
	int		exit_code;

	i = 1;
	exit_code = 0;
	if (!args[1])
	{
		print_export_sorted(shell);
		return (0);
	}
	while (args[i])
	{
		if (handle_exp_arg(shell, args[i]))
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
