/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:37:15 by van               #+#    #+#             */
/*   Updated: 2025/06/11 15:44:28 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		exec_cmd(t_minishell *shell);
static int	concat_path(char *dest, const char *dir,
				const char *cmd, int max_len);
static int	check_direct_cmd(const char *cmd, char *path,
				int max_len, int *found);
int			cat_path(t_minishell *shell, char **cmd, char *path, int *found);
int			parse_paths(t_minishell *shell);

void	exec_cmd(t_minishell *shell)
{
	char	path[256];
	char	**cmd;
	int		status;
	int		found;

	parse_paths(shell);
	cmd = shell->cmds[shell->cmd_id - 1];
	if (is_builtin(cmd[0]))
	{
		status = exec_builtins(cmd, shell);
		free_shell(shell);
		exit (status);
	}
	found = 0;
	if (cat_path(shell, cmd, path, &found))
	{
		free_shell(shell);
		exit (1);
	}
	execve(path, cmd, shell->env);
	perror("execve");
	free_shell(shell);
	exit (127 - found);
}

static int	concat_path(char *dest, const char *dir,
		const char *cmd, int max_len)
{
	int	dir_len;
	int	cmd_len;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	if (dir_len + cmd_len + 2 > max_len)
		return (1);
	ft_strlcpy(dest, dir, dir_len + 1);
	ft_strlcat(dest, "/", dir_len + 2);
	ft_strlcat(dest, &cmd[0], dir_len + cmd_len + 2);
	return (0);
}

static int	check_direct_cmd(const char *cmd, char *path,
		int max_len, int *found)
{
	int	cmd_len;

	cmd_len = ft_strlen(cmd);
	if (cmd_len + 1 > max_len)
		return (err_too_long_path(1));
	ft_strlcpy(path, cmd, cmd_len + 1);
	if (ft_strchr(cmd, '/'))
	{
		if (access(path, F_OK) == 0)
			*found = 1;
		return (1);
	}
	return (0);
}

int	cat_path(t_minishell *shell, char **cmd, char *path, int *found)
{
	char		**paths;
	const int	max_len = 256;

	paths = shell->paths;
	if (paths == NULL)
	{
		ft_strlcpy(path, cmd[0], ft_strlen(cmd[0]) + 1);
		return (0);
	}
	if (check_direct_cmd(cmd[0], path, max_len, found))
		return (0);
	while (paths && *paths)
	{
		if (concat_path(path, *paths, cmd[0], max_len))
			return (err_too_long_path(1));
		if (access(path, X_OK) == 0)
		{
			*found = 1;
			return (0);
		}
		paths++;
	}
	ft_strlcpy(path, cmd[0], ft_strlen(cmd[0]) + 1);
	return (0);
}
