/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:48:33 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/11 15:51:22 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_builtins(char **args, t_minishell *shell);
int	is_builtin(const char *cmd);
int	builtin_env(t_minishell *shell);
int	is_invalid_opt(const char *arg);

int	exec_builtins(char **args, t_minishell *shell)
{
	if (!args || !args[0])
		return (1);
	if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, shell));
	else if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(shell));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, shell));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd(shell));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(shell, args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, shell));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	else if (ft_strcmp(args[0], "history") == 0)
		return (print_history(shell));
	else
		printf("invalid command: %s\n", args[0]);
	return (0);
}

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "history") == 0)
		return (1);
	return (0);
}

int	builtin_env(t_minishell *shell)
{
	t_env	*current;

	current = shell->env_list;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n",
				current->key, current->value);
		current = current->next;
	}
	return (0);
}

int	is_invalid_opt(const char *arg)
{
	return (arg[0] == '-' && arg[1] != '\0' && ft_strcmp(arg, "--") != 0);
}
