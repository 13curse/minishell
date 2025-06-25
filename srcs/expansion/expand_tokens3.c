/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 19:22:46 by van               #+#    #+#             */
/*   Updated: 2025/06/08 19:44:17 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cpy_var(t_minishell *shell, char **token, char **new, t_cpy_exp *v);

void	cpy_exp_match_quote(char *quote, char **tkn, char **new, t_cpy_exp *v)
{
	if (*quote == 0)
		*quote = **tkn;
	else if (*quote == **tkn)
		*quote = 0;
	else
		add_uninterpreted(v->shell, v->i, v->l);
	**new = **tkn;
	(*tkn)++;
	v->l++;
	(*new)++;
}

void	cpy_expand_match_dollar(char **new, char **token, t_cpy_exp *v)
{
	**new = **token;
	(*token)++;
	v->l++;
	(*new)++;
}

void	cpy_expand_else_quote(char **new, char **token, t_cpy_exp *v)
{
	**new = **token;
	(*token)++;
	v->l++;
	(*new)++;
}

int	cpy_expand(t_minishell *shell, char *token, char *new, int i)
{
	char		quote;
	t_cpy_exp	v;

	v.i = i;
	v.shell = shell;
	quote = 0;
	v.l = 0;
	while (*token)
	{
		if (*token == '\'' || *token == '"')
			cpy_exp_match_quote(&quote, &token, &new, &v);
		else if (quote != '\'' && *token != '$')
			cpy_expand_match_dollar(&new, &token, &v);
		else if (quote != '\'' && *token == '$')
		{
			if (cpy_var(shell, &token, &new, &v))
				return (1);
		}
		else if (quote)
			cpy_expand_else_quote(&new, &token, &v);
	}
	*new = '\0';
	return (0);
}
