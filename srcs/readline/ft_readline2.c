/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:58:06 by van-nguy          #+#    #+#             */
/*   Updated: 2025/06/09 19:21:04 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*read_user_input(t_minishell *shell, int add_his);
char	*read_user_input2(t_minishell *shell);
char	*realloc_buffer(char *buffer, int *size);
int		dup_stdin(int *fd);

char	*ft_readline2(t_minishell *shell)
{
	char	*input;
	int		fd;

	if (dup_stdin(&fd))
		return (NULL);
	write(1, "> ", 2);
	setup_signal_handlers(1);
	input = read_user_input2(shell);
	setup_signal_handlers(0);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (input);
}

char	*rui2_loop_rets(int *i, int opt[3], char **buffer, char *ret)
{
	int	to_free;
	int	nl;
	int	null_term;

	to_free = opt[0];
	nl = opt[1];
	null_term = opt[2];
	if (nl)
		write(STDIN_FILENO, "\n", 1);
	if (to_free)
		free(*buffer);
	if (null_term)
		(*buffer)[*i] = '\0';
	return (ret);
}

char	*rui2_loop(t_minishell *shell, char **buffer, int *i, int *size)
{
	char	c;
	int		bytes;

	c = '\n';
	bytes = read(STDIN_FILENO, &c, 1);
	if (bytes <= 0 && g_sigint_received == 1)
	{
		g_sigint_received = 0;
		shell->status = 130;
		free(*buffer);
		return ((void *)-1);
	}
	if (bytes < 0)
		return (rui2_loop_rets(i, (int [3]){1, 0, 0}, buffer, NULL));
	if (bytes == 0)
		return (rui2_loop_rets(i, (int [3]){1, 1, 0}, buffer, (void *)-2));
	if (c == '\n')
		return (rui2_loop_rets(i, (int [3]){0, 0, 1}, buffer, (void *)-3));
	if (*i == *size - 1)
		*buffer = realloc_buffer(*buffer, size);
	if (*buffer == NULL)
		return ((void *)-3);
	(*buffer)[(*i)++] = c;
	return ((void *)-4);
}

char	*call_err_malloc_ret_null(void)
{
	err_malloc(1);
	return (NULL);
}

char	*read_user_input2(t_minishell *shell)
{
	char	*buffer;
	int		i;
	int		size;
	char	*ret;

	size = 32;
	buffer = malloc(sizeof(char) * size);
	if (buffer == NULL)
		return (call_err_malloc_ret_null());
	ft_memset(buffer, '\0', size);
	i = 0;
	while (1)
	{
		ret = rui2_loop(shell, &buffer, &i, &size);
		if (ret == (void *)-4)
			continue ;
		if (ret == (void *)-3)
			break ;
		return (ret);
	}
	if (!buffer || i == 0)
		printf("\n");
	return (buffer);
}
