/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_expand_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:32:56 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/12 21:32:56 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	init_exp_vars(t_expand *data, t_minishell *shell,
			char **token, char **new);
void	init_exp_vars2(t_expand *data, int i, int j, int *l);
int		cpy_var(t_expand *data);

static void	handle_quote(t_expand *data)
{
	if (data->quote == 0)
		data->quote = **(data->token);
	else if (data->quote == **(data->token))
		data->quote = 0;
	else
		add_uninterpreted(data->shell, data->i, *(data->l));
	**(data->new) = **(data->token);
	(*(data->token))++;
	(*(data->l))++;
	(*(data->new))++;
}

static void	handle_normal_char(t_expand *data)
{
	**(data->new) = **(data->token);
	(*(data->token))++;
	(*(data->l))++;
	(*(data->new))++;
}

static int	handle_dollar(t_expand *data)
{
	if (cpy_var(data))
		return (1);
	return (0);
}

static void	handle_in_quote(t_expand *data)
{
	**(data->new) = **(data->token);
	(*(data->token))++;
	(*(data->l))++;
	(*(data->new))++;
}

int	cpy_expand(t_minishell *shell, char *token, char *new, int i)
{
	t_expand	data;
	int			l;

	l = 0;
	init_exp_vars(&data, shell, &token, &new);
	init_exp_vars2(&data, i, 0, &l);
	while (*(data.token) && **(data.token))
	{
		if (**(data.token) == '\'' || **(data.token) == '"')
			handle_quote(&data);
		else if (data.quote != '\'' && **(data.token) != '$')
			handle_normal_char(&data);
		else if (data.quote != '\'' && **(data.token) == '$')
		{
			if (handle_dollar(&data))
				return (1);
		}
		else if (data.quote)
			handle_in_quote(&data);
	}
	**(data.new) = '\0';
	return (0);
}
