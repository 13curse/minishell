/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:22:06 by van-nguy          #+#    #+#             */
/*   Updated: 2025/06/13 11:23:07 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int		set_heredocs(t_minishell *shell);
int		parse_paths(t_minishell *shell);
int		create_dup_stdio(t_minishell *shell);
void	free_heredocs(t_heredocs **heredocs);

int	init_shell2(t_minishell *shell)
{
	if (create_dup_stdio(shell))
		return (1);
	shell->op = malloc(sizeof(t_operators));
	if (shell->op == NULL)
		return (err_malloc(1));
	init_operators(shell->op);
	shell->heredocs = NULL;
	if (set_heredocs(shell))
	{
		free_shell(shell);
		return (1);
	}
	return (0);
}

int	init_shell(t_minishell *shell, char **envp)
{
	shell->status = 0;
	shell->cmd_id = 1;
	shell->env = envp;
	shell->paths = NULL;
	shell->input = NULL;
	shell->cmds_lst = NULL;
	shell->pipes = NULL;
	shell->pids = NULL;
	shell->env_list = NULL;
	shell->export_list = NULL;
	shell->uninterpreted = NULL;
	shell->history = NULL;
	shell->last_redir_in = NULL;
	shell->cmds_seps = NULL;
	if (init_shell2(shell))
		return (1);
	setup_signal_handlers(0);
	return (0);
}
