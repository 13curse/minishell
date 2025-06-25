/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:58:29 by van               #+#    #+#             */
/*   Updated: 2024/11/17 19:18:03 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*current;
	t_list	*prev;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	prev = NULL;
	while (lst)
	{
		current = ft_lstnew(f(lst->content));
		if (!head)
			head = current;
		if (current == NULL)
		{
			while (head)
				ft_lstdelone(ft_lstlast(head), del);
			return (NULL);
		}
		if (prev)
			prev->next = current;
		lst = lst->next;
		prev = current;
	}
	return (head);
}
