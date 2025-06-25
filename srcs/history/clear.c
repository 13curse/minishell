/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:48:32 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/06 12:48:32 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			get_terminal_cols(void);
static void	move_cursor_up(int lines);
static void	clear_line_and_down(int lines);
void		clear_lines(int prev_term_width);

int	get_terminal_cols(void)
{
	struct winsize	ws;
	int				cols;

	cols = 80;
	if (ioctl(1, TIOCGWINSZ, &ws) == 0)
		cols = ws.ws_col;
	return (cols);
}

static void	move_cursor_up(int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		write(1, "\033[A", 3);
		i++;
	}
}

static void	clear_line_and_down(int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		write(1, "\r\033[2K", 5);
		if (i < lines - 1)
			write(1, "\033[B", 3);
		i++;
	}
}

void	clear_lines(int prev_term_width)
{
	int				cols;
	int				lines;

	cols = get_terminal_cols();
	lines = (prev_term_width + cols - 1) / cols;
	if (lines < 1)
		lines = 1;
	write(1, "\r", 1);
	move_cursor_up(lines - 1);
	clear_line_and_down(lines);
	move_cursor_up(lines - 1);
}
