/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:39:30 by van               #+#    #+#             */
/*   Updated: 2024/11/18 19:52:15 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	big_len;
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	little_len = 0;
	while (little[little_len])
		little_len++;
	big_len = 0;
	while (big[big_len])
		big_len++;
	i = 0;
	while (i + little_len <= len && i + little_len <= big_len)
	{
		j = 0;
		while (j < little_len && big[i + j] == little[j])
			j++;
		if (j == little_len)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
