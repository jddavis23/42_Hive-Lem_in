/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:55:16 by molesen           #+#    #+#             */
/*   Updated: 2021/11/24 10:22:37 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list **alst)
{
	t_list	*current;

	if (!alst)
		return ;
	current = *alst;
	ft_putchar('[');
	while (current)
	{
		ft_putstr(current->content);
		ft_putstr("] --> [");
		current = current->next;
	}
	ft_putstr("NULL]\n");
}
