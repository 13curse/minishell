/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:40:54 by van               #+#    #+#             */
/*   Updated: 2025/06/25 22:27:25 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_null(void **arr, int count);
void	free_split(char **split);
int		cmds_len(char ***arr);
int		is_made_of(char *input, char *accepted);
int		arr_len(char **arr);

void	fill_null(void **arr, int count)
{
	while (count--)
		arr[count] = NULL;
}

void	free_split(char **split)
{
	int	i;

	if (split == NULL)
		return ;
	i = 0;
	while (split[i])
	{
		free (split[i]);
		i++;
	}
	free (split);
}

int	cmds_len(char ***arr)
{
	int	len;

	len = -1;
	while (arr[++len])
		;
	return (len);
}

int	is_made_of(char *input, char *accepted)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (!ft_strchr(accepted, input[i]))
			return (0);
	}
	return (1);
}

int	arr_len(char **arr)
{
	int	len;

	len = -1;
	while (arr[++len])
		;
	return (len);
}
