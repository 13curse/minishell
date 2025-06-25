/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_id_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:35:43 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/12 22:35:43 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int		count_cmds_lst(char **tokens);
void	fill_cmds_seps(t_minishell *shell, char **tokens);
int		fills_cmds_lst(t_minishell *shell, char ****cmds_lst,
			char **tokens, int count);
void	free_pipes_and_seps(char **tokens);
void	add_cmds_seps(t_minishell *shell, int i, char *sep);

int	count_cmds_lst(char **tokens)
{
	int	count;

	count = 1;
	while (*tokens)
	{
		if (is_cmds_sep(*tokens))
			count++;
		tokens++;
	}
	return (count);
}

void	fill_cmds_seps(t_minishell *shell, char **tokens)
{
	int	i;

	shell->cmds_seps[0] = -1;
	i = 0;
	while (*tokens)
	{
		if (is_cmds_sep(*tokens))
			add_cmds_seps(shell, ++i, *tokens);
		tokens++;
	}
}

int	fills_cmds_lst(t_minishell *shell, char ****cmds_lst,
		char **tokens, int count)
{
	int	i;

	fill_null((void *)cmds_lst, count + 1);
	i = -1;
	while (++i < count)
	{
		if (*tokens == NULL)
			break ;
		cmds_lst[i] = split_cmds(shell, tokens);
		if (cmds_lst[i] == NULL)
		{
			free_cmds_lst(shell);
			free_split(tokens);
			return (1);
		}
		if (*tokens == NULL)
			break ;
		while (*tokens && !is_cmds_sep(*tokens))
			tokens++;
		if (*tokens)
			tokens++;
	}
	return (0);
}

void	free_pipes_and_seps(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
	{
		if (is_cmds_sep(tokens[i]) || !ft_strncmp(tokens[i], "|", 2))
			free(tokens[i]);
	}
	free(tokens);
}
