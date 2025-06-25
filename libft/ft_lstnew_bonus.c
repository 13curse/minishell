/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:22:27 by van               #+#    #+#             */
/*   Updated: 2024/11/17 01:09:38 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*el;

	el = malloc (sizeof(t_list));
	if (el == NULL)
		return (NULL);
	(*el).content = content;
	el->next = NULL;
	return (el);
}
