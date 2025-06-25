/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:41:48 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/12 16:41:48 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	free_cmds_lst(t_minishell *shell);
void	free_last_redir_in(t_minishell *shell);
void	free_shell2(t_minishell *shell);
void	free_shell(t_minishell *shell);
void	kill_shell(t_minishell *shell);
void	free_pipes(int ***pipes);
void	free_heredocs(t_heredocs **heredocs);
void	free_operators(t_operators **op);
void	free_paths(char ***paths);
void	free_env_list2(t_env **env_list);
void	free_uninterpreted(int ***uninterpreted);
void	free_cmds_seps(int **cmds_seps);

void	free_cmds_lst(t_minishell *shell)
{
	int	i;

	i = -1;
	while (shell->cmds_lst[++i])
		free_cmds(shell, &shell->cmds_lst[i]);
	free(shell->cmds_lst);
	shell->cmds_lst = NULL;
}

void	free_last_redir_in(t_minishell *shell)
{
	int	i;
	int	j;

	i = -1;
	while (++i < shell->cmdc)
	{
		j = -1;
		while (shell->last_redir_in[i][++j] != -2)
		{
			if (shell->last_redir_in[i][j] > 2)
				close (shell->last_redir_in[i][j]);
		}
		free(shell->last_redir_in[i]);
	}
	free(shell->last_redir_in);
	shell->last_redir_in = NULL;
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
		free_last_redir_in(shell);
	if (shell->cmds_seps)
		free_cmds_seps(&shell->cmds_seps);
}

void	free_shell(t_minishell *shell)
{
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->cmds_lst)
		free_cmds_lst(shell);
	if (shell->uninterpreted)
		free_uninterpreted(&shell->uninterpreted);
	if (shell->pipes)
		free_pipes(&shell->pipes);
	if (shell->pids)
	{
		free(shell->pids);
		shell->pids = NULL;
	}
}

void	kill_shell(t_minishell *shell)
{
	free_shell(shell);
	exit(shell->status);
	if (shell)
	{
	}
}
