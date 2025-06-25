/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identification_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:05:07 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:24:04 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int		count_cmds(char **tokens);
void	fill_cmds(char **tokens, char ****cmds);
void	abort_fill_cmds(char **tokens, int len, char ****cmds,
			char **original_tokens);
int		parse_tokens(t_minishell *shell, char **tokens);
void	fill_cmds(char **tokens, char ****cmds);

int	get_cmd_len(char **tokens)
{
	int	len;

	len = 0;
	while (tokens[len] && ft_strncmp(tokens[len], "|", 2)
		&& !is_cmds_sep(tokens[len]))
		len++;
	return (len);
}

int	skip_and_get_len(char **tokens)
{
	skip_space(tokens);
	return (get_cmd_len(tokens));
}

void	copy_tokens(char **dest, char **src, int len)
{
	int	j;

	j = 0;
	while (j < len)
	{
		dest[j] = src[j];
		j++;
	}
}

void	fill_cmds(char **tokens, char ****cmds)
{
	int		len;
	int		i;
	char	**original_tokens;

	original_tokens = tokens;
	i = -1;
	tokens--;
	while (*(++tokens))
	{
		len = skip_and_get_len(tokens);
		if (len == 0)
			continue ;
		(*cmds)[++i] = malloc (sizeof(char *) * (len + 1));
		if ((*cmds)[i] == NULL)
		{
			abort_fill_cmds(tokens, len, cmds, original_tokens);
			return ;
		}
		fill_null((void *)(*cmds)[i], len + 1);
		copy_tokens((*cmds)[i], tokens, len);
		tokens += len;
		if (*tokens == NULL || is_cmds_sep(*tokens))
			break ;
	}
}

void	abort_fill_cmds(char **tokens, int len,
			char ****cmds, char **original_tokens)
{
	int	i;
	int	j;

	i = -1;
	while ((*cmds)[++i])
	{
		j = -1;
		while ((*cmds)[i][++j])
			free ((*cmds)[i][j]);
		free ((*cmds)[i]);
	}
	free (*cmds);
	*cmds = NULL;
	i = -1;
	while (tokens + len + --i && i > -len)
		free(tokens[len + i]);
	i = -1;
	while (++i == len || tokens[i])
	{
		if (i == len)
			continue ;
		free(tokens[i]);
	}
	free(original_tokens);
	err_malloc(1);
}
