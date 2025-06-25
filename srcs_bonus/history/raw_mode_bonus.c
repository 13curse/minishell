/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:24:16 by sbehar            #+#    #+#             */
/*   Updated: 2025/05/20 14:24:16 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	enable_raw_mode(struct termios *orig_termios);
int	disable_raw_mode(struct termios *orig_termios);

int	enable_raw_mode(struct termios *orig_termios)
{
	struct termios	raw;

	if (tcgetattr(STDIN_FILENO, orig_termios) == -1)
		return (1);
	raw = *orig_termios;
	raw.c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		return (1);
	return (0);
}

int	disable_raw_mode(struct termios *orig_termios)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios) == -1)
		return (1);
	return (0);
}
