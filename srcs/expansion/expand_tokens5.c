/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 19:56:55 by van               #+#    #+#             */
/*   Updated: 2025/06/08 20:07:50 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	avl_status(t_minishell *shell, int *len, char **token)
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

int	avl_add_len(t_minishell *shell, char *var_name, int *li[2], char **token)
{
	char	*var;
	int		*len;
	int		i;

	len = li[0];
	i = *li[1];
	if (!ft_strncmp(var_name, "?", 2))
	{
		var = ft_itoa(shell->status);
		if (var == NULL)
			return (1);
		*len += ft_strlen(var);
		free (var);
	}
	else
	{
		(*token) += i;
		var = get_env_value(shell, var_name);
		if (var == NULL)
			return (0);
		*len += ft_strlen(var);
	}
	return (0);
}

int	add_var_len(t_minishell *shell, char **token, int *len)
{
	char	var_name[256];
	int		i;

	(*token)++;
	if (**token == '?')
		return (avl_status(shell, len, token));
	i = -1;
	while ((*token)[++i]
		&& (ft_isalnum((*token)[i]) || (*token)[i] == '_') && i < 256)
		var_name[i] = (*token)[i];
	if (i == 256)
	{
		write(2, "the name of the varibale to be expanded is too long\n", 52);
		return (1);
	}
	if (i == 0)
	{
		if (is_dollar_to_be_printed(*token + i))
			(*len)++;
		return (0);
	}
	var_name[i] = '\0';
	if (avl_add_len(shell, var_name, (int *[2]){len, &i}, token))
		return (1);
	return (0);
}
