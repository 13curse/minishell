/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_id_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:33:03 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/12 22:33:03 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

char	***split_cmds(t_minishell *shell, char **tokens);
int		count_cmds(char **tokens);
void	free_cmds(t_minishell *shell, char ****cmds);
void	abort_fill_cmds(char **tokens, int len,
			char ****cmds, char **original_tokens);
int		parse_tokens(t_minishell *shell, char **tokens);
void	fill_cmds(char **tokens, char ****cmds);

char	***split_cmds(t_minishell *shell, char **tokens)
{
	int		count;
	char	***cmds;
	int		i;

	if (tokens == NULL)
		return (NULL);
	if (parse_tokens(shell, tokens))
		return (NULL);
	count = count_cmds(tokens);
	cmds = malloc(sizeof(char **) * (count + 1));
	if (cmds == NULL)
		return (NULL);
	i = -1;
	while (++i <= count)
		cmds[i] = NULL;
	fill_cmds(tokens, &cmds);
	return (cmds);
}

int	count_cmds(char **tokens)
{
	int	i;
	int	count;
	int	empty;

	i = -1;
	count = 1;
	empty = 1;
	while (tokens[++i])
	{
		if (is_cmds_sep(tokens[i]))
			return (count);
		if (!ft_strncmp(tokens[i], "|", 2))
		{
			if (!empty)
				count++;
			empty = 1;
		}
		else
			empty = 0;
	}
	return (count);
}

void	free_cmds(t_minishell *shell, char ****cmds)
{
	int	i;
	int	j;

	if (shell->uninterpreted)
		free_uninterpreted(&shell->uninterpreted);
	if (shell->cmds_seps)
		free_cmds_seps(&shell->cmds_seps);
	i = -1;
	while ((*cmds)[++i])
	{
		j = -1;
		while ((*cmds)[i][++j])
		{
			free((*cmds)[i][j]);
		}
		free((*cmds)[i]);
	}
	free(*cmds);
	*cmds = NULL;
}
