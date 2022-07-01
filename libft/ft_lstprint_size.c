/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:02:41 by molesen           #+#    #+#             */
/*   Updated: 2021/11/24 10:24:07 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint_size(t_list **alst)
{
	t_list	*current;

	if (!alst)
		return ;
	current = *alst;
	ft_putchar('[');
	while (current)
	{
		ft_putstr(current->content);
		ft_putstr("] (");
		ft_putnbr(current->content_size);
		ft_putstr(") --> [");
		current = current->next;
	}
	ft_putstr("NULL]\n");
}
