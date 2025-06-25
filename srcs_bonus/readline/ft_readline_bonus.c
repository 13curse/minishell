/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:10:40 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:23:52 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

char	*ft_readline(char *prompt, int add_his, t_minishell *shell);
int		process_char(t_input_state *input, t_minishell *shell, char c);
char	*user_input_loop(t_input_state *input, t_minishell *shell, int add_his);
char	*read_user_input(t_minishell *shell, int add_his);
char	*realloc_buffer(char *buffer, int *size);

char	*ft_readline(char *prompt, int add_his, t_minishell *shell)
{
	struct termios	orig_termios;
	char			*input;

	if (prompt == NULL)
		write(1, "\033[31mminishell >\033[0m", 21);
	else
		write(1, prompt, ft_strlen(prompt));
	if (add_his)
		enable_raw_mode(&orig_termios);
	input = read_user_input(shell, add_his);
	if (add_his)
		disable_raw_mode(&orig_termios);
	if (input == (void *)-1)
		kill_shell(shell);
	if (input && add_his && input[0] != '\0')
		add_to_history(shell, input);
	return (input);
}

int	process_char(t_input_state *input, t_minishell *shell, char c)
{
	const char	*prompt;

	prompt = "\033[1;35mminishell > \033[0m";
	if (c == '\n')
	{
		input->buffer[input->len] = '\0';
		write(1, "\n", 1);
		return (1);
	}
	else if (c == 127 || c == 8)
		delete_char(input, prompt);
	else if (c == 27)
	{
		handle_arrow_keys(input, shell);
		input->buffer[input->len] = '\0';
	}
	else if (input->buffer)
		insert_char(input, c, prompt);
	return (0);
}

char	*user_input_loop(t_input_state *input, t_minishell *shell, int add_his)
{
	char	c;
	int		ret;

	while (1)
	{
		ret = read(STDIN_FILENO, &c, 1);
		if (add_his && ret > 0 && c == 0x04)
		{
			if (input->len == 0)
			{
				handle_ctrl_d(input);
				return ((void *)-1);
			}
			continue ;
		}
		if (g_sigint_received)
			return (handle_sigint_rd(input, shell));
		if (handle_read_errors(ret, input))
			return ((void *)-1);
		if (process_char(input, shell, c) == 1)
			break ;
		if (!input->buffer)
			return (NULL);
	}
	return (input->buffer);
}

char	*read_user_input(t_minishell *shell, int add_his)
{
	t_input_state	input;
	char			*result;

	if (!init_input_and_buff(&input, shell))
		return (NULL);
	result = user_input_loop(&input, shell, add_his);
	if (result == (void *)-1 || result == NULL)
		return (result);
	input.buffer[input.len] = '\0';
	if (input.len == 0)
		input.buffer[0] = '\0';
	return (input.buffer);
}

char	*realloc_buffer(char *buffer, int *size)
{
	int		new_size;
	char	*new_buffer;

	if (*size <= 64)
		new_size = *size * 2;
	else
		new_size = *size + 64;
	new_buffer = malloc(sizeof(char) * new_size);
	if (new_buffer == NULL)
	{
		free(buffer);
		return (NULL);
	}
	ft_memcpy(new_buffer, buffer, *size);
	new_buffer[new_size - 1] = '\0';
	*size = new_size;
	free(buffer);
	return (new_buffer);
}
