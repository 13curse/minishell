/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:50:23 by van-nguy          #+#    #+#             */
/*   Updated: 2025/06/13 11:22:22 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	set_heredocs(t_minishell *shell);
int	parse_paths(t_minishell *shell);

static void	cleanup_shell_loop(t_minishell *shell)
{
	if (shell->cmds_lst)
		free_cmds_lst(shell);
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (reset_stdio(shell))
		kill_shell(shell);
	if (shell->last_redir_in)
		free_last_redir_in(shell);
}

static int	handle_prompt_and_parse(t_minishell *shell)
{
	shell->input = sent_prompt(shell);
	if (shell->input == NULL || shell->input[0] == '\0')
		return (1);
	shell->cmds_lst = cmds_lst(shell, split_tokens(shell->input));
	if (shell->cmds_lst == NULL)
		return (1);
	return (0);
}

static void	execute_cmds(t_minishell *shell)
{
	if (init_last_redir_in(shell))
		return ;
	if (shell->cmdc == 1 && shell->cmds_lst[0][1] == NULL
		&& is_builtin_cmd(shell, shell->cmds_lst[0][0]))
	{
		shell->status = exec_parent(shell);
		return ;
	}
	if (shell->cmdc)
		exec_all(shell);
}

static void	shell_loop(t_minishell *shell)
{
	while (1)
	{
		shell->cmd_id = 1;
		if (set_heredocs(shell))
		{
			free_shell(shell);
			exit(1);
		}
		cleanup_shell_loop(shell);
		if (handle_prompt_and_parse(shell))
			continue ;
		execute_cmds(shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	if (init_shell(&shell, envp))
		return (1);
	fill_env(&shell, envp);
	shell_loop(&shell);
	free_shell(&shell);
	return (shell.status);
	(void)argc;
	(void)argv;
}

// shell.cmds tableau de tte les cmds a envoyer dans des forks
// ex: "echo" Hello > file | wc -l | grep 1 > file2"
// 		->
// {
// 	{"echo", "Hello", ">", "file", NULL},
// 	{"wc", "-l", NULL},
// 	{"grep", "1", ">", "file2", NULL},
// 	 NULL
// }

/*

clear; make re
valgrind --leak-check=full --show-leak-kinds=all -s ./minishell
echo a | cat < file

*/
