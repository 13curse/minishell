/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:07:33 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:22:52 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	fta_while_quote(t_fta *v);

int	fta_while_op(t_fta *v)
{
	if (v->len)
	{
		(*v->tokens)[v->i] = malloc(sizeof(char) * (v->len + 1));
		if ((*v->tokens)[v->i] == NULL)
		{
			free_split(*v->tokens);
			return (err_malloc(1));
		}
		ft_strlcpy((*v->tokens)[v->i++], v->input, v->len + 1);
		v->input += v->len;
		v->len = 0;
	}
	(*v->tokens)[v->i] = malloc(sizeof(char) * (is_op(v->input, v->op) + 1));
	if ((*v->tokens)[v->i] == NULL)
	{
		free_split(*v->tokens);
		return (err_malloc(1));
	}
	ft_strlcpy((*v->tokens)[v->i++], v->input, is_op(v->input, v->op) + 1);
	v->input += is_op(v->input, v->op);
	return (0);
}

void	fta_while_match_quote(t_fta *v)
{
	v->quote = v->input[v->len];
	v->len++;
}

int	fta_while_wspc(t_fta *v)
{
	if (!v->len)
	{
		if (*v->input)
			v->input++;
		return (-1);
	}
	(*v->tokens)[v->i] = malloc(sizeof(char) * (v->len + 1));
	if ((*v->tokens)[v->i] == NULL)
	{
		free_split(*v->tokens);
		return (err_malloc(1));
	}
	ft_strlcpy((*v->tokens)[v->i++], v->input, v->len + 1);
	v->input += v->len;
	v->len = 0;
	return (0);
}

int	fta_while(t_fta *v)
{
	while (v->input[v->len])
	{
		if (v->quote)
			fta_while_quote(v);
		else if (is_op(v->input + v->len, v->op))
		{
			v->ret = fta_while_op(v);
			if (v->ret)
				return (v->ret);
		}
		else if (ft_strchr("'\"", v->input[v->len]))
			fta_while_match_quote(v);
		else if (ft_isspace(v->input[v->len]))
		{
			v->ret = fta_while_wspc(v);
			if (v->ret == -1)
				continue ;
			else if (v->ret)
				return (v->ret);
		}
		else
			v->len++;
	}
	return (0);
}

int	fill_tokens_arr(char *input, char ***tokens, t_operators *operators)
{
	t_fta	v;

	v.i = 0;
	v.quote = 0;
	v.len = 0;
	v.input = input;
	v.tokens = tokens;
	v.op = operators;
	v.ret = fta_while(&v);
	if (v.ret)
		return (v.ret);
	if (v.len)
	{
		(*v.tokens)[v.i] = malloc(sizeof(char) * (v.len + 1));
		if ((*v.tokens)[v.i] == NULL)
		{
			free_split(*v.tokens);
			return (err_malloc(1));
		}
		ft_strlcpy((*v.tokens)[v.i++], v.input, v.len + 1);
	}
	return (0);
}
