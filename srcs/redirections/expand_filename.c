/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:37:53 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/08 12:37:53 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		var_expanded_len(t_minishell *shell, char *cmd);
int		expand_filename_quote(char *filename, int *uninterpreted);
int		expand_filename(t_minishell *shell, char **filename);
int		expand_filename_var(t_minishell *shell, char *filename,
			char *new, int *uninterpreted);
void	cpy_expand_quote(char **filename, int *uninterpreted, int *l);

int	expand_filename_quote(char *filename, int *uninterpreted)
{
	int	len;

	len = 0;
	while (*filename)
	{
		if ((*filename == '\'' || *filename == '"')
			&& is_interpreted2(uninterpreted, len))
			cpy_expand_quote(&filename, uninterpreted, &len);
		else
		{
			filename++;
			len++;
		}
	}
	return (0);
}

int	expand_filename(t_minishell *shell, char **filename)
{
	int		uninterpreted[MAX_UNINTERPRETED + 1];
	int		expanded_len;
	char	*new;

	expanded_len = var_expanded_len(shell, *filename);
	if (expanded_len == -1)
		return (1);
	if ((expanded_len == -2 || expanded_len == 0)
		&& !ft_strchr(*filename, '"') && !ft_strchr(*filename, '\''))
		return (0);
	if (expanded_len < 0)
		expanded_len = ft_strlen(*filename);
	new = malloc(sizeof(char) * (expanded_len + 1));
	if (new == NULL)
		return (err_malloc(1));
	ft_memset(uninterpreted, -1, sizeof(uninterpreted));
	expand_filename_var(shell, *filename, new, uninterpreted);
	expand_filename_quote(new, uninterpreted);
	free(*filename);
	*filename = new;
	return (0);
}

int	efv_quote(t_efv *v, int *uninterpreted_i)
{
	if (v->quote == 0)
		v->quote = *v->filename;
	else if (v->quote == *v->filename)
		v->quote = 0;
	else if (add_uninterpreted_filename(v->uninterpreted,
			uninterpreted_i, v->len))
		return (1);
	v->len++;
	*v->new++ = *v->filename++;
	return (0);
}

void	efv_dollar_else(t_minishell *shell, t_efv *v)
{
	char	var_name[256];
	int		i;
	char	*var_value;

	i = 0;
	while (ft_isalnum(*v->filename) || *v->filename == '_')
		var_name[i++] = *v->filename++;
	var_name[i] = '\0';
	var_value = get_env_value(shell, var_name);
	if (var_value)
	{
		v->len += ft_strlen(var_value);
		ft_strlcpy(v->new, var_value, ft_strlen(var_value) + 1);
		v->new += ft_strlen(var_value);
	}
}

int	efv_dollar(t_minishell *shell, t_efv *v)
{
	char	*status_str;

	v->filename++;
	if (*v->filename == '?')
	{
		status_str = ft_itoa(shell->status);
		if (status_str == NULL)
			return (err_malloc(1));
		v->len += ft_strlen(status_str);
		ft_strlcpy(v->new, status_str, ft_strlen(status_str) + 1);
		free(status_str);
		v->new += ft_strlen(status_str);
		v->filename++;
	}
	else
		efv_dollar_else(shell, v);
	return (0);
}
