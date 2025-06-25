/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_var_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:48:33 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/12 19:48:33 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	cpy_status(t_expand *data);
int	get_var_name(char **token, char *var_name);
int	copy_var_value(t_expand *data, char *var);
int	get_var_value(t_expand *data, char *var_name, char **var);
int	cpy_var_dollar_print(t_expand *data);

int	cpy_status(t_expand *data)
{
	int		i;
	char	*var;

	i = -1;
	var = ft_itoa(data->shell->status);
	if (var == NULL)
		return (1);
	while (var[++i])
	{
		if (ft_strchr("'\"$", var[i]))
			add_uninterpreted(data->shell, data->j, *(data->l));
		**(data->new) = var[i];
		(*(data->new))++;
		(*(data->l))++;
	}
	free (var);
	(*(data->token))++;
	return (0);
}

int	get_var_name(char **token, char *var_name)
{
	int	i;

	i = -1;
	while ((*token)[++i] && (ft_isalnum((*token)[i])
		|| (*token)[i] == '_') && i < 256)
		var_name[i] = (*token)[i];
	if (i == 256)
	{
		write(2, "the name of the variable to be expanded is too long\n", 52);
		return (-1);
	}
	var_name[i] = '\0';
	(*token) += i;
	return (i);
}

int	copy_var_value(t_expand *data, char *var)
{
	int	i;

	i = -1;
	while (var[++i])
	{
		if (ft_strchr("'\"$", var[i]))
		{
			add_uninterpreted(data->shell, data->j, *(data->l));
		}
		**(data->new) = var[i];
		(*(data->new))++;
		(*(data->l))++;
	}
	return (0);
}

int	get_var_value(t_expand *data, char *var_name, char **var)
{
	if (!ft_strncmp(var_name, "?", 2))
	{
		*var = ft_itoa(data->shell->status);
		if (*var == NULL)
			return (1);
	}
	else
	{
		*var = get_env_value(data->shell, var_name);
		if (*var == NULL)
			return (0);
	}
	return (2);
}

int	cpy_var_dollar_print(t_expand *data)
{
	if (is_dollar_to_be_printed(*(data->token)))
	{
		**(data->new) = '$';
		(*(data->new))++;
		(*(data->l))++;
	}
	return (0);
}
