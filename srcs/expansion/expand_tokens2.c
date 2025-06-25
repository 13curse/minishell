/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:33:49 by van               #+#    #+#             */
/*   Updated: 2025/06/08 19:22:26 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cpy_var_status(t_minishell *shell, char **new, char **token, t_cpy_exp *v)
{
	char	*var;
	int		i;

	var = ft_itoa(shell->status);
	if (var == NULL)
		return (1);
	i = -1;
	while (var[++i])
	{
		if (ft_strchr("'\"$", var[i]))
			add_uninterpreted(shell, v->i, v->l);
		**new = var[i];
		(*new)++;
		(v->l)++;
	}
	free (var);
	(*token)++;
	return (0);
}

int	cpy_var_i_0(char **new, char **token, t_cpy_exp *v)
{
	if (is_dollar_to_be_printed(*token))
	{
		**new = '$';
		(*new)++;
		(v->l)++;
	}
	return (0);
}

int	cpy_var_get_var(t_minishell *shell, char *var_name, char **var)
{
	if (!ft_strncmp(var_name, "?", 2))
	{
		*var = ft_itoa(shell->status);
		if (*var == NULL)
			return (1);
	}
	else
	{
		*var = get_env_value(shell, var_name);
		if (*var == NULL)
			return (0);
	}
	return (0);
}

void	cpy_var_cpy(t_minishell *shell, char *var, char **new, t_cpy_exp *v)
{
	int	i;

	i = -1;
	while (var[++i])
	{
		if (ft_strchr("'\"$", var[i]))
			add_uninterpreted(shell, v->i, v->l);
		**new = var[i];
		(*new)++;
		(v->l)++;
	}
}

int	cpy_var(t_minishell *shell, char **token, char **new, t_cpy_exp *v)
{
	char	var_name[256];
	int		i;
	char	*var;

	i = -1;
	(*token)++;
	if (**token == '?')
		return (cpy_var_status(shell, new, token, v));
	while ((*token)[++i] && (ft_isalnum((*token)[i])
		|| (*token)[i] == '_') && i < 256)
		var_name[i] = (*token)[i];
	if (i == 256)
	{
		write(2, "the name of the variable to be expanded is too long\n", 52);
		return (1);
	}
	if (i == 0)
		return (cpy_var_i_0(new, token, v));
	(*token) += i;
	var_name[i] = '\0';
	cpy_var_get_var(shell, var_name, &var);
	cpy_var_cpy(shell, var, new, v);
	return (0);
}
