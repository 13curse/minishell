/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:22:41 by van-nguy          #+#    #+#             */
/*   Updated: 2025/06/13 11:23:27 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	move_to_end(char **cmd, int i);
int		redirection_heredoc(t_minishell *shell, char **cmd, int i, int *tkn_i);
int		redirection_in(t_minishell *shell, char **cmd, int i, int *tkn_i);
int		var_expanded_len(t_minishell *shell, char *cmd);

int	redir_in_all(t_minishell *shell)
{
	int	i;

	i = -1;
	while (++i < shell->cmdc)
	{
		if (redir_in(shell))
			return (1);
		shell->cmd_id++;
	}
	shell->cmd_id = 1;
	return (0);
}

void	redir_in_inner_while(t_minishell *shell, t_redir_in *v, char **cmd)
{
	while (cmd[++v->tkn_i])
	{
		v->ret = 0;
		if (*cmd[v->tkn_i] == '"' || *cmd[v->tkn_i] == '\'')
			;
		else if (ft_strnstr(cmd[v->tkn_i], "<<", ft_strlen(cmd[v->tkn_i])))
			v->ret = redirection_heredoc(shell,
					cmd + v->tkn_i, v->i, &v->tkn_i);
		else if (ft_strnstr(cmd[v->tkn_i], "<", ft_strlen(cmd[v->tkn_i])))
			v->ret = redirection_in(shell, cmd + v->tkn_i, v->i, &v->tkn_i);
		if (v->ret == 1)
			break ;
		else if (v->ret == 2)
			shell->last_redir_in[shell->cmd_id - 1][v->i] = -3 - v->tkn_i;
	}
}

int	redir_in(t_minishell *shell)
{
	char		***cmds;
	char		**cmd;
	t_redir_in	v;

	cmds = shell->cmds_lst[shell->cmd_id - 1];
	v.i = -1;
	while (cmds && cmds[++v.i])
	{
		cmd = cmds[v.i];
		v.tkn_i = -1;
		redir_in_inner_while(shell, &v, cmd);
		if (v.ret == 1)
		{
			ft_putstr_fd("redirection error\n", 2);
			perror("\t");
			return (1);
		}
	}
	return (0);
}

void	remove_redirections(t_minishell *shell, char **cmd)
{
	int		i;

	i = -1;
	while (cmd[++i])
	{
		if (is_op(cmd[i], shell->op))
		{
			move_to_end(cmd, i);
			i = -1;
		}
	}
}

void	move_to_end(char **cmd, int i)
{
	int		j;

	free(cmd[i]);
	free(cmd[i + 1]);
	cmd[i] = NULL;
	cmd[i + 1] = NULL;
	j = -1;
	while (cmd[i + ++j + 2])
	{
		cmd[i + j] = cmd[i + j + 2];
		cmd[i + j + 2] = NULL;
	}
}
