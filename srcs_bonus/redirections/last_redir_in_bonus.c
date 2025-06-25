/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_redir_in_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:54:04 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:23:37 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	redir_in_all(t_minishell *shell);

void	print_last_redir_in(t_minishell *shell)
{
	int	i;
	int	j;

	printf("---last_redir_in-----\n");
	i = -1;
	while (++i < shell->cmdc)
	{
		printf("cdms %d\n", i);
		j = -1;
		while (shell->last_redir_in[i][++j] != -2)
			printf("\t%d: %d\n", j, shell->last_redir_in[i][j]);
	}
}

void	test_null_end(t_minishell *shell)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (shell->cmds_lst[++i])
	{
		j = -1;
		while (shell->cmds_lst[i][++j])
		{
			k = -1;
			while (shell->cmds_lst[i][j][++k])
				printf("token: %s\n", shell->cmds_lst[i][j][k]);
		}
	}
}

int	init_last_redir_in(t_minishell *shell)
{
	int	i;
	int	cmd_len;
	int	j;

	shell->last_redir_in = malloc(sizeof(int *) * (shell->cmdc + 1));
	if (shell->last_redir_in == NULL)
		return (err_malloc(1));
	i = -1;
	while (++i < shell->cmdc)
	{
		cmd_len = arr_len((void *)shell->cmds_lst[i]);
		shell->last_redir_in[i] = malloc(sizeof(int) * (cmd_len + 1));
		if (shell->last_redir_in[i] == NULL)
			return (err_malloc(1));
		j = -1;
		while (++j < cmd_len)
			shell->last_redir_in[i][j] = -1;
		shell->last_redir_in[i][cmd_len] = -2;
	}
	if (redir_in_all(shell))
		return (1);
	return (0);
}
