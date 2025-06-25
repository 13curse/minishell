/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:26:56 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/09 17:47:30 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_hex_fd(unsigned int n, int uppercase, int fd)
{
	char	*hex_lower;
	char	*hex_upper;
	char	*hex;
	int		count;

	count = 0;
	hex_lower = "0123456789abcdef";
	hex_upper = "0123456789ABCDEF";
	if (uppercase)
		hex = hex_upper;
	else
		hex = hex_lower;
	if (n >= 16)
		count += ft_putnbr_hex_fd(n / 16, uppercase, fd);
	count += write(fd, &hex[n % 16], 1);
	return (count);
}

int	ft_putnbr_unsigned_fd(unsigned int n, int fd)
{
	int		count;
	char	c;

	count = 0;
	if (n >= 10)
		count += ft_putnbr_unsigned_fd(n / 10, fd);
	c = (n % 10) + '0';
	count += write(fd, &c, 1);
	return (count);
}

int	ft_putnbr_ptr_fd(unsigned long p, int fd)
{
	char	*hex;
	int		count;

	count = 0;
	hex = "0123456789abcdef";
	if (p >= 16)
	{
		count += ft_putnbr_ptr_fd(p / 16, fd);
	}
	count += write(fd, &hex[p % 16], 1);
	return (count);
}

int	ft_isptrnull_fd(unsigned long p, int fd)
{
	int	count;

	count = 0;
	if (p == 0)
		count += write(fd, "(nil)", 5);
	else
	{
		count += write(fd, "0x", 2);
		return (count + ft_putnbr_ptr_fd(p, fd));
	}
	return (count);
}
