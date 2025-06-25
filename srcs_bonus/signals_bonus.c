/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:28:57 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/13 11:21:29 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

volatile sig_atomic_t	g_sigint_received = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	g_sigint_received = 1;
	write(STDIN_FILENO, "\n", 1);
	close (STDIN_FILENO);
}

void	sigquit_handler(int sig)
{
	(void)sig;
	g_sigint_received = 2;
	exit (131);
}

void	setup_signal_handlers(int interactive)
{
	if (interactive == 1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (interactive == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, sigquit_handler);
	}
	else if (interactive == 2)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, sigquit_handler);
	}
}
