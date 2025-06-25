/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:16:31 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/12 22:16:31 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static int	parse_tokens_start(char **tokens)
{
	if (!ft_strncmp(tokens[0], "|", 2) || !ft_strncmp(tokens[0], "||", 3)
		|| !ft_strncmp(tokens[0], "&&", 3))
	{
		write(2, "syntax error near unexpected token '|'\n", 39);
		write(2, tokens[0], ft_strlen(tokens[0]));
		write(2, "\n", 1);
		free_split(tokens);
		return (1);
	}
	return (0);
}

static int	parse_tokens_middle(t_minishell *shell, char **tokens)
{
	int	i;

	i = 0;
	while (tokens[++i])
	{
		if ((!ft_strncmp(tokens[i], "|", 2) || !ft_strncmp(tokens[i], "||", 3)
				|| !ft_strncmp(tokens[i], "&&", 3))
			&& (is_op(tokens[i - 1], shell->op)))
		{
			write(2, "syntax error near unexpected token '", 36);
			write(2, tokens[i], ft_strlen(tokens[i]));
			write(2, "'\n", 2);
			free_split(tokens);
			return (1);
		}
	}
	return (0);
}

static int	parse_tokens_end(t_minishell *shell, char **tokens, int i)
{
	if (is_op(tokens[i - 1], shell->op))
	{
		write(2, "syntax error near unexpected token '", 36);
		write(2, tokens[i - 1], ft_strlen(tokens[i - 1]));
		write(2, "'\n", 2);
		free_split(tokens);
		return (1);
	}
	return (0);
}

int	parse_tokens(t_minishell *shell, char **tokens)
{
	int	i;

	i = 0;
	if (tokens == NULL || *tokens == NULL)
		return (0);
	if (parse_tokens_start(tokens))
		return (1);
	if (parse_tokens_middle(shell, tokens))
		return (1);
	while (tokens[++i])
		;
	if (parse_tokens_end(shell, tokens, i))
		return (1);
	return (0);
}
