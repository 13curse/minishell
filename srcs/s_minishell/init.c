/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:22:06 by van-nguy          #+#    #+#             */
/*   Updated: 2025/06/11 15:47:15 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		set_heredocs(t_minishell *shell);
int		parse_paths(t_minishell *shell);
int		create_dup_stdio(t_minishell *shell);
void	free_heredocs(t_heredocs **heredocs);
int		init_shell2(t_minishell *shell);

int	init_shell(t_minishell *shell, char **envp)
{
	shell->status = 0;
	shell->cmd_id = 1;
	shell->sigquit_received = 0;
	shell->env = envp;
	shell->input = NULL;
	shell->cmds = NULL;
	shell->pipes = NULL;
	shell->pids = NULL;
	shell->env_list = NULL;
	shell->export_list = NULL;
	shell->uninterpreted = NULL;
	shell->history = NULL;
	shell->last_redir_in = NULL;
	shell->tokens = NULL;
	shell->paths = NULL;
	if (init_shell2(shell))
		return (1);
	setup_signal_handlers(0);
	return (0);
}

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

int	set_heredocs(t_minishell *shell)
{
	int	i;

	if (shell->heredocs != NULL)
	{
		free_heredocs(&shell->heredocs);
		shell->heredocs = NULL;
	}
	shell->heredocs = malloc(sizeof(t_heredocs));
	if (shell->heredocs == NULL)
		return (err_malloc(1));
	i = -1;
	while (++i < MAX_HEREDOCS + 1)
	{
		shell->heredocs->fds[i] = -1;
		shell->heredocs->names[i] = NULL;
	}
	shell->heredocs->i = 0;
	return (0);
}

int	parse_paths(t_minishell *shell)
{
	t_env	*export;

	shell->paths = NULL;
	if (shell->export_list == NULL)
		return (0);
	export = shell->export_list;
	while (export && export->key)
	{
		if (!ft_strncmp(export->key, "PATH", 4))
			break ;
		export = export->next;
	}
	if (export == NULL)
		return (0);
	shell->paths = ft_split(export->value, ':');
	if (shell->paths == NULL)
		return (1);
	return (0);
}

int	create_dup_stdio(t_minishell *shell)
{
	int	fd;
	int	fd2;

	fd = open("/dev/tty", O_RDONLY);
	fd2 = open("/dev/tty", O_RDONLY);
	if (fd == -1 || fd2 == -1)
	{
		perror("open");
		return (1);
	}
	if (dup2(STDIN_FILENO, fd) == -1 || dup2(STDOUT_FILENO, fd2) == -1)
	{
		perror("dup2");
		return (1);
	}
	shell->stdin = fd;
	shell->stdout = fd2;
	return (0);
}
