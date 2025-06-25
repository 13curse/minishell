/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmds_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:18:04 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/12 22:18:04 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	print_cmds(char ***cmds);
void	print_arr(char **arr);
void	print_cmds_seps(t_minishell *shell, int count);
void	print_cmds_lst(char ****cmds_lst);

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

void	print_cmds_seps(t_minishell *shell, int count)
{
	int	i;

	printf("cmds_seps:\n");
	i = -1;
	while (++i < count)
	{
		if (shell->cmds_seps[i] == OR)
			printf("%d: ||\n", i);
		else if (shell->cmds_seps[i] == AND)
			printf("%d: &&\n", i);
		else
			printf("%d: \n", i);
	}
}

void	print_cmds_lst(char ****cmds_lst)
{
	int	i;

	i = -1;
	printf("---cmds_lst-----\n");
	while (cmds_lst[++i])
	{
		printf("\ni: %d\n", i);
		print_cmds(cmds_lst[i]);
	}
}
