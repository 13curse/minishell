/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:22:44 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/07 17:22:44 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "tokenization.h"

int		alloc_and_copy_token(char ***tokens, int *i, char *input, int len);
int		handle_operator(t_token *data, char ***tokens, int *i,
			t_operators *operators);
int		handle_data(t_token *data, char ***tokens, int *i);
void	init_token_data(t_token *data, char **input, int *len, int *quote);
int		handle_end(char ***tokens, int *i, char *input, int len);

int	alloc_and_copy_token(char ***tokens, int *i, char *input, int len)
{
	(*tokens)[*i] = malloc(sizeof(char) * (len + 1));
	if ((*tokens)[*i] == NULL)
	{
		free_split(*tokens);
		return (err_malloc(1));
	}
	ft_strlcpy((*tokens)[(*i)++], input, len + 1);
	return (0);
}

int	handle_operator(t_token *data, char ***tokens, int *i,
		t_operators *operators)
{
	if (*(data->len))
	{
		if (alloc_and_copy_token(tokens, i, *(data->input), *(data->len)))
			return (1);
		*(data->input) += *(data->len);
		*(data->len) = 0;
	}
	if (alloc_and_copy_token(tokens, i, *(data->input),
			is_op(*(data->input), operators)))
		return (1);
	*(data->input) += is_op(*(data->input), operators);
	return (0);
}

int	handle_data(t_token *data, char ***tokens, int *i)
{
	if (!*(data->len))
	{
		if (**(data->input))
			(*(data->input))++;
		return (0);
	}
	if (alloc_and_copy_token(tokens, i, *(data->input), *(data->len)))
		return (1);
	*(data->input) += *(data->len);
	*(data->len) = 0;
	return (0);
}

void	init_token_data(t_token *data, char **input, int *len, int *quote)
{
	data->input = input;
	data->len = len;
	data->quote = quote;
}

int	handle_end(char ***tokens, int *i, char *input, int len)
{
	if (len)
	{
		if (alloc_and_copy_token(tokens, i, input, len))
			return (1);
	}
	return (0);
}
