/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_user_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:45:06 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/07 17:45:06 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int		get_history_size(t_history *history);
int		init_input_and_buff(t_input_state *input, t_minishell *shell);
int		handle_ctrl_d(t_input_state *input);
int		handle_read_errors(int ret, t_input_state *input);
char	*handle_sigint_rd(t_input_state *input, t_minishell *shell);

int	get_history_size(t_history *history)
{
	t_history	*temp;
	int			history_size;

	history_size = 0;
	temp = history;
	while (temp)
	{
		history_size++;
		temp = temp->next;
	}
	return (history_size);
}

int	init_input_and_buff(t_input_state *input, t_minishell *shell)
{
	int	history_size;

	history_size = get_history_size(shell->history);
	ft_memset(input, 0, sizeof(t_input_state));
	init_input_state(input, 32, history_size);
	if (!input->buffer)
		return (0);
	input->len = 0;
	return (1);
}

int	handle_ctrl_d(t_input_state *input)
{
	write(STDIN_FILENO, "\n", 1);
	free(input->buffer);
	return (1);
}

int	handle_read_errors(int ret, t_input_state *input)
{
	if (ret == 0 && input->len == 0)
	{
		free(input->buffer);
		return (1);
	}
	if (ret < 0)
	{
		free(input->buffer);
		perror("\nread_user_input(): \n\tread");
		return (1);
	}
	return (0);
}

char	*handle_sigint_rd(t_input_state *input, t_minishell *shell)
{
	free(input->buffer);
	shell->status = 130;
	g_sigint_received = 0;
	return (NULL);
}
