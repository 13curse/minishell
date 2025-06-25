/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:31:03 by van-nguy          #+#    #+#             */
/*   Updated: 2025/06/07 17:32:46 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "tokenization.h"

static int	handle_quote(int *quote, char c);
static int	token_loop(t_token *data, char ***tokens,
				int *i, t_operators *operators);
int			fill_tokens_arr(char *input, char ***tokens,
				t_operators *operators);

static int	handle_quote(int *quote, char c)
{
	if (*quote)
	{
		if (c == *quote)
			*quote = 0;
		return (1);
	}
	if (ft_strchr("'\"", c))
	{
		*quote = c;
		return (1);
	}
	return (0);
}

static int	token_loop(t_token *data, char ***tokens,
		int *i, t_operators *operators)
{
	while ((*(*data).input)[*(*data).len])
	{
		if (handle_quote(data->quote, (*(*data).input)[*(*data).len]))
		{
			(*(*data).len)++;
			continue ;
		}
		if (is_op((*(*data).input) + *(*data).len, operators))
		{
			if (handle_operator(data, tokens, i, operators))
				return (1);
		}
		else if (ft_isspace((*(*data).input)[*(*data).len]))
		{
			if (handle_data(data, tokens, i))
				return (1);
		}
		else
			(*(*data).len)++;
	}
	return (0);
}

int	fill_tokens_arr(char *input, char ***tokens, t_operators *operators)
{
	int		i;
	int		quote;
	int		len;
	t_token	data;

	i = 0;
	quote = 0;
	len = 0;
	init_token_data(&data, &input, &len, &quote);
	if (token_loop(&data, tokens, &i, operators))
		return (1);
	return (handle_end(tokens, &i, input, len));
}

// int	fill_tokens_arr(char *input, char ***tokens, t_operators *operators)
// {
// 	int	i;
// 	int	quote;
// 	int	len;

// 	i = 0;
// 	quote = 0;
// 	len = 0;
// 	while (input[len])
// 	{
// 		if (quote)
// 		{
// 			if (input[len] == quote)
// 				quote = 0;
// 			len++;
// 		}
// 		else if (is_op(input + len, operators))
// 		{
// 			if (len)
// 			{
// 				(*tokens)[i] = malloc(sizeof(char) * (len + 1));
// 				if ((*tokens)[i] == NULL)
// 				{
// 					free_split(*tokens);
// 					return (err_malloc(1));
// 				}
// 				ft_strlcpy((*tokens)[i++], input, len + 1);
// 				input += len;
// 				len = 0;
// 			}
// 			(*tokens)[i] = malloc(sizeof(char) * (is_op(input, operators) + 1));
// 			if ((*tokens)[i] == NULL)
// 			{
// 				free_split(*tokens);
// 				return (err_malloc(1));
// 			}
// 			ft_strlcpy((*tokens)[i++], input, is_op(input, operators) + 1);
// 			input += is_op(input, operators);
// 		}
// 		else if (ft_strchr("'\"", input[len]))
// 		{
// 			quote = input[len];
// 			len++;
// 		}
// 		else if (ft_isspace(input[len]))
// 		{
// 			if (!len)
// 			{
// 				if (*input)
// 					input++;
// 				continue ;
// 			}
// 			(*tokens)[i] = malloc(sizeof(char) * (len + 1));
// 			if ((*tokens)[i] == NULL)
// 			{
// 				free_split(*tokens);
// 				return (err_malloc(1));
// 			}
// 			ft_strlcpy((*tokens)[i++], input, len + 1);
// 			input += len;
// 			len = 0;
// 		}
// 		else
// 			len++;
// 	}
// 	if (len)
// 	{
// 		(*tokens)[i] = malloc(sizeof(char) * (len + 1));
// 		if ((*tokens)[i] == NULL)
// 		{
// 			free_split(*tokens);
// 			return (err_malloc(1));
// 		}
// 		ft_strlcpy((*tokens)[i++], input, len + 1);
// 	}
// 	return (0);
// }
