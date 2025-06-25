/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:40:21 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/08 12:40:21 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		add_uninterpreted_filename(int *uninterpreted,
			int *uninterpreted_i, int len);
int		is_interpreted2(int *uninterpreted, int len);
void	update_uninterpreted2(int *uninterpreted, int *len);

int	add_uninterpreted_filename(int *uninterpreted,
		int *uninterpreted_i, int len)
{
	if (*uninterpreted_i >= MAX_UNINTERPRETED)
	{
		write(2, "too many uninterpreted characters\n", 34);
		return (1);
	}
	uninterpreted[*uninterpreted_i] = len;
	(*uninterpreted_i)++;
	return (0);
}

int	is_interpreted2(int *uninterpreted, int len)
{
	int	i;

	i = -1;
	while (++i < MAX_UNINTERPRETED && uninterpreted[i] != -1)
	{
		if (uninterpreted[i] == len)
			return (0);
		if (uninterpreted[i] > len)
			return (1);
	}
	return (1);
}

void	update_uninterpreted2(int *uninterpreted, int *len)
{
	int	i;

	i = -1;
	while (++i < 31)
	{
		if (uninterpreted[i] == -1)
			return ;
		if (uninterpreted[i] >= *len)
			uninterpreted[i]--;
	}
	(*len)--;
}
