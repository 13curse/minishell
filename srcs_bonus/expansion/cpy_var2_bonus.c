/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_var2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:08:22 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/12 20:08:22 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	cpy_status(t_expand *data);
int	get_var_name(char **token, char *var_name);
int	copy_var_value(t_expand *data, char *var);
int	get_var_value(t_expand *data, char *var_name, char **var);
int	cpy_var_dollar_print(t_expand *data);

void	init_exp_vars(t_expand *data, t_minishell *shell,
		char **token, char **new)
{
	data->shell = shell;
	data->token = token;
	data->new = new;
}

void	init_exp_vars2(t_expand *data, int i, int j, int *l)
{
	data->i = i;
	data->j = j;
	data->l = l;
	data->quote = 0;
}

int	cpy_var(t_expand *data)
{
	char	var_name[256];
	char	*var;
	int		name_len;
	int		ret;

	(*(data->token))++;
	if (**(data->token) == '?')
		return (cpy_status(data));
	name_len = get_var_name(data->token, var_name);
	if (name_len == -1)
		return (1);
	if (name_len == 0)
		return (cpy_var_dollar_print(data));
	ret = get_var_value(data, var_name, &var);
	if (ret == 1)
		return (1);
	if (ret == 0)
		return (0);
	copy_var_value(data, var);
	if (!ft_strncmp(var_name, "?", 2))
		free(var);
	return (0);
}
