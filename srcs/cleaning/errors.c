/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:47:28 by van               #+#    #+#             */
/*   Updated: 2025/06/25 22:27:12 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
