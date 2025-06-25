/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:30:13 by van               #+#    #+#             */
/*   Updated: 2025/06/11 13:50:03 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_uninterpreted(t_minishell *shell);

static char	**prepare_cmd2(t_minishell *shell, int *count)
{
	char	**cmd2;
	int		i;

	*count = count_tokens_after_expand(shell);
	if (alloc_uninterpreted(shell, *count))
		kill_shell(shell);
	cmd2 = malloc(sizeof(char *) * (*count + 1));
	if (cmd2 == NULL)
	{
		err_malloc(1);
		kill_shell(shell);
	}
	i = -1;
	while (++i < *count + 1)
		cmd2[i] = NULL;
	expand_vars(shell, cmd2);
	free (shell->cmds[shell->cmd_id - 1]);
	shell->cmds[shell->cmd_id - 1] = cmd2;
	expand_quotes(shell);
	return (cmd2);
}

int	exec_parent(t_minishell *shell)
{
	char	**cmd2;
	int		count;

	shell->cmd_id = 1;
	if (redirections(shell))
		return (shell->status);
	remove_redirections(shell);
	cmd2 = prepare_cmd2(shell, &count);
	if (*cmd2 == NULL)
		return (0);
	shell->in_fork = 0;
	shell->status = exec_builtins(cmd2, shell);
	return (shell->status);
}
