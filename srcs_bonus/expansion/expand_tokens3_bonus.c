/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens3_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:27:46 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:25:42 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	avl_while(t_minishell *shell, int *len, char **token, char *quote);
int	cpy_expand(t_minishell *shell, char *token, char *new, int i);
int	add_var_len(t_minishell *shell, char **token, int *len);
int	cpy_var(t_expand *data);
int	note_uninterpreted(int *uninterpreted, char *expanded_tkn,
		int i, int *quote);

int	var_expanded_len(t_minishell *shell, char *token)
{
	int		len;
	char	quote;
	int		expand;

	expand = 0;
	len = 0;
	quote = 0;
	expand = avl_while(shell, &len, &token, &quote);
	if (expand == -1)
		return (-1);
	if (len == 0)
		return (0);
	if (!expand)
		return (-2);
	return (len);
}

int	fill_exp_status(t_minishell *shell, t_fet_params *fet_p)
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
	return (0);
}

int	fill_exp_var(t_minishell *shell, t_fet_params *fet_p, int *quote)
{
	(fet_p->var) = get_var(shell, &(fet_p->tkn));
	if ((fet_p->var) == NULL)
		return (1);
	(fet_p->len) = ft_strlen((fet_p->var));
	ft_strlcpy((fet_p->exp_tkn), (fet_p->var),
		(fet_p->len) + 1);
	if (note_uninterpreted((fet_p->unint),
			(fet_p->exp_tkn), (fet_p->i), quote))
		return (1);
	(fet_p->exp_tkn) += (fet_p->len);
	(fet_p->i) += (fet_p->len);
	return (0);
}

int	fill_exp_match_dollar(t_minishell *shell, t_fet_params *fet_p, int *quote)
{
	if (*((fet_p->tkn) + 1) == '?')
		return (fill_exp_status(shell, fet_p));
	else
		return (fill_exp_var(shell, fet_p, quote));
}
