/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 19:44:36 by van               #+#    #+#             */
/*   Updated: 2025/06/08 19:57:11 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_var_len(t_minishell *shell, char **token, int *len);

void	vel_quote(char *quote, char **token, int *len)
{
	if (*quote == 0)
		*quote = **token;
	else if (*quote == **token)
		*quote = 0;
	(*len)++;
	(*token)++;
}

void	vel_inc_len_and_tkn(int *len, char **token)
{
	(*len)++;
	(*token)++;
}

int	vel_dollar(t_minishell *shell, char **token, int *len, int *expand)
{
	if (ft_isalnum((*token)[1]) || ft_strchr("_?'\"", (*token)[1]))
		*expand = 1;
	if (add_var_len(shell, token, len))
		return (-1);
	return (0);
}

int	var_expanded_len(t_minishell *shell, char *token)
{
	int		len;
	char	quote;
	int		expand;

	expand = 0;
	len = 0;
	quote = 0;
	while (*token)
	{
		if (*token == '\'' || *token == '"')
			vel_quote(&quote, &token, &len);
		else if (quote != '\'' && *token != '$')
			vel_inc_len_and_tkn(&len, &token);
		else if (quote != '\'' && *token == '$')
		{
			if (vel_dollar(shell, &token, &len, &expand))
				return (-1);
		}
		else if (quote)
			vel_inc_len_and_tkn(&len, &token);
	}
	if (len && !expand)
		return (-2);
	return (len);
}
