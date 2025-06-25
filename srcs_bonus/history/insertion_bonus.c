/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:55:56 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/06 12:55:56 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	insert_char(t_input_state *input, char c, const char *prompt);
void	delete_char(t_input_state *input, const char *prompt);
int		handle_arrow_keys(t_input_state *input, t_minishell *shell);

void	insert_char(t_input_state *input, char c, const char *prompt)
{
	int		i;
	int		prev_term_width;
	char	*new_buff;

	prev_term_width = get_terminal_width(input->buffer, prompt);
	if (input->len + 1 >= input->size)
	{
		new_buff = realloc_buffer(input->buffer, &(input->size));
		if (!new_buff)
			return ;
		input->buffer = new_buff;
	}
	clear_lines(prev_term_width);
	i = input->len;
	while (i > input->cursor)
	{
		input->buffer[i] = input->buffer[i - 1];
		i--;
	}
	input->buffer[input->cursor] = c;
	input->len++;
	input->cursor++;
	input->buffer[input->len] = '\0';
	print_prompt_and_buff(input, prompt);
}

void	delete_char(t_input_state *input, const char *prompt)
{
	int	i;
	int	prev_term_width;

	prev_term_width = get_terminal_width(input->buffer, prompt);
	if (input->cursor > 0)
	{
		clear_lines(prev_term_width);
		i = input->cursor - 1;
		while (i < input->len - 1)
		{
			input->buffer[i] = input->buffer[i + 1];
			i++;
		}
		input->len--;
		input->cursor--;
		input->buffer[input->len] = '\0';
		print_prompt_and_buff(input, prompt);
	}
}

int	handle_arrow_keys(t_input_state *input, t_minishell *shell)
{
	char	seq[2];
	char	*prompt;
	int		bytes_read;

	bytes_read = read(STDIN_FILENO, seq, 2);
	if (bytes_read != 2)
		return (0);
	prompt = "\033[1;35mminishell > \033[0m";
	if (seq[0] == '[')
	{
		if (seq[1] == 'A')
			arrow_up(input, shell, prompt);
		else if (seq[1] == 'B')
			arrow_down(input, shell, prompt);
		else if (seq[1] == 'C')
			move_cursor_right(input, prompt);
		else if (seq[1] == 'D')
			move_cursor_left(input, prompt);
		else
			return (0);
		return (1);
	}
	return (0);
}
