/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 10:33:42 by molesen           #+#    #+#             */
/*   Updated: 2021/11/16 13:41:25 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_free_list(t_list *list)
{
	free (list);
	return (NULL);
}

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_list;
	void	*item;

	item = (void *)content;
	new_list = (t_list *)malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	if (!item)
	{
		new_list->content = NULL;
		new_list->content_size = 0;
	}
	else
	{
		item = (void *)malloc(content_size);
		if (!item)
			return (ft_free_list(new_list));
		ft_memcpy(item, content, content_size);
		new_list->content = item;
		new_list->content_size = content_size;
	}
	new_list->next = NULL;
	return (new_list);
}
