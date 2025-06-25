/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:57:17 by van               #+#    #+#             */
/*   Updated: 2025/06/08 16:57:44 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	note_uninterpreted(int *uninterpreted, char *expanded_tkn, int i)
{
	int	j;
	int	k;

	j = -1;
	while (++j < MAX_UNINTERPRETED && uninterpreted[j] != -1)
		;
	if (j == MAX_UNINTERPRETED)
	{
		ft_printf(2, "Too many uninterpreted characters\n");
		return (1);
	}
	k = 0;
	while (expanded_tkn && expanded_tkn[k])
	{
		if (expanded_tkn[k] && ft_strchr("'\"$", expanded_tkn[k]))
			uninterpreted[j++] = i + k;
		if (j == MAX_UNINTERPRETED + 1)
		{
			ft_printf(2, "Too many uninterpreted characters\n");
			return (1);
		}
		k++;
	}
	return (0);
}

void	fill_exp_match_quote(int *quote, t_fet_params *fet_p)
{
	if (*quote == *(fet_p->tkn))
		*quote = 0;
	else if (*quote == 0)
		*quote = *(fet_p->tkn);
	*(fet_p->exp_tkn)++ = *(fet_p->tkn)++;
	(fet_p->i)++;
}

int	fill_exp_match_dollar(t_minishell *shell, t_fet_params *fet_p)
{
	if (*((fet_p->tkn) + 1) == '?')
	{
		(fet_p->var) = get_status(shell);
		if ((fet_p->var) == NULL)
			return (1);
		(fet_p->len) = ft_strlen((fet_p->var));
		ft_strlcpy((fet_p->exp_tkn), (fet_p->var), (fet_p->len) + 1);
		(fet_p->exp_tkn) += (fet_p->len);
		(fet_p->i) += (fet_p->len);
		(fet_p->tkn) += 2;
		free((fet_p->var));
	}
	else
	{
		(fet_p->var) = get_var(shell, &(fet_p->tkn));
		if ((fet_p->var) == NULL)
			return (1);
		(fet_p->len) = ft_strlen((fet_p->var));
		ft_strlcpy((fet_p->exp_tkn), (fet_p->var), (fet_p->len) + 1);
		if (note_uninterpreted((fet_p->unint), (fet_p->exp_tkn), (fet_p->i)))
			return (1);
		(fet_p->exp_tkn) += (fet_p->len);
		(fet_p->i) += (fet_p->len);
	}
	return (0);
}

int	fill_expanded_tkn(t_minishell *shell, char *exp_tkn, char *tkn, int *unint)
{
	int				quote;
	t_fet_params	fet_p;

	fet_p.i = 0;
	fet_p.exp_tkn = exp_tkn;
	fet_p.tkn = tkn;
	fet_p.unint = unint;
	quote = 0;
	while (*(fet_p.tkn))
	{
		if (*(fet_p.tkn) == '"' || *(fet_p.tkn) == '\'')
			fill_exp_match_quote(&quote, &fet_p);
		else if (quote != '\'' && *(fet_p.tkn) == '$')
		{
			if (fill_exp_match_dollar(shell, &fet_p))
				return (1);
		}
		else
		{
			(fet_p.i)++;
			*(fet_p.exp_tkn)++ = *(fet_p.tkn)++;
		}
	}
	*(fet_p.exp_tkn) = '\0';
	return (0);
}
