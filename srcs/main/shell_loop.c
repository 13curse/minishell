/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:52:50 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/07 18:52:50 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_shell_loop(t_minishell *shell);
int		get_and_parse_input(t_minishell *shell);
int		handle_redirections(t_minishell *shell);
int		init_and_fill_shell(t_minishell *shell, char **envp);
int		setup_redirections(t_minishell *shell);

void	clean_shell_loop(t_minishell *shell)
{
	if (shell->cmds)
		free_cmds(shell, &shell->cmds);
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
}

int	get_and_parse_input(t_minishell *shell)
{
	shell->input = sent_prompt(shell);
	if (shell->input == NULL || shell->input[0] == '\0')
		return (0);
	shell->cmds = split_cmds(shell, split_tokens(shell->input));
	if (shell->cmds == NULL)
		return (0);
	shell->cmdc = cmds_len(shell->cmds);
	return (1);
}

int	handle_redirections(t_minishell *shell)
{
	if (setup_redirections(shell))
		return (0);
	return (1);
}

int	init_and_fill_shell(t_minishell *shell, char **envp)
{
	if (init_shell(shell, envp))
		return (1);
	fill_env(shell, envp);
	return (0);
}

int	setup_redirections(t_minishell *shell)
{
	int	i;

	shell->last_redir_in = malloc(sizeof(int) * (shell->cmdc + 1));
	if (shell->last_redir_in == NULL)
		return (err_malloc(1));
	i = -1;
	while (++i < shell->cmdc + 1)
		shell->last_redir_in[i] = -1;
	if (redir_in(shell) == 666)
		return (666);
	return (0);
}
