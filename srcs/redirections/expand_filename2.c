/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:53:19 by van-nguy          #+#    #+#             */
/*   Updated: 2025/06/09 14:54:25 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	efv_quote(t_efv *v, int *uninterpreted_i);
int	efv_dollar(t_minishell *shell, t_efv *v);

void	efv_else(t_efv *v)
{
	v->len++;
	*v->new++ = *v->filename++;
}

int	expand_filename_var(t_minishell *shell, char *fname, char *new, int *unint)
{
	int		uninterpreted_i;
	t_efv	v;

	v.len = 0;
	v.quote = 0;
	v.filename = fname;
	v.new = new;
	v.uninterpreted = unint;
	while (*v.filename)
	{
		if (*v.filename == '\'' || *v.filename == '"')
		{
			if (efv_quote(&v, &uninterpreted_i))
				return (1);
		}
		else if (*v.filename == '$' && v.quote != '\'')
		{
			if (efv_dollar(shell, &v))
				return (1);
		}
		else
			efv_else(&v);
	}
	*v.new = '\0';
	return (0);
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
