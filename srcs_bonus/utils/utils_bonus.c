/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:40:54 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:21:24 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

//	ret len of matched operator
int	is_op(char *input, t_operators *operators)
{
	int	shift;

	if (!ft_strncmp(input, operators->and, 2))
		return (2);
	if (!ft_strncmp(input, operators->or, 2))
		return (2);
	if (!ft_strncmp(input, operators->pipe, 1))
		return (1);
	shift = 0;
	if (!ft_strncmp(input + shift, operators->heredoc, 2))
		return (2 + shift);
	if (!ft_strncmp(input + shift, operators->append, 2))
		return (2 + shift);
	if (!ft_strncmp(input + shift, operators->redir_in, 1))
		return (1 + shift);
	if (!ft_strncmp(input + shift, operators->redir_out, 1))
		return (1 + shift);
	return (0);
}

// set the count last element of an array to NULL
void	fill_null(void **arr, int count)
{
	while (count--)
		arr[count] = NULL;
}

// ret the number of elements of arr
// must be NULL terminated
int	cmds_len(char ***arr)
{
	int	len;

	len = -1;
	while (arr[++len])
		;
	return (len);
}

// if input is made of accepted chars ret 1, else 0
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

int	arr_len(void **arr)
{
	int	len;

	len = -1;
	while (arr[++len])
		;
	return (len);
}
