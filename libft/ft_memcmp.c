/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:05:42 by van               #+#    #+#             */
/*   Updated: 2024/11/18 20:03:14 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_;
	const unsigned char	*s2_;

	if (n == 0)
		return (0);
	s1_ = s1;
	s2_ = s2;
	while (n && *s1_ == *s2_)
	{
		n--;
		if (n)
		{
			s1_++;
			s2_++;
		}
	}
	return (*s1_ - *s2_);
}
