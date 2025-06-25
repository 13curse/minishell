/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:40:13 by van               #+#    #+#             */
/*   Updated: 2024/11/18 20:06:44 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	length;

	length = 0;
	while (s[length])
		length++;
	if (start >= length || !s[start] || len == 0)
	{
		ptr = malloc(1);
		*ptr = '\0';
		return (ptr);
	}
	length = 0;
	while (s[start + length] && length < len)
		length++;
	ptr = malloc(length + 1);
	if (ptr == NULL)
		return (NULL);
	ptr[length] = '\0';
	while (length--)
		ptr[length] = s[start + length];
	return (ptr);
}
