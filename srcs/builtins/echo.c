/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:32:46 by sbehar            #+#    #+#             */
/*   Updated: 2025/05/13 20:32:46 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	parse_echo_flags(char **args, int *n_flag);
int			builtin_echo(char **args);

static int	parse_echo_flags(char **args, int *n_flag)
{
	int	i;
	int	j;

	i = 1;
	*n_flag = 0;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		*n_flag = 1;
		i++;
	}
	return (i);
}

int	builtin_echo(char **args)
{
	int	i;
	int	n_flag;

	i = parse_echo_flags(args, &n_flag);
	while (args[i])
	{
		ft_printf(STDOUT_FILENO, "%s", args[i]);
		if (args[i + 1])
			ft_printf(STDOUT_FILENO, " ");
		i++;
	}
	if (!n_flag)
		ft_printf(STDOUT_FILENO, "\n");
	return (0);
}
