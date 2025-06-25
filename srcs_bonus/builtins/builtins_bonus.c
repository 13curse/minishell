/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:48:33 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/13 11:28:06 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

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
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}

int	is_redir(t_minishell *shell, char *token)
{
	if (!ft_strncmp(token, shell->op->heredoc, 2))
		return (2);
	if (!ft_strncmp(token, shell->op->append, 2))
		return (2);
	if (!ft_strncmp(token, shell->op->redir_in, 1))
		return (1);
	if (!ft_strncmp(token, shell->op->redir_out, 1))
		return (1);
	return (0);
}

int	is_builtin_cmd(t_minishell *shell, char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (is_builtin(cmd[i]))
			return (1);
		if (is_redir(shell, cmd[i]))
		{
			i++;
			continue ;
		}
	}
	return (0);
}
