/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:30:30 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/09 17:46:12 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		alloc_and_fill_cmd(char ***cmds, char **tokens, int len, int i);
int		next_cmd_len(char **tokens);
void	fill_cmds(char **tokens, char ****cmds);
void	abort_fill_cmds(char **tokens, int len,
			char ****cmds, char **original_tokens);

int	alloc_and_fill_cmd(char ***cmds, char **tokens, int len, int i)
{
	int	j;

	cmds[i] = malloc(sizeof(char *) * (len + 1));
	if (cmds[i] == NULL)
		return (1);
	fill_null((void *)cmds[i], len + 1);
	j = -1;
	while (++j < len)
		cmds[i][j] = *(tokens++);
	return (0);
}

int	next_cmd_len(char **tokens)
{
	int	len;

	len = 0;
	while (tokens[len] && ft_strncmp(tokens[len], "|", 2))
		len++;
	return (len);
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
		skip_space(tokens);
		len = next_cmd_len(tokens);
		free(tokens[len]);
		if (len == 0)
			continue ;
		if (alloc_and_fill_cmd(*cmds, tokens, len, ++i))
		{
			abort_fill_cmds(tokens, len, cmds, original_tokens);
			return ;
		}
		tokens += len;
		if (*tokens == NULL)
			break ;
	}
	free(original_tokens);
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
