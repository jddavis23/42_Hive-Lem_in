/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:32:28 by molesen           #+#    #+#             */
/*   Updated: 2021/11/23 09:13:54 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*pnt;

	if (size == 0)
		return (NULL);
	pnt = (void *)malloc(size);
	if (pnt != NULL)
		ft_memset(pnt, 0, size);
	return (pnt);
}
