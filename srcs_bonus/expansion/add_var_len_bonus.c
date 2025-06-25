/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var_len_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:20:43 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/12 20:20:43 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	add_status_len(t_minishell *shell, char **token, int *len)
{
	char	*var;

	var = ft_itoa(shell->status);
	if (var == NULL)
		return (1);
	*len += ft_strlen(var);
	free (var);
	(*token)++;
	return (0);
}

int	get_var_name_len(char **token, char *var_name)
{
	int	i;

	i = -1;
	while ((*token)[++i] && (ft_isalnum((*token)[i])
		|| (*token)[i] == '_') && i < 256)
		var_name[i] = (*token)[i];
	if (i == 256)
	{
		write(2, "the name of the varibale to be expanded is too long\n", 52);
		return (-1);
	}
	var_name[i] = '\0';
	return (i);
}

int	add_dollar_len(char **token, int *len, int i)
{
	if (is_dollar_to_be_printed(*token + i))
		(*len)++;
	return (0);
}

int	add_env_len(t_minishell *shell, int *len, char *var_name)
{
	char	*var;

	var = get_env_value(shell, var_name);
	if (var == NULL)
		return (0);
	*len += ft_strlen(var);
	return (0);
}

int	add_var_len(t_minishell *shell, char **token, int *len)
{
	char	var_name[256];
	int		i;

	(*token)++;
	if (**token == '?')
		return (add_status_len(shell, token, len));
	i = get_var_name_len(token, var_name);
	if (i == -1)
		return (1);
	if (i == 0)
		return (add_dollar_len(token, len, i));
	if (!ft_strncmp(var_name, "?", 2))
		return (add_status_len(shell, token, len));
	(*token) += i;
	return (add_env_len(shell, len, var_name));
}
