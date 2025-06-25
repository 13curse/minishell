/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:47:28 by van               #+#    #+#             */
/*   Updated: 2025/06/13 11:22:42 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	err_malloc(int err)
{
	write(2, "malloc failed\n", 15);
	perror("malloc");
	return (err);
}

int	err_unclosed_quote(void)
{
	write(2, "unclosed quote\n", 16);
	return (-1);
}

int	err_too_long_path(int err)
{
	write(2, "path too long\n", 15);
	return (err);
}
