/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:02:34 by van               #+#    #+#             */
/*   Updated: 2025/05/15 14:00:19 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putnbr_fd(int n, int fd)
{
	int		count;
	char	c;

	count = 0;
	if (n == -2147483648)
	{
		return (write(fd, "-2147483648", 11));
	}
	if (n < 0)
	{
		count += write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		count += ft_putnbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	count += write(fd, &c, 1);
	return (count);
}
