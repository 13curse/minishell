/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:12 by van               #+#    #+#             */
/*   Updated: 2025/06/12 22:44:28 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

static size_t	count_str(char const *s)
{
	size_t	count;
	int		sep;

	count = 0;
	sep = 1;
	while (*s)
	{
		if (is_whitespace(*s))
			sep = 1;
		else
		{
			count += sep;
			sep = 0;
		}
		s++;
	}
	return (count);
}

static size_t	slen(char const *s)
{
	size_t	len;

	len = 0;
	while (s[len] && !is_whitespace(s[len]))
		len++;
	return (len);
}

char	**ft_split2(char const *s)
{
	char		**arr;
	size_t		cs;
	size_t		i;
	size_t		shift;

	if (!s)
		return (NULL);
	cs = count_str(s);
	arr = malloc((cs + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = -1;
	shift = 0;
	while (++i < cs)
	{
		while (s[shift] && is_whitespace(s[shift]))
			shift++;
		arr[i] = malloc (slen (s + shift) + 1);
		if (arr[i] == NULL)
			return (NULL);
		ft_strlcpy (arr[i], s + shift, slen (s + shift) + 1);
		shift = shift + slen (s + shift);
	}
	arr[i] = NULL;
	return (arr);
}
