/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:43:41 by sbehar            #+#    #+#             */
/*   Updated: 2025/05/20 14:43:41 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static void	update_input(t_input_state *input, t_minishell *shell,
				int prev, const char *prompt);
void		arrow_up(t_input_state *input, t_minishell *shell,
				const char *prompt);
void		arrow_down(t_input_state *inp, t_minishell *shell,
				const char *prompt);
void		move_cursor_left(t_input_state *input, const char *prompt);
void		move_cursor_right(t_input_state *input, const char *prompt);

static void	update_input(t_input_state *input, t_minishell *shell,
		int prev, const char *prompt)
{
	t_history	*temp;
	int			idx;
	int			target;

	temp = shell->history;
	idx = 0;
	target = input->history_size - 1 - input->history_index;
	while (temp && idx < target)
	{
		temp = temp->next;
		idx++;
	}
	clear_lines(prev);
	if (temp && input->history_index >= 0 && copy_hist_line(input, temp->line))
		print_prompt_and_buff(input, prompt);
	else
	{
		input->len = 0;
		input->cursor = 0;
		input->buffer[0] = '\0';
		print_prompt_and_buff(input, prompt);
	}
}

void	arrow_up(t_input_state *input, t_minishell *shell, const char *prompt)
{
	int	prev_term_width;

	if (input->history_size == 0
		|| input->history_index + 1 >= input->history_size)
		return ;
	input->history_index++;
	prev_term_width = get_terminal_width(input->buffer, prompt);
	update_input(input, shell, prev_term_width, prompt);
}

void	arrow_down(t_input_state *inp, t_minishell *shell, const char *prompt)
{
	int	prev_term_width;

	prev_term_width = get_terminal_width(inp->buffer, prompt);
	if (inp->history_size == 0)
		return ;
	if (inp->history_index <= -1)
	{
		clear_lines(prev_term_width);
		inp->len = 0;
		inp->cursor = 0;
		inp->buffer[0] = '\0';
		print_prompt_and_buff(inp, prompt);
		return ;
	}
	if (inp->history_index > -1)
		inp->history_index--;
	else
		inp->history_index = -1;
	update_input(inp, shell, prev_term_width, prompt);
}

void	move_cursor_left(t_input_state *input, const char *prompt)
{
	int	prev_term_width;

	prev_term_width = get_terminal_width(input->buffer, prompt);
	if (input->cursor > 0)
	{
		clear_lines(prev_term_width);
		input->cursor--;
		print_prompt_and_buff(input, prompt);
	}
}

void	move_cursor_right(t_input_state *input, const char *prompt)
{
	int	prev_term_width;

	prev_term_width = get_terminal_width(input->buffer, prompt);
	if (input->cursor < input->len)
	{
		clear_lines(prev_term_width);
		input->cursor++;
		print_prompt_and_buff(input, prompt);
	}
}
