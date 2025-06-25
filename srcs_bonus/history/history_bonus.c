/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:44:01 by sbehar            #+#    #+#             */
/*   Updated: 2025/05/20 14:44:01 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	init_input_state(t_input_state *input, int buf_size, int history_size);
void	add_to_history(t_minishell *shell, const char *line);
int		print_history(t_minishell *shell);
void	free_history(t_history *history);

void	init_input_state(t_input_state *input, int buf_size, int history_size)
{
	input->buffer = malloc(buf_size);
	if (!input->buffer)
		return ;
	input->buffer[0] = '\0';
	input->buffer[buf_size - 1] = '\0';
	input->len = 0;
	input->size = buf_size;
	input->history_index = -1;
	input->history_size = history_size;
}

int	ft_strcmp_history(t_minishell *shell, const char *line)
{
	t_history	*curr;

	if (!line || line[0] == '\0')
		return (0);
	curr = shell->history;
	if (curr)
	{
		while (curr->next)
			curr = curr->next;
		if (curr->line && ft_strcmp(curr->line, line) == 0)
			return (0);
	}
	return (1);
}

void	add_to_history(t_minishell *shell, const char *line)
{
	t_history	*new;
	t_history	*curr;

	if (!ft_strcmp_history(shell, line))
		return ;
	new = malloc(sizeof(t_history));
	if (!new)
		return ;
	new->line = ft_strdup(line);
	new->next = NULL;
	if (!shell->history)
		shell->history = new;
	else
	{
		curr = shell->history;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

int	print_history(t_minishell *shell)
{
	t_history	*curr;
	int			i;

	curr = shell->history;
	i = 1;
	if (!curr)
		return (1);
	while (curr)
	{
		printf("%d %s\n", i++, curr->line);
		curr = curr->next;
	}
	return (0);
}

void	free_history(t_history *history)
{
	t_history	*tmp;

	while (history)
	{
		tmp = history->next;
		free(history->line);
		free(history);
		history = tmp;
	}
}
