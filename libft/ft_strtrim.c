/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:10:14 by van               #+#    #+#             */
/*   Updated: 2024/11/18 20:37:53 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	set_start_i(size_t *start, size_t *i, char const *s1, char const *set)
{
	*start = 0;
	while (s1[*start] && ft_strchr(set, s1[*start]))
		(*start)++;
	if (s1[*start] == '\0')
		return (1);
	*i = *start;
	return (0);
}

int	malloc_ptr_set_i(char **ptr, size_t *i, size_t start, size_t end)
{
	*i = -1;
	*ptr = malloc (end - start + 1 + 1);
	if (*ptr == NULL)
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	start;
	size_t	end;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	if (!*s1 || !set)
		return (ft_strdup(s1));
	if (set_start_i(&start, &i, s1, set))
		return (ft_strdup(""));
	end = start;
	while (s1[i])
	{
		if (!ft_strchr(set, s1[i]))
			end = i;
		i++;
	}
	ptr = NULL;
	if (malloc_ptr_set_i(&ptr, &i, start, end))
		return (NULL);
	while (++i < end - start + 1)
		ptr[i] = s1[start + i];
	ptr[i] = '\0';
	return (ptr);
}

// BONNE  >25 lignes
// char	*ft_strtrim(char const *s1, char const *set)
// {
// 	char	*ptr;
// 	size_t	start;
// 	size_t	end;
// 	size_t	i;

// 	if (s1 == NULL)
// 		return (NULL);
// 	if (!*s1 || !set)
// 		return (ft_strdup(s1));
// 	start = 0;
// 	while (s1[start] && ft_strchr(set, s1[start]))
// 		start++;
// 	if (s1[start] == '\0')
// 		return (ft_strdup(""));
// 	end = start;
// 	i = start;
// 	while (s1[i])
// 	{
// 		if (!ft_strchr(set, s1[i]))
// 			end = i;
// 		i++;
// 	}
// 	ptr = malloc (end - start + 1 + 1);
// 	if (ptr == NULL)
// 		return (NULL);
// 	i = -1;
// 	while (++i < end - start + 1)
// 		ptr[i] = s1[start + i];
// 	ptr[i] = '\0';
// 	return (ptr);
// }

// int	isset(char const *s, char const *set)
// {
// 	size_t	len_set;
// 	size_t	i;

// 	len_set = 0;
// 	while (set[len_set])
// 		len_set++;
// 	if (len_set == 0)
// 		return (0);
// 	i = 0;
// 	while (s[i] && s[i] == set[i])
// 		i++;
// 	if (i == len_set)
// 		return (1);
// 	return (0);
// }

// char	*ft_strtrim(char const *s1, char const *set)
// {
// 	char	*ptr;
// 	size_t	start;
// 	size_t	end;
// 	size_t	len_set;
// 	size_t	i;

// 	len_set = 0;
// 	start = 0;
// 	end = 0;
// 	while (*(set + len_set))
// 		len_set++;
// 	if (isset(s1, set))
// 		start = len_set;
// 	while (s1[end])
// 		end++;
// 	if (isset(s1 + end - len_set, set))
// 		end = end - len_set;
// 	ptr = malloc (end - start + 1);
// 	if (ptr == NULL)
// 		return (NULL);
// 	i = -1;
// 	while (++i < end - start)
// 		ptr[i] = s1[start + i];
// 	ptr[i] = '\0';
// 	return (ptr);
// }
