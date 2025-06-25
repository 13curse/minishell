/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:08:16 by sbehar            #+#    #+#             */
/*   Updated: 2025/05/15 14:15:52 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include "../libft/libft.h"

int		ft_printf(int fd, const char *format, ...);
int		ft_putnbr_hex_fd(unsigned int n, int uppercase, int fd);
int		ft_putnbr_unsigned_fd(unsigned int n, int fd);
int		ft_putnbr_ptr_fd(unsigned long p, int fd);
int		ft_isptrnull_fd(unsigned long p, int fd);

#endif
