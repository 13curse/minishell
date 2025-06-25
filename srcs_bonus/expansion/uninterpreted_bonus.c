/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uninterpreted_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:05:02 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:25:17 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	set_uninterpreted(t_minishell *shell, int i)
{
	int	j;

	j = -1;
	while (++j < MAX_UNINTERPRETED)
		shell->uninterpreted[i][j] = -1;
}

void	update_uninterpreted(t_minishell *shell, int ign_i, int l, int shift)
{
	int	j;

	if (shell->uninterpreted == NULL || shell->uninterpreted[ign_i] == NULL)
		return ;
	j = -1;
	while (++j < MAX_UNINTERPRETED)
	{
		if (shell->uninterpreted[ign_i][j] == l)
		{
			shell->uninterpreted[ign_i][j] -= shift;
			return ;
		}
	}
}

int	is_interpreted(t_minishell *shell, int i, int l)
{
	int	j;

	if (shell->uninterpreted == NULL || shell->uninterpreted[i] == NULL)
		return (1);
	j = -1;
	while (shell->uninterpreted[i][++j] != -1)
	{
		if (shell->uninterpreted[i][j] == l)
			return (0);
		if (shell->uninterpreted[i][j] > l)
			return (1);
	}
	return (1);
}

int	alloc_uninterpreted(t_minishell *shell, char **cmd)
{
	int		len;
	int		i;

	len = arr_len((void *)cmd);
	shell->uninterpreted = malloc (sizeof(int *) * (len + 1));
	if (shell->uninterpreted == NULL)
		return (err_malloc(1));
	i = -1;
	while (++i < len + 1)
		shell->uninterpreted[i] = NULL;
	return (0);
}

void	add_uninterpreted(t_minishell *shell, int i, int l)
{
	int	k;

	k = -1;
	while (++k < MAX_UNINTERPRETED)
	{
		if (shell->uninterpreted[i][k] == -1)
		{
			shell->uninterpreted[i][k] = l;
			break ;
		}
	}
	if (k < MAX_UNINTERPRETED)
		return ;
	write(2, "max_uninterpreted chars has been reached\n", 41);
	free_shell(shell);
	exit(1);
}
