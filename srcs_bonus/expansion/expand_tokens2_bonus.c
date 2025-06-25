/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:45:08 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:25:47 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	var_expanded_len(t_minishell *shell, char *cmd);
int	cpy_expand(t_minishell *shell, char *cmd, char *new, int i);

int	ftft(t_minishell *shell, t_ev *v, char **cmd)
{
	int	k;

	shell->uninterpreted[v->i] = malloc (sizeof(int) * MAX_UNINTERPRETED + 1);
	if (shell->uninterpreted[v->i] == NULL)
		return (err_malloc(1));
	k = -1;
	while (++k < MAX_UNINTERPRETED)
		shell->uninterpreted[v->i][k] = -1;
	v->token = cmd[++v->i];
	return (0);
}

int	ev_handle_len_spc_val(t_minishell *shell, t_ev *v, char **cmd)
{
	if (v->len == -1)
		kill_shell(shell);
	if (v->len == -2)
	{
		if (ftft(shell, v, cmd))
			return (1);
		return (-1);
	}
	if (v->len == 0)
	{
		free (v->token);
		v->j = v->i - 1;
		while (cmd[++v->j])
			cmd[v->j] = cmd[v->j + 1];
		v->token = cmd[v->i];
		return (-1);
	}
	return (0);
}

int	ev_alloc(t_minishell *shell, t_ev *v)
{
	v->new = malloc(sizeof(char) * (v->len + 1));
	if (v->new == NULL)
	{
		free_shell(shell);
		return (err_malloc(1));
	}
	v->new[v->len] = '\0';
	shell->uninterpreted[v->i] = malloc(sizeof(int) * (MAX_UNINTERPRETED + 1));
	if (shell->uninterpreted[v->i] == NULL)
	{
		free (v->new);
		free_shell(shell);
		return (err_malloc(1));
	}
	set_uninterpreted(shell, v->i);
	if (cpy_expand(shell, v->token, v->new, v->i))
	{
		free(v->new);
		free_shell(shell);
		exit (0);
	}
	return (0);
}

int	expand_vars(t_minishell *shell, char **cmd)
{
	t_ev	v;

	if (alloc_uninterpreted(shell, cmd))
	{
		free_shell(shell);
		return (1);
	}
	v.token = cmd[0];
	v.i = 0;
	while (v.token)
	{
		v.len = var_expanded_len(shell, v.token);
		v.ret = ev_handle_len_spc_val(shell, &v, cmd);
		if (v.ret == -1)
			continue ;
		else if (v.ret)
			return (v.ret);
		if (ev_alloc(shell, &v))
			return (1);
		free(cmd[v.i]);
		cmd[v.i] = v.new;
		v.token = cmd[++v.i];
	}
	return (0);
}
