/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:57:28 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/12 16:57:28 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int		set_heredocs(t_minishell *shell);
int		parse_paths(t_minishell *shell);
int		create_dup_stdio(t_minishell *shell);
void	free_heredocs(t_heredocs **heredocs);

int	set_heredocs(t_minishell *shell)
{
	int	i;

	if (shell->heredocs != NULL)
		free_heredocs(&shell->heredocs);
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

	export = shell->export_list;
	while (export && export->key)
	{
		if (!ft_strncmp(export->key, "PATH", 4))
			break ;
		export = export->next;
	}
	if (export == NULL || export->value == NULL)
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

int	init_cmds_seps(t_minishell *shell, int cmdc)
{
	int	i;

	shell->cmds_seps = malloc(sizeof(int) * (cmdc));
	if (shell->cmds_seps == NULL)
		return (err_malloc(1));
	i = -1;
	while (++i < cmdc)
		shell->cmds_seps[i] = -1;
	return (0);
}
