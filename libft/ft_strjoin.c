/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:31:18 by van               #+#    #+#             */
/*   Updated: 2024/11/18 20:05:11 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	l1;
	size_t	l2;
	size_t	i;

	l1 = 0;
	while (s1[l1])
		l1++;
	l2 = 0;
	while (s2[l2])
		l2++;
	ptr = malloc(l1 + l2 + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < l1 + l2)
	{
		if (i < l1)
			ptr[i] = s1[i];
		else
			ptr[i] = s2[i - l1];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
