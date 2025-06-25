/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:19:25 by van-nguy          #+#    #+#             */
/*   Updated: 2025/06/13 11:21:40 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	dup_stdin(int *fd);

char	*sent_prompt(t_minishell *shell)
{
	char	*input;
	char	*color;
	int		fd;

	if (dup_stdin(&fd))
		return (NULL);
	color = "\033[1;35mminishell >\033[0m";
	setup_signal_handlers(1);
	input = ft_readline(color, 1, shell);
	setup_signal_handlers(0);
	if (input == (void *)-1)
		kill_shell(shell);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (input);
	(void) shell;
}

int	dup_stdin(int *fd)
{
	*fd = open("/dev/tty", O_RDONLY);
	if (*fd == -1)
	{
		perror("open");
		return (1);
	}
	if (dup2(STDIN_FILENO, *fd) == -1)
	{
		perror("dup2");
		return (1);
	}
	return (0);
}
