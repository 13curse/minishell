/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:28:29 by sbehar            #+#    #+#             */
/*   Updated: 2025/05/13 11:27:05 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_handle_format(char percent, va_list args, int fd)
{
	int	count;

	count = 0;
	if (percent == 'c')
		count += ft_putchar_fd(va_arg(args, int), fd);
	else if (percent == 's')
		count += ft_putstr_fd(va_arg(args, char *), fd);
	else if (percent == 'p')
		count += ft_isptrnull_fd(va_arg(args, unsigned long), fd);
	else if (percent == 'd' || percent == 'i')
		count += ft_putnbr_fd(va_arg(args, int), fd);
	else if (percent == 'u')
		count += ft_putnbr_unsigned_fd(va_arg(args, unsigned int), fd);
	else if (percent == 'x')
		count += ft_putnbr_hex_fd(va_arg(args, unsigned int), 0, fd);
	else if (percent == 'X')
		count += ft_putnbr_hex_fd(va_arg(args, unsigned int), 1, fd);
	else if (percent == '%')
		count += ft_putchar_fd('%', fd);
	return (count);
}

int	ft_printf(int fd, const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += ft_handle_format(*format, args, fd);
		}
		else
		{
			count += ft_putchar_fd(*format, fd);
		}
		format++;
	}
	va_end(args);
	return (count);
}

/*int	main()
{
	char *s;
	char str = "salut";
	int	nb;
	nb = ft_printf("%p\n", &str);
	ft_printf("%d", nb);
}*/
