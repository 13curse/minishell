/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:07:08 by van               #+#    #+#             */
/*   Updated: 2025/06/07 18:35:15 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(char c);
int	skip_space(char **input);
int	reach_next_quote(char **input);

int	ft_isspace(char c)
{
	return (c == ' ' || (9 <= c && c <= 12));
}

//	modify the str ptr until it reach a non white space char
//		ret 1 if ptr has been changed
int	skip_space(char **input)
{
	int	ret;

	ret = 0;
	while (**input && ft_isspace(**input))
	{
		if (!ret)
			ret = 1;
		(*input)++;
	}
	return (ret);
}

//	modify the str ptr until it found the next occurence of the first char
//		ret 1 if not found
int	reach_next_quote(char **input)
{
	char	quote;

	quote = **input;
	(*input)++;
	while (**input)
	{
		if (**input == quote)
			return (0);
		(*input)++;
	}
	return (1);
}
