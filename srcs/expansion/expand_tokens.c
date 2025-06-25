/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:12:05 by van               #+#    #+#             */
/*   Updated: 2025/06/10 19:06:28 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	var_expanded_len(t_minishell *shell, char *cmd);
int	cpy_expand(t_minishell *shell, char *cmd, char *new, int i);

int	is_dollar_to_be_printed(char *token);

void	increment_l_and_i(t_exp_quotes *v)
{
	v->i++;
	v->l++;
}

void	idk_what_to_name_it(t_exp_quotes *v)
{
	v->change = 1;
	v->shift = 2;
	v->rem = v->i;
}

void	expand_quotes_inner_while(t_minishell *sh, t_exp_quotes *v, char **cmd)
{
	while ((*cmd)[v->rem])
	{
		v->i = v->rem;
		v->l = v->rem;
		while (((*cmd)[v->i] && !ft_strchr("'\"", (*cmd)[v->i]))
			|| !is_interpreted(sh, v->ign_i, v->l))
			increment_l_and_i(v);
		if ((*cmd)[v->i] == '\0')
			break ;
		v->quote = (*cmd)[v->i];
		v->shift = 1;
		while ((*cmd)[v->i])
		{
			v->change = 0;
			if (v->shift == 1 && (*cmd)[v->i + v->shift] == v->quote
				&& is_interpreted(sh, v->ign_i, v->l))
				idk_what_to_name_it(v);
			(*cmd)[v->i] = (*cmd)[v->i + v->shift];
			update_uninterpreted(sh, v->ign_i, v->l, v->shift - v->change);
			if ((*cmd)[v->i] == '\0')
				break ;
			increment_l_and_i(v);
		}
	}
}

void	expand_quotes(t_minishell *shell)
{
	char			**cmd;
	t_exp_quotes	v;

	cmd = shell->cmds[shell->cmd_id - 1] - 1;
	v.ign_i = -1;
	while ((*++cmd))
	{
		v.ign_i++;
		v.l = 0;
		v.rem = 0;
		expand_quotes_inner_while(shell, &v, cmd);
	}
}
