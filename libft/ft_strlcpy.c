/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:46:05 by van-nguy          #+#    #+#             */
/*   Updated: 2024/11/18 20:05:29 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;

	len = 0;
	while (*(src + len))
		len++;
	while (size > 1 && *src)
	{
		*dst = *src;
		dst++;
		src++;
		size--;
	}
	if (size)
		*dst = '\0';
	return (len);
}
