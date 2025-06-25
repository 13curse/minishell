/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:44:54 by sbehar            #+#    #+#             */
/*   Updated: 2025/05/10 19:44:54 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_num(char *s);
static int	parse_exit_status(char *arg, long long *val);
static void	print_exit_err(char *arg, int too_many_args);
int			builtin_exit(t_minishell *shell, char **args);

static int	is_num(char *s)
{
	if (!s || !*s)
		return (0);
	if (*s == '-' || *s == '+')
		s++;
	if (!*s)
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

static int	parse_exit_status(char *arg, long long *val)
{
	int	overflow;

	overflow = 0;
	if (!is_num(arg))
		return (0);
	*val = ft_atoll(arg, &overflow);
	if (overflow)
		return (0);
	return (1);
}

static void	print_exit_err(char *arg, int too_many_args)
{
	if (too_many_args)
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	else
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
}

int	builtin_exit(t_minishell *shell, char **args)
{
	int			status;
	long long	val;

	status = shell->status;
	if (!shell->in_fork)
		ft_putstr_fd("exit\n", 1);
	if (args && args[1])
	{
		if (!parse_exit_status(args[1], &val))
		{
			print_exit_err(args[1], 0);
			free_shell(shell);
			exit(2);
		}
		if (args[2])
		{
			print_exit_err(NULL, 1);
			return (1);
		}
		free_shell(shell);
		exit((unsigned char)val);
	}
	free_shell(shell);
	exit(status);
}
