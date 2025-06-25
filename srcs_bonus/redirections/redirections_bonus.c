/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:21:32 by van-nguy          #+#    #+#             */
/*   Updated: 2025/06/13 11:23:32 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	redirection_heredoc(t_minishell *shell, char **cmd, int i, int *tkn_i);
int	redirection_append(t_minishell *shell, char ***cmd);
int	redirection_in(t_minishell *shell, char **cmd, int i, int *tkn_i);
int	redirection_out(t_minishell *shell, char ***cmd);
int	connect_heredoc(t_minishell *shell);

void	redir_while(t_minishell *shell, char ***cmd, int cmds_lst_i, t_redir *v)
{
	while (**cmd)
	{
		if (shell->last_redir_in[cmds_lst_i][shell->cmd_id - 1]
			== -3 - (++v->tkn_i))
			break ;
		if (***cmd == '"' || ***cmd == '\'')
			;
		else if (ft_strnstr(**cmd, "<<", ft_strlen(**cmd)))
			(*cmd)++;
		else if (ft_strnstr(**cmd, ">>", ft_strlen(**cmd)))
			v->ret = redirection_append(shell, cmd);
		else if (ft_strnstr(**cmd, ">", ft_strlen(**cmd)))
			v->ret = redirection_out(shell, cmd);
		else if (ft_strnstr(**cmd, "<", ft_strlen(**cmd)))
			(*cmd)++;
		if (v->ret)
			break ;
		(*cmd)++;
	}
}

int	redir_if_ret(t_minishell *shell)
{
	shell->status = 1;
	ft_putstr_fd("redirection error\n", 2);
	perror("\t");
	return (1);
}

// redirect depending on the operator
int	redirections(t_minishell *shell, char **cmd, int cmds_lst_i)
{
	t_redir	v;

	v.tkn_i = -1;
	v.ret = 0;
	redir_while(shell, &cmd, cmds_lst_i, &v);
	if (shell->last_redir_in[cmds_lst_i][shell->cmd_id - 1] < -1)
	{
		perror("");
		shell->status = 1;
		return (1);
	}
	if (v.ret)
		return (redir_if_ret(shell));
	if (shell->last_redir_in[cmds_lst_i][shell->cmd_id - 1] == -3)
		return (1);
	if (shell->last_redir_in[cmds_lst_i][shell->cmd_id - 1] != -1)
	{
		if (dup2(shell->last_redir_in[cmds_lst_i][shell->cmd_id - 1], 0) == -1)
			return (1);
		close(shell->last_redir_in[cmds_lst_i][shell->cmd_id - 1]);
		shell->last_redir_in[cmds_lst_i][shell->cmd_id - 1] = -1;
	}
	return (0);
}

int	connect_heredoc(t_minishell *shell)
{
	int	i;

	i = shell->heredocs->i;
	close(shell->heredocs->fds[i]);
	shell->heredocs->fds[i] = open(shell->heredocs->names[i], O_RDONLY);
	if (shell->heredocs->fds[i] == -1)
	{
		perror("");
		return (1);
	}
	if (shell->heredocs->names[i] == NULL)
		return (0);
	if (dup2(shell->heredocs->fds[i], 0))
		return (1);
	return (0);
}

int	redirection_heredoc(t_minishell *shell, char **cmd, int i, int *tkn_i)
{
	char	*limiter;

	(*tkn_i)++;
	cmd++;
	limiter = *cmd;
	if (heredoc(shell, limiter, i))
		return (1);
	return (0);
}
