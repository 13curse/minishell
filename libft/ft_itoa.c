/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 01:56:42 by van               #+#    #+#             */
/*   Updated: 2024/11/16 14:11:39 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	needed_len(int n)
{
	size_t	len;

	len = 1;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

void	insert_itoa(char *s, int n)
{
	if (n < 10)
		*s = n + '0';
	else
	{
		*s = n % 10 + '0';
		insert_itoa(s - 1, n / 10);
	}
}

char	*min_handler(void)
{
	char	*ptr;

	ptr = malloc (12);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, "-2147483648", 13);
	return (ptr);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*ptr;

	if (n == -2147483648)
		return (min_handler());
	len = needed_len(n);
	ptr = malloc (len + 1);
	if (ptr == NULL)
		return (NULL);
	ptr[len] = '\0';
	if (n < 0)
	{
		n = -n;
		*ptr = '-';
	}
	insert_itoa(ptr + len - 1, n);
	return (ptr);
}
