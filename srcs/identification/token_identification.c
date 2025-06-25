/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:05:07 by van               #+#    #+#             */
/*   Updated: 2025/06/09 17:37:09 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// **tokens {"cat", "-e", "file", ">", "out", "|", "echo", "$?", NULL}
// 	->
// ***cmds {
//			{"cat", "-e", "file", ">", "out", NULL},
//			{"echo", "$?", NULL},
//			NULL
// 		   }

char	***split_cmds(t_minishell *shell, char **tokens);
int		count_cmds(char **tokens);
int		parse_tokens(t_minishell *shell, char **tokens);

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

static int	syntax_err(const char *token, char **tokens)
{
	write(2, "syntax error near unexpected token '", 36);
	write(2, tokens[0], ft_strlen(token));
	write(2, "'\n", 2);
	free_split(tokens);
	return (1);
}

int	parse_tokens(t_minishell *shell, char **tokens)
{
	int	i;

	if (tokens == NULL || *tokens == NULL)
		return (0);
	if (!ft_strncmp(tokens[0], "|", 2) || !ft_strncmp(tokens[0], "||", 3)
		|| !ft_strncmp(tokens[0], "&&", 3))
		return (syntax_err(tokens[0], tokens));
	i = 0;
	while (tokens[++i])
	{
		if ((!ft_strncmp(tokens[i], "|", 2)
				|| !ft_strncmp(tokens[i], "||", 3)
				|| !ft_strncmp(tokens[i], "&&", 3))
			&& (is_op(tokens[i - 1], shell->op)))
			return (syntax_err(tokens[i], tokens));
	}
	if (is_op(tokens[i - 1], shell->op))
		return (syntax_err(tokens[i - 1], tokens));
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	int	i,j;
// 	char	*input = " |||qsd>>a|||sort||	||cc| abhead -n'5' |b | ok||||";
// 	// char	*input = "";

// 	char **tokens = split_tokens(input);
// 	if (tokens == NULL)
// 		return (1);
// 	char ***cmds = split_cmds(tokens);
// 	if (cmds == NULL)
// 		return (1);
// 	i = -1;
// 	while (cmds[++i])
// 	{
// 		j = -1;
// 		printf("%d:\n\t", i);
// 		while (cmds[i][++j])
// 			printf("%s ", cmds[i][j]);
// 		printf("\n");
// 	}
// 	i = -1;
// 	while (cmds[++i])
// 	{
// 		j = -1;
// 		while (cmds[i][++j])
// 			free(cmds[i][j]);
// 		free(cmds[i]);
// 	}
// 	free(cmds);
// 	return (0);
// 	if (argc && argv && envp){}
// }
