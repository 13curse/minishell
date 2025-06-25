/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:12:05 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:25:59 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	add_var_len(t_minishell *shell, char **token, int *len);
int	var_expanded_len(t_minishell *shell, char *cmd);
int	cpy_expand(t_minishell *shell, char *cmd, char *new, int i);

void	eq_inner_while(t_minishell *shell, t_eq *v, char **cmd)
{
	while ((*cmd)[v->i])
	{
		if (v->shift == 1 && (*cmd)[v->i + v->shift]
			== v->quote && is_interpreted(shell, v->ign_i, v->l))
		{
			v->shift = 2;
			v->rem = v->i;
		}
		(*cmd)[v->i] = (*cmd)[v->i + v->shift];
		update_uninterpreted(shell, v->ign_i, v->l, v->shift);
		if ((*cmd)[v->i] == '\0')
			break ;
		v->i++;
		v->l++;
	}
}

void	expand_quotes(t_minishell *shell, char **cmd)
{
	t_eq	v;

	v.ign_i = -1;
	while ((*++cmd))
	{
		v.ign_i++;
		v.l = 0;
		v.rem = 0;
		while ((*cmd)[v.rem])
		{
			v.i = v.rem;
			v.l = v.rem;
			while (((*cmd)[v.i] && !ft_strchr("'\"", (*cmd)[v.i]))
				|| !is_interpreted(shell, v.ign_i, v.l))
			{
				v.i++;
				v.l++;
			}
			if ((*cmd)[v.i] == '\0')
				break ;
			v.quote = (*cmd)[v.i];
			v.shift = 1;
			eq_inner_while(shell, &v, cmd);
		}
	}
}

void	avl_quote(char *quote, int *len, char **token)
{
	if (*quote == 0)
		*quote = **token;
	else if (*quote == **token)
		*quote = 0;
	(*len)++;
	(*token)++;
}

void	inc_len_and_token(int *len, char **token)
{
	(*len)++;
	(*token)++;
}

int	avl_while(t_minishell *shell, int *len, char **token, char *quote)
{
	int	expand;

	expand = 0;
	while (**token)
	{
		if (**token == '\'' || **token == '"')
			avl_quote(quote, len, token);
		else if (*quote != '\'' && **token != '$')
			inc_len_and_token(len, token);
		else if (*quote != '\'' && **token == '$')
		{
			if (ft_isalnum((*token)[1]) || ft_strchr("_?\"", (*token)[1]))
				expand = 1;
			if (add_var_len(shell, token, len))
				return (-1);
		}
		else if (*quote)
			inc_len_and_token(len, token);
	}
	return (expand);
}
