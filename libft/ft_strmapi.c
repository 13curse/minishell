/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:42:16 by van               #+#    #+#             */
/*   Updated: 2024/11/16 14:13:48 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*ptr;

	len = 0;
	while (*(s + len))
		len++;
	ptr = malloc (len + 1);
	if (ptr == NULL)
		return (NULL);
	len = 0;
	while (s[len])
	{
		ptr[len] = f(len, s[len]);
		len++;
	}
	ptr[len] = '\0';
	return (ptr);
}
