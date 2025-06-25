/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:26:20 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/09 17:54:05 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static long long	ft_atoll_parse(const char *str, int sign, int *overflow)
{
	long long	result;
	int			digit;

	if (ft_strncmp(str, "9223372036854775808", 19) == 0 && sign == -1)
		return (LLONG_MIN);
	result = 0;
	if (overflow)
		*overflow = 0;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (result > (LLONG_MAX - digit) / 10)
		{
			if (overflow)
				*overflow = 1;
			if (sign == 1)
				return (LLONG_MAX);
			else
				return (LLONG_MAX);
		}
		result = result * 10 + digit;
		str++;
	}
	return (sign * result);
}

int	int_len(long long n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 1;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	check_overflow(const char *str, int sign, int *overflow)
{
	if ((int)ft_strlen(str) > int_len(LLONG_MAX))
	{
		*overflow = 1;
		return (0);
	}
	if ((int)ft_strlen(str) == int_len(LLONG_MAX))
	{
		if ((sign == 1 && ft_strncmp(str, "9223372036854775807", 19) > 0)
			|| (sign == -1 && ft_strncmp(str, "9223372036854775808", 19) > 0))
		{
			*overflow = 1;
			return (0);
		}
	}
	return (0);
}

long long	ft_atoll(const char *str, int *overflow)
{
	int	sign;

	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (check_overflow(str, sign, overflow))
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	return (ft_atoll_parse(str, sign, overflow));
}
