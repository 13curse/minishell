/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:31:03 by van-nguy          #+#    #+#             */
/*   Updated: 2025/06/13 11:22:48 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	fill_tokens_arr(char *input, char ***tokens, t_operators *operators);
int	count_split(char *input, t_operators *operators);
int	reach_next_quote(char **input);

char	**split_tokens(char *input)
{
	t_operators	operators;
	int			count;
	char		**tokens;
	int			i;

	if (input == NULL)
		return (NULL);
	init_operators(&operators);
	count = count_split(input, &operators);
	if (count < 0)
		return (NULL);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (tokens == NULL)
		return (NULL);
	i = -1;
	while (++i <= count)
		tokens[i] = NULL;
	if (fill_tokens_arr(input, &tokens, &operators))
		return (NULL);
	return (tokens);
}

void	count_split_op(char **input, int *new, int *count, t_operators *op)
{
	*input += is_op(*input, op);
	(*count)++;
	*new = 1;
}

//	ret the number of tokens in input
int	count_split(char *input, t_operators *operators)
{
	int			count;
	int			new;

	if (input == NULL || *input == '\0')
		return (0);
	count = 0;
	new = 1;
	while (*input)
	{
		if (skip_space(&input))
			new = 1;
		while (*input && !ft_isspace(*input) && !is_op(input, operators))
		{
			if (*input == '\'' || *input == '"')
				if (reach_next_quote(&input))
					return (err_unclosed_quote());
			input++;
			if (new)
				count += new--;
		}
		if (is_op(input, operators))
			count_split_op(&input, &new, &count, operators);
	}
	return (count);
}

void	fta_while_quote(t_fta *v)
{
	if (v->input[v->len] == v->quote)
		v->quote = 0;
	v->len++;
}
