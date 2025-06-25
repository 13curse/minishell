/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:04:47 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/10 17:04:47 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_var_heredoc(t_minishell *shell, char *line);

static char	*get_var_name(const char *str, int *len)
{
	*len = 0;
	if (str[0] == '?')
		return ((*len = 1), ft_strdup("?"));
	while (str[*len] && (ft_isalnum(str[*len]) || str[*len] == '_'))
		(*len)++;
	return (ft_substr(str, 0, *len));
}

static int	append_str(char **result, const char *text)
{
	char	*tmp;

	tmp = ft_strjoin(*result, text);
	if (!tmp)
		return (1);
	free(*result);
	*result = tmp;
	return (0);
}

static int	append_var_value(t_minishell *shell, char **result, char *var_name)
{
	char	*var_value;

	if (ft_strcmp(var_name, "?") == 0)
		var_value = ft_itoa(shell->status);
	else
		var_value = get_env_value(shell, var_name);
	if (var_value)
	{
		if (append_str(result, var_value))
		{
			if (!ft_strcmp(var_name, "?"))
				free(var_value);
			return (1);
		}
		if (ft_strcmp(var_name, "?") == 0)
			free(var_value);
	}
	return (0);
}

static int	expand_one_var(t_minishell *shell, char **result, char **start)
{
	char	*var_start;
	char	*var_name;
	char	*before;
	int		var_len;

	var_start = ft_strchr(*start, '$');
	if (!var_start)
		return (0);
	before = ft_substr(*start, 0, var_start - *start);
	if (!before)
		return (-1);
	if (append_str(result, before))
		return (free(before), -1);
	free(before);
	var_start++;
	var_name = get_var_name(var_start, &var_len);
	if (!var_name)
		return (-1);
	if (append_var_value(shell, result, var_name))
		return (free(var_name), -1);
	free(var_name);
	*start = var_start + var_len;
	return (1);
}

char	*expand_var_heredoc(t_minishell *shell, char *line)
{
	char	*result;
	char	*start;
	int		status;

	result = ft_strdup("");
	start = line;
	if (!result)
		return (NULL);
	while (ft_strchr(start, '$'))
	{
		status = expand_one_var(shell, &result, &start);
		if (status == -1)
			return (free(result), NULL);
	}
	if (*start)
		append_str(&result, start);
	return (result);
}
