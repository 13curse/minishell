/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections5_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:03:14 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:23:14 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	efv_match_quote(t_efv *v, char **new, char **filename, int *uninterpreted);
int	efv_match_dollar(t_minishell *shell, t_efv *v, char **new, char **filename);

int	expand_filename_var(t_minishell *shell,
	char *filename, char *new, int *uninterpreted)
{
	t_efv	v;

	v.len = 0;
	v.quote = 0;
	while (*filename)
	{
		if (*filename == '\'' || *filename == '"')
		{
			if (efv_match_quote(&v, &new, &filename, uninterpreted))
				return (1);
		}
		else if (*filename == '$' && v.quote != '\'')
		{
			if (efv_match_dollar(shell, &v, &new, &filename))
				return (1);
		}
		else
		{
			v.len++;
			*new++ = *filename++;
		}
	}
	*new = '\0';
	return (0);
}

int	is_interpreted2(int *uninterpreted, int len)
{
	int	i;

	i = -1;
	while (++i < MAX_UNINTERPRETED && uninterpreted[i] != -1)
	{
		if (uninterpreted[i] == len)
			return (0);
		if (uninterpreted[i] > len)
			return (1);
	}
	return (1);
}

void	update_uninterpreted2(int *uninterpreted, int *len)
{
	int	i;

	i = -1;
	while (++i < MAX_UNINTERPRETED)
	{
		if (uninterpreted[i] == -1)
			return ;
		if (uninterpreted[i] >= *len)
			uninterpreted[i]--;
	}
	(*len)--;
}

void	cpy_expand_quote(char **filename, int *uninterpreted, int *l)
{
	int	quote;
	int	len;

	quote = **filename;
	ft_strlcpy(*filename, *filename + 1, ft_strlen(*filename + 1) + 1);
	update_uninterpreted2(uninterpreted, l);
	len = 0;
	while (((*filename)[len] && (*filename)[len] != quote)
		|| !is_interpreted2(uninterpreted, len))
		len++;
	ft_strlcpy(*filename + len, *filename + len + 1,
		ft_strlen(*filename + len + 1) + 1);
	*l += len;
	update_uninterpreted2(uninterpreted, l);
	*filename += len;
}

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
