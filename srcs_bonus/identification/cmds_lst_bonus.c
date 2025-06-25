/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_lst_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:00:21 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:24:19 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int		parse_cmds_seps(t_minishell *shell, char **tokens);
int		count_cmds_lst(char **tokens);
void	fill_cmds_seps(t_minishell *shell, char **tokens);
int		fills_cmds_lst(t_minishell *shell, char ****cmds_lst,
			char **tokens, int count);
void	free_pipes_and_seps(char **tokens);

char	****cmds_lst_prep(t_minishell *shell, char **tokens, int *count)
{
	char	****cmds_lst;

	if (tokens == NULL)
		return (NULL);
	if (parse_cmds_seps(shell, tokens))
	{
		free_split(tokens);
		return (NULL);
	}
	*count = count_cmds_lst(tokens);
	if (init_cmds_seps(shell, *count))
		return (NULL);
	fill_cmds_seps(shell, tokens);
	cmds_lst = malloc(sizeof(char ***) * (*count + 1));
	if (cmds_lst == NULL)
	{
		err_malloc(1);
		free(tokens);
		return (NULL);
	}
	shell->cmds_lst = cmds_lst;
	return (cmds_lst);
}

char	****cmds_lst(t_minishell *shell, char **tokens)
{
	char	****cmds_lst;
	int		count;

	cmds_lst = cmds_lst_prep(shell, tokens, &count);
	if (cmds_lst == NULL)
		return (NULL);
	if (fills_cmds_lst(shell, cmds_lst, tokens, count))
		return (NULL);
	free_pipes_and_seps(tokens);
	shell->cmdc = count;
	return (cmds_lst);
}

int	is_cmds_sep(char *str)
{
	if (!ft_strncmp("||", str, 3))
		return (1);
	if (!ft_strncmp("&&", str, 3))
		return (1);
	return (0);
}

int	parse_cmds_seps(t_minishell *shell, char **tokens)
{
	int	i;

	if (is_cmds_sep(tokens[0]))
	{
		ft_printf(2, "syntax error near unexpected token '%s'\n", tokens[0]);
		return (1);
	}
	i = 0;
	while (tokens[++i])
	{
		if (is_cmds_sep(tokens[i]) && is_cmds_sep(tokens[i - 1]))
		{
			ft_printf(2, "syntax error near unexpected token '%s'\n",
				tokens[i]);
			return (1);
		}
	}
	if (is_op(tokens[i - 1], shell->op))
	{
		ft_printf(2, "syntax error near unexpected token '%s'\n", tokens[i]);
		return (1);
	}
	return (0);
}

void	add_cmds_seps(t_minishell *shell, int i, char *sep)
{
	if (!ft_strncmp(sep, "&&", 3))
		shell->cmds_seps[i] = AND;
	else if (!ft_strncmp(sep, "||", 3))
		shell->cmds_seps[i] = OR;
	else if (!ft_strncmp(sep, "|", 2))
		shell->cmds_seps[i] = PIPE;
}
