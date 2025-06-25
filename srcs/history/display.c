/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:57:01 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/06 12:57:01 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			color_prompt_len(const char *s);
int			get_terminal_width(const char *s, const char *prompt);
int			copy_hist_line(t_input_state *input, char *line);
static void	print_prompt(const t_input_state *input, const char *prompt);
void		print_prompt_and_buff(t_input_state *input, const char *prompt);

int	color_prompt_len(const char *s)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\033' && s[i + 1] == '[')
		{
			i += 2;
			while (s[i] && s[i] != 'm')
				i++;
			if (s[i] == 'm')
				i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

int	get_terminal_width(const char *s, const char *prompt)
{
	int	prompt_len;
	int	width;
	int	col;
	int	spaces;
	int	i;

	prompt_len = color_prompt_len(prompt);
	width = prompt_len;
	col = prompt_len;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\t')
		{
			spaces = 8 - (col % 8);
			width += spaces;
			col += spaces;
		}
		else
		{
			width += 1;
			col += 1;
		}
	}
	return (width);
}

int	copy_hist_line(t_input_state *input, char *line)
{
	int		need;
	char	*new_buff;

	need = ft_strlen(line) + 1;
	while (need > input->size)
	{
		new_buff = realloc_buffer(input->buffer, &(input->size));
		if (!new_buff)
			return (0);
		input->buffer = new_buff;
	}
	ft_strcpy(input->buffer, line);
	input->len = ft_strlen(input->buffer);
	input->cursor = input->len;
	return (1);
}

static void	print_prompt(const t_input_state *input, const char *prompt)
{
	write(1, "\r", 1);
	write(1, prompt, ft_strlen(prompt));
	if (input->len > 0)
		write(1, input->buffer, input->len);
}

void	print_prompt_and_buff(t_input_state *input, const char *prompt)
{
	int	prompt_len;
	int	cursor_pos;
	int	total_display_len;
	int	move_left;
	int	i;

	prompt_len = color_prompt_len(prompt);
	cursor_pos = prompt_len;
	i = 0;
	print_prompt(input, prompt);
	while (i < input->cursor)
	{
		if (input->buffer[i] == '\t')
			cursor_pos += 8 - (cursor_pos % 8);
		else
			cursor_pos++;
		i++;
	}
	total_display_len = get_terminal_width(input->buffer, prompt);
	move_left = total_display_len - cursor_pos;
	while (move_left > 0)
	{
		write(1, "\b", 1);
		move_left--;
	}
}
