/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:25:37 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/08 13:25:37 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	process_in_token(t_minishell *shell,
				char ***cmd, int tkn_i, int *ret);
static int	redir_in_loop(t_minishell *shell);
int			redir_in(t_minishell *shell);

static int	process_in_token(t_minishell *shell, char ***cmd,
		int tkn_i, int *ret)
{
	if (***cmd == '"' || ***cmd == '\'')
		return (0);
	else if (ft_strnstr(**cmd, "<<", ft_strlen(**cmd)))
		*ret = redirection_heredoc(shell, cmd);
	else if (ft_strnstr(**cmd, "<", ft_strlen(**cmd)))
		*ret = redirection_in(shell, cmd);
	if (*ret == 2)
		shell->last_redir_in[shell->cmd_id - 1] = -2 - tkn_i;
	if (*ret == 666)
		return (666);
	return (*ret == 1);
}

static int	redir_in_loop(t_minishell *shell)
{
	int		ret;
	char	**cmd;
	int		tkn_i;

	tkn_i = -1;
	cmd = shell->cmds[shell->cmd_id - 1];
	ret = 0;
	while (cmd && *cmd)
	{
		tkn_i++;
		ret = 0;
		if (process_in_token(shell, &cmd, tkn_i, &ret))
			break ;
		cmd++;
		if (*cmd == NULL)
			cmd = shell->cmds[++shell->cmd_id - 1];
	}
	return (ret);
}

int	redir_in(t_minishell *shell)
{
	int		ret;

	ret = redir_in_loop(shell);
	shell->cmd_id--;
	if (ret)
	{
		if (ret != 666)
		{
			perror(" ");
			return (1);
		}
		return (666);
	}
	return (ret);
}
