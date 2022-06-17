/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:26:00 by molesen           #+#    #+#             */
/*   Updated: 2021/11/24 09:45:12 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_list;
	t_list	*head;

	if (lst && f)
	{
		new_list = f(lst);
		if (!new_list)
			return (NULL);
		head = new_list;
		lst = lst->next;
		while (lst)
		{
			new_list->next = f(lst);
			if (!new_list->next)
			{
				new_list->next = NULL;
				ft_lstdel(&head, &ft_lstdel_content);
				return (NULL);
			}
			new_list = new_list->next;
			lst = lst->next;
		}
		return (head);
	}
	return (NULL);
}
