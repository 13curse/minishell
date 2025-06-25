/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:34:53 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/10 17:34:53 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_unique_filename(char *name)
{
	int		i;
	char	*n;

	ft_strlcpy(name, "/tmp/heredoc", 13);
	i = -1;
	while (++i <= 2147483647)
	{
		n = ft_itoa(i);
		ft_strlcpy(name + 12, n, 12 + ft_strlen(n) + 1);
		free(n);
		if (access(name, F_OK) == -1)
			return (0);
	}
	write(2, "cannot create heredoc file\n", 27);
	return (1);
}

int	whl_handle_spc_val(char **input, char *limiter)
{
	if (*input == NULL)
		return (1);
	if (*input == (void *)-1)
	{
		*input = NULL;
		return (666);
	}
	if (*input == (void *)-2
		|| !ft_strncmp(*input, limiter, ft_strlen(limiter) + 1))
	{
		if (*input == (void *)-2)
			*input = NULL;
		return (0);
	}
	return (-1);
}

int	write_heredoc_line(int fd, char *limiter, t_minishell *shell, char **input)
{
	char	*expanded;
	int		ret;

	*input = ft_readline2(shell);
	ret = whl_handle_spc_val(input, limiter);
	if (ret != -1)
		return (ret);
	if (shell->heredocs->expand_var && ft_strchr(*input, '$'))
	{
		expanded = expand_var_heredoc(shell, *input);
		if (expanded)
		{
			write(fd, expanded, ft_strlen(expanded));
			free(expanded);
		}
		else
			write(fd, *input, ft_strlen(*input));
	}
	else
		write(fd, *input, ft_strlen(*input));
	write(fd, "\n", 1);
	return (2);
}

int	write_to_heredoc(t_minishell *shell, char *limiter)
{
	int		fd;
	char	*input;
	int		status;

	fd = shell->heredocs->fds[shell->heredocs->i];
	while (1)
	{
		status = write_heredoc_line(fd, limiter, shell, &input);
		if (status == 666)
			return (666);
		if (status == 1)
			return (1);
		if (status == 0)
		{
			free(input);
			break ;
		}
		free(input);
	}
	return (0);
}
