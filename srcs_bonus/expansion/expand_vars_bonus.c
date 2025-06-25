/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:57:17 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:25:34 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	fill_exp_match_dollar(t_minishell *shell, t_fet_params *fet_p, int *quote);

int	note_uninterpreted(int *uninterpreted, char *expanded_tkn,
	int i, int *quote)
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
		if (ft_strchr("'\"", expanded_tkn[k])
			|| (*quote == '\'' && expanded_tkn[k] == '$'))
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
			if (fill_exp_match_dollar(shell, &fet_p, &quote))
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

void	print_uninterpreted(t_minishell *shell)
{
	int	i;
	int	j;

	i = -1;
	printf("---uninterpreted---\n");
	while (shell->uninterpreted[++i])
	{
		printf("%d:\t", i);
		if (shell->uninterpreted[i])
		{
			printf("\n");
			j = -1;
			while (shell->uninterpreted[i][++j] != -1)
				printf("\t%d: %d\n", j, shell->uninterpreted[i][j]);
			printf("\t%d: %d\n", j, -1);
		}
		else
			printf("%ls\n", shell->uninterpreted[i]);
	}
}
