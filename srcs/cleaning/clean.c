/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:25:22 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/09 14:36:41 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env_list2(t_env **env_list);
void	free_shell2(t_minishell *shell);
void	free_shell(t_minishell *shell);
void	kill_shell(t_minishell *shell);

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

void	free_shell2(t_minishell *shell)
{
	if (shell->heredocs)
		free_heredocs(&shell->heredocs);
	if (shell->op)
		free_operators(&shell->op);
	if (shell->paths)
		free_paths(&shell->paths);
	if (shell->env_list)
		free_env_list2(&shell->env_list);
	if (shell->export_list)
		free_env_list2(&shell->export_list);
	if (shell->history)
		free_history(shell->history);
	if (shell->last_redir_in)
	{
		free(shell->last_redir_in);
		shell->last_redir_in = NULL;
	}
}

void	free_shell(t_minishell *shell)
{
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->uninterpreted)
		free_uninterpreted(shell, &shell->uninterpreted);
	if (shell->cmds)
		free_cmds(shell, &shell->cmds);
	if (shell->pipes)
		free_pipes(&shell->pipes);
	if (shell->pids)
	{
		free(shell->pids);
		shell->pids = NULL;
	}
	free_shell2(shell);
}

void	kill_shell(t_minishell *shell)
{
	free_shell(shell);
	exit(0);
	if (shell)
	{
	}
}
