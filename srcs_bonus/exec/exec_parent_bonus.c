/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:30:13 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:26:45 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	print_uninterpreted(t_minishell *shell);

int	exec_parent(t_minishell *shell)
{
	char	**cmd;

	cmd = shell->cmds_lst[0][0];
	shell->cmd_id = 1;
	if (redirections(shell, cmd, 0))
		return (shell->status);
	remove_redirections(shell, cmd);
	expand_vars(shell, cmd);
	expand_quotes(shell, cmd);
	if (*cmd == NULL)
	{
		free_shell(shell);
		return (0);
	}
	shell->status = exec_builtins(cmd, shell);
	return (shell->status);
}
