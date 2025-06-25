/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:50:33 by van               #+#    #+#             */
/*   Updated: 2025/06/08 18:01:08 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		proceed_expand(int *j, t_exp_tkn *e);
void	init_uninterpreted(int *uninterpreted, int size);
int		fill_expanded_tkn(t_minishell *shell, char *exp_tkn, char *tkn, int *u);

void	abort_expand_token(t_minishell *shell, char **new, int call_err_malloc)
{
	free(new);
	if (call_err_malloc)
		err_malloc(1);
	kill_shell(shell);
}

void	set_exp_tkn(t_exp_tkn *e, char **new, char *token, t_minishell *shell)
{
	e->tkn = token;
	e->new = new;
	e->shell = shell;
}

int	expand_token(t_minishell *shell, char **new, char *token, int *j)
{
	int			len;
	t_exp_tkn	e_tkn;

	set_exp_tkn(&e_tkn, new, token, shell);
	len = var_expanded_len(shell, e_tkn.tkn);
	if (len == -1)
		abort_expand_token(shell, new, 0);
	if (len == -2)
	{
		new[(*j)++] = e_tkn.tkn;
		return (0);
	}
	e_tkn.expd_tkn = malloc(sizeof(char) * (len + 1));
	ft_memset(e_tkn.expd_tkn, '\0', len + 1);
	if (e_tkn.expd_tkn == NULL)
		abort_expand_token(shell, new, 1);
	init_uninterpreted(e_tkn.unint, 256);
	if (len && fill_expanded_tkn(shell, e_tkn.expd_tkn, e_tkn.tkn, e_tkn.unint))
		abort_expand_token(shell, new, 0);
	free(e_tkn.tkn);
	if (len && proceed_expand(j, &e_tkn))
		abort_expand_token(shell, new, 0);
	free(e_tkn.expd_tkn);
	return (0);
}

int	expand_vars(t_minishell *shell, char **new)
{
	char	*token;
	int		i;
	int		j;

	i = 0;
	j = 0;
	token = shell->cmds[shell->cmd_id - 1][0];
	while (token)
	{
		if (!ft_strchr(token, '$'))
			new[j++] = token;
		else
			expand_token(shell, new, token, &j);
		token = shell->cmds[shell->cmd_id - 1][++i];
	}
	return (0);
}
