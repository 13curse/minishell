/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:02:19 by van               #+#    #+#             */
/*   Updated: 2024/11/18 20:05:23 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	i;

	len_src = 0;
	len_dst = 0;
	while (*(src + len_src))
		len_src++;
	while (*(dst + len_dst))
		len_dst++;
	if (len_dst >= size)
		return (size + len_src);
	i = 0;
	while (size - len_dst > 1 && *src)
	{
		dst[len_dst + i] = *src;
		i++;
		src++;
		size--;
	}
	dst[len_dst + i] = '\0';
	return (len_src + len_dst);
}

// size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	k;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (dst[i] && i < dstsize)
// 		i++;
// 	while (src[j])
// 		j++;
// 	if (i == dstsize)
// 		return (i + j);
// 	while (src[k] && i + k < dstsize - 1)
// 	{
// 		dst[i + k] = src[k];
// 		k++;
// 	}
// 	dst[i + k] = '\0';
// 	return (i + j);
// }