/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:58:18 by van               #+#    #+#             */
/*   Updated: 2025/06/08 20:09:11 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_additionnal_token(char *str, int *new_tkn);
int	count_tkn_var(t_minishell *shell, char **token, int *quote, int *new_tkn);

int	count_tokens_after_expand(t_minishell *shell)
{
	int		i;
	int		count;
	char	*token;
	int		quote;
	int		new_tkn;

	count = 0;
	token = shell->cmds[shell->cmd_id - 1][0];
	i = 0;
	new_tkn = 1;
	while (token)
	{
		count++;
		if (!ft_strchr(token, '$'))
		{
			token = shell->cmds[shell->cmd_id - 1][++i];
			new_tkn = 1;
			continue ;
		}
		quote = 0;
		token--;
		count += count_tkn_var(shell, &token, &quote, &new_tkn);
		token = shell->cmds[shell->cmd_id - 1][++i];
	}
	return (count);
}

int	count_tkn_var(t_minishell *shell, char **token, int *quote, int *new_tkn)
{
	int		count;
	char	*var;

	count = 0;
	while (*++(*token))
	{
		if (ft_strchr("'\"", **token))
		{
			if (*quote == 0)
				*quote = **token;
			else if (*quote == **token)
				*quote = 0;
		}
		if (!*quote && **token == '$')
		{
			var = get_var(shell, token);
			if (var == NULL)
				kill_shell(shell);
			count += count_additionnal_token(var, new_tkn);
			(*token)--;
		}
	}
	return (count);
}

int	count_additionnal_token(char *str, int *new_tkn)
{
	int	count;

	if (str == NULL || *str == '\0')
		return (0);
	count = 0;
	while (*str)
	{
		while (ft_isspace(*str))
		{
			str++;
			*new_tkn = 1;
		}
		while (!ft_isspace(*str) && *str)
		{
			if (*new_tkn)
			{
				count++;
				*new_tkn = 0;
			}
			str++;
		}
	}
	return (count);
}
