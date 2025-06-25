/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:12 by van               #+#    #+#             */
/*   Updated: 2024/11/18 19:12:31 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_str(char const *s, char c)
{
	size_t	count;
	size_t	sep;

	count = 0;
	sep = 1;
	while (*s)
	{
		if (*s == c)
			sep = 1;
		else
		{
			if (sep)
				count++;
			sep = 0;
		}
		s++;
	}
	return (count);
}

size_t	slen(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char		**arr;
	size_t		cs;
	size_t		i;
	size_t		shift;

	cs = count_str(s, c);
	arr = malloc((cs + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	i = -1;
	shift = 0;
	while (++i < cs)
	{
		while (s[shift] && s[shift] == c)
			shift++;
		arr[i] = malloc (slen (s + shift, c) + 1);
		if (arr[i] == NULL)
			return (NULL);
		ft_strlcpy (arr[i], s + shift, slen (s + shift, c) + 1);
		shift = shift + slen (s + shift, c);
	}
	arr[i] = NULL;
	return (arr);
}
