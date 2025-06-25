/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections4_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:38:50 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:23:18 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int		var_expanded_len(t_minishell *shell, char *cmd);

int	reset_stdio(t_minishell *shell)
{
	if (dup2(shell->stdin, STDIN_FILENO) == -1
		|| dup2(shell->stdout, STDOUT_FILENO) == -1)
	{
		perror("");
		return (1);
	}
	return (0);
}

int	add_uninterpreted_filename(int *uninterpreted,
	int *uninterpreted_i, int len)
{
	if (*uninterpreted_i >= MAX_UNINTERPRETED)
	{
		write(2, "too many uninterpreted characters\n", 34);
		return (1);
	}
	uninterpreted[*uninterpreted_i] = len;
	(*uninterpreted_i)++;
	return (0);
}

int	efv_match_quote(t_efv *v, char **new, char **filename, int *uninterpreted)
{
	if (v->quote == 0)
		v->quote = **filename;
	else if (v->quote == **filename)
		v->quote = 0;
	else if (add_uninterpreted_filename(uninterpreted, &v->unint_i, v->len))
		return (1);
	v->len++;
	*(*new)++ = *(*filename)++;
	return (0);
}

int	efv_status(t_minishell *shell, t_efv *v, char **new, char **filename)
{
	char	*status_str;

	status_str = ft_itoa(shell->status);
	if (status_str == NULL)
		return (err_malloc(1));
	v->len += ft_strlen(status_str);
	ft_strlcpy(*new, status_str, ft_strlen(status_str) + 1);
	free(status_str);
	*new += ft_strlen(status_str);
	(*filename)++;
	return (0);
}

int	efv_match_dollar(t_minishell *shell, t_efv *v, char **new, char **filename)
{
	char	var_name[256];
	int		i;
	char	*var_value;

	(*filename)++;
	if (**filename == '?')
	{
		if (efv_status(shell, v, new, filename))
			return (1);
	}
	else
	{
		i = 0;
		while (ft_isalnum(**filename) || **filename == '_')
			var_name[i++] = *(*filename)++;
		var_name[i] = '\0';
		var_value = get_env_value(shell, var_name);
		if (var_value)
		{
			v->len += ft_strlen(var_value);
			ft_strlcpy(*new, var_value, ft_strlen(var_value) + 1);
			*new += ft_strlen(var_value);
		}
	}
	return (0);
}
