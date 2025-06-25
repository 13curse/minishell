/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:36:55 by van               #+#    #+#             */
/*   Updated: 2024/11/18 19:56:48 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	bytes;

	if (size != 0 && nmemb >= (size_t) ~ 0UL / size)
		return (NULL);
	bytes = nmemb * size;
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	while (bytes--)
		*((char *)ptr + bytes) = '\0';
	return (ptr);
}

// (size_t)~0UL ~0:invert bytes of 0 000...->111...