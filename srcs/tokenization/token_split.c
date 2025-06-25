/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:21:32 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/07 17:21:32 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "tokenization.h"

char		**split_tokens(char *input);
static int	count_split_quote(char **input);
static int	count_split_inner(char **input, int *new, t_operators *operators);
int			count_split(char *input, t_operators *operators);
int			is_op(char *input, t_operators *operators);

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

static int	count_split_quote(char **input)
{
	if (**input == '\'' || **input == '"')
		if (reach_next_quote(input))
			return (err_unclosed_quote());
	return (0);
}

static int	count_split_inner(char **input, int *new, t_operators *operators)
{
	int	count;

	count = 0;
	while (**input && !ft_isspace(**input) && !is_op(*input, operators))
	{
		if (count_split_quote(input))
			return (-1);
		(*input)++;
		if (new)
		{
			count += *new;
			*new = 0;
		}
	}
	return (count);
}

//	ret the number of tokens in input
int	count_split(char *input, t_operators *operators)
{
	int	count;
	int	new;
	int	ret;

	if (input == NULL || *input == '\0')
		return (0);
	count = 0;
	new = 1;
	while (*input)
	{
		if (skip_space(&input))
			new = 1;
		ret = count_split_inner(&input, &new, operators);
		if (ret == -1)
			return (err_unclosed_quote());
		count += ret;
		if (is_op(input, operators))
		{
			input += is_op(input, operators);
			count++;
			new = 1;
		}
	}
	return (count);
}

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
