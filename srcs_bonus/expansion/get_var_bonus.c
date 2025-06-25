/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:26:53 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:25:21 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

char	*dollar_dont_match_varname(char **token);

char	*get_var(t_minishell *shell, char **token)
{
	char	var_name[256];
	int		i;
	char	*value;

	(*token)++;
	if (**token == '?')
	{
		(*token)++;
		return ("status_code");
	}
	if (!ft_isalnum(**token) && **token != '_')
		return (dollar_dont_match_varname(token));
	var_name[0] = **token;
	i = 0;
	while ((*token)[++i] && (ft_isalnum((*token)[i])
		|| (*token)[i] == '_') && i < 256)
		var_name[i] = (*token)[i];
	var_name[i] = '\0';
	*token += ft_strlen(var_name);
	value = get_env_value(shell, var_name);
	if (value == NULL)
		return ("");
	return (value);
}

char	*dollar_dont_match_varname(char **tkn)
{
	if (is_dollar_to_be_printed(*tkn))
		return ("$");
	else
		return ("");
}

char	*get_status(t_minishell *shell)
{
	char	*exit_code;

	exit_code = ft_itoa(shell->status);
	if (exit_code == NULL)
		ft_printf(2, "itoa failed\n");
	return (exit_code);
}

int	is_dollar_to_be_printed(char *token)
{
	int	quote;
	int	count;

	if (*token != '\'' && *token != '"')
		return (1);
	quote = *token;
	token++;
	count = 1;
	while (*token)
	{
		if (*token == quote)
			count++;
		token++;
	}
	return (count % 2);
}
