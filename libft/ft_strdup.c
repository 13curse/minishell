/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:18:42 by van               #+#    #+#             */
/*   Updated: 2025/06/04 18:02:52 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	length;

	if (s == NULL)
		return (NULL);
	length = 0;
	while (*(s + length))
		length++;
	ptr = malloc(length + 1);
	if (ptr == NULL)
		return (NULL);
	ptr[length] = '\0';
	while (length--)
		ptr[length] = s[length];
	return (ptr);
}
