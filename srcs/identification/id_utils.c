/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:20:52 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/09 17:45:08 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_cmds_array(char ****cmds);
void		free_cmds(t_minishell *shell, char ****cmds);
void		print_cmds(char ***cmds);
void		print_arr(char **arr);

static void	free_cmds_array(char ****cmds)
{
	int	i;
	int	j;

	if (!cmds || !*cmds)
		return ;
	i = -1;
	while ((*cmds)[++i])
	{
		j = -1;
		while ((*cmds)[i][++j])
			free((*cmds)[i][j]);
		free((*cmds)[i]);
	}
	free(*cmds);
	*cmds = NULL;
}

void	free_cmds(t_minishell *shell, char ****cmds)
{
	int	i;

	if (shell->uninterpreted)
		free_uninterpreted(shell, &shell->uninterpreted);
	if (shell->last_redir_in)
	{
		i = -1;
		while (++i < shell->cmdc)
		{
			if (shell->last_redir_in[i] > 2)
				close(shell->last_redir_in[i]);
		}
		free(shell->last_redir_in);
		shell->last_redir_in = NULL;
	}
	free_cmds_array(cmds);
}

void	print_cmds(char ***cmds)
{
	int	i;
	int	j;

	printf("--------cmds-----------\n");
	i = -1;
	while (cmds[++i])
	{
		printf("%d:\n", i);
		j = -1;
		while (cmds[i][++j])
			printf("\t%s\n", cmds[i][j]);
	}
	printf("-----------------------\n");
}

void	print_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		printf("\t%s\n", arr[i]);
}
