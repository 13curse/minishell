/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 16:43:39 by van               #+#    #+#             */
/*   Updated: 2025/06/08 18:00:29 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_interpreted2(int *uninterpreted, int len);

int	mark_uninterpreted(char *token, int *uninterpreted, int *unint)
{
	int	i;
	int	j;

	j = -1;
	while (++j < MAX_UNINTERPRETED && uninterpreted[j] != -1)
		;
	if (j == MAX_UNINTERPRETED)
		return (1);
	i = -1;
	while (token[++i])
	{
		if (ft_strchr("'\"$", token[i]) && !is_interpreted2(unint, i))
			uninterpreted[j++] = i;
		if (j == MAX_UNINTERPRETED + 1)
		{
			ft_printf(2, "MAX_INTERPRETED chars reached\n");
			return (1);
		}
	}
	return (0);
}

void	abort_set_token(t_exp_tkn *exp_tkn)
{
	free_split(exp_tkn->new);
	free_shell(exp_tkn->shell);
	exit (err_malloc(1));
}

int	set_token(char **expanded_tkn, int *len, int *j, t_exp_tkn *e)
{
	if (*len == 0)
	{
		(*expanded_tkn)++;
		return (0);
	}
	e->shell->uninterpreted[*j] = malloc(sizeof(int) * (MAX_UNINTERPRETED + 1));
	if (e->shell->uninterpreted[*j] == NULL)
		abort_set_token(e);
	set_uninterpreted(e->shell, *j);
	e->new[*j] = malloc(sizeof(char) * (*len + 1));
	if (e->new[*j] == NULL)
		abort_set_token(e);
	ft_strlcpy(e->new[*j], *expanded_tkn, *len + 1);
	if (mark_uninterpreted(e->new[*j], e->shell->uninterpreted[*j], e->unint))
		return (1);
	(*expanded_tkn) += *len;
	(*j)++;
	*len = 0;
	while (ft_isspace(**expanded_tkn))
		(*expanded_tkn)++;
	return (0);
}

int	proceed_expand(int *j, t_exp_tkn *e)
{
	int		l;
	int		quote;
	char	*expd;

	expd = e->expd_tkn;
	quote = 0;
	l = 0;
	while (expd[l])
	{
		if (is_interpreted2(e->unint, l) && (expd[l] == '"' || expd[l] == '\''))
		{
			if (quote == expd[l])
				quote = 0;
			else if (quote == 0)
				quote = expd[l];
			l++;
		}
		else if (!quote && ft_isspace(expd[l]))
			set_token(&expd, &l, j, e);
		else
			l++;
	}
	if (l)
		set_token(&expd, &l, j, e);
	return (0);
}

void	init_uninterpreted(int *uninterpreted, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		uninterpreted[i] = -1;
}
