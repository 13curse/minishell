/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:50:23 by van-nguy          #+#    #+#             */
/*   Updated: 2025/06/09 13:46:25 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
<<ff cat > 1 | <<dd cat > 2 | <<gg cat > 3
*/

#include "../minishell.h"

int			set_heredocs(t_minishell *shell);
int			parse_paths(t_minishell *shell);
static void	shell_loop(t_minishell *shell);
int			main(int argc, char **argv, char **envp);

static void	shell_loop(t_minishell *shell)
{
	while (1)
	{
		shell->cmd_id = 1;
		if (set_heredocs(shell))
			kill_shell(shell);
		clean_shell_loop(shell);
		if (reset_stdio(shell))
			kill_shell(shell);
		if (!get_and_parse_input(shell))
			continue ;
		if (!handle_redirections(shell))
			continue ;
		if (shell->cmdc == 1 && is_builtin(**shell->cmds))
		{
			shell->status = exec_parent(shell);
			free_cmds(shell, &shell->cmds);
			continue ;
		}
		if (shell->cmdc)
			exec(shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	if (init_and_fill_shell(&shell, envp))
		return (1);
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
