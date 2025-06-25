/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:21:32 by van-nguy          #+#    #+#             */
/*   Updated: 2025/06/10 11:19:18 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_redir_token(t_minishell *shell, char ***cmd, int *tkn_i);
static int	process_redir_tokens(t_minishell *shell);
static int	handle_redir_errors(t_minishell *shell, int ret);
static int	apply_redir_in(t_minishell *shell);
int			redirections(t_minishell *shell);
/*
<<ff cat > 1| <<dd cat > 2
*/

static int	handle_redir_token(t_minishell *shell, char ***cmd, int *tkn_i)
{
	int	ret;

	ret = 0;
	if (shell->last_redir_in[shell->cmd_id - 1] == -2 - (++(*tkn_i)))
		return (1);
	if (***cmd == '"' || ***cmd == '\'')
		;
	else if (ft_strnstr(**cmd, "<<", ft_strlen(**cmd)))
		(*cmd)++;
	else if (ft_strnstr(**cmd, ">>", ft_strlen(**cmd)))
		ret = redirection_append(shell, cmd);
	else if (ft_strnstr(**cmd, ">", ft_strlen(**cmd)))
		ret = redirection_out(shell, cmd);
	else if (ft_strnstr(**cmd, "<", ft_strlen(**cmd)))
		(*cmd)++;
	if (ret)
		return (-1);
	return (0);
}

static int	process_redir_tokens(t_minishell *shell)
{
	char	**cmd;
	int		tkn_i;
	int		ret;
	int		status;

	tkn_i = -1;
	cmd = shell->cmds[shell->cmd_id - 1];
	ret = 0;
	while (*cmd)
	{
		status = handle_redir_token(shell, &cmd, &tkn_i);
		if (status == 1)
			break ;
		if (status == -1)
		{
			ret = 1;
			break ;
		}
		cmd++;
	}
	return (ret);
}

static int	handle_redir_errors(t_minishell *shell, int ret)
{
	if (shell->last_redir_in[shell->cmd_id - 1] < -1)
	{
		perror("");
		shell->status = 1;
		return (1);
	}
	if (ret)
	{
		shell->status = 1;
		perror(" ");
		return (1);
	}
	return (0);
}

static int	apply_redir_in(t_minishell *shell)
{
	int	fd;

	if (shell->last_redir_in[shell->cmd_id - 1] == -2)
		return (1);
	if (shell->last_redir_in[shell->cmd_id - 1] != -1)
	{
		fd = shell->last_redir_in[shell->cmd_id -1];
		if (dup2(fd, 0) == -1)
			return (1);
		close(fd);
		shell->last_redir_in[shell->cmd_id - 1] = -1;
	}
	return (0);
}

// redirect depending on the operator
int	redirections(t_minishell *shell)
{
	int		ret;

	ret = process_redir_tokens(shell);
	if (handle_redir_errors(shell, ret))
		return (1);
	if (apply_redir_in(shell))
		return (1);
	return (0);
}
