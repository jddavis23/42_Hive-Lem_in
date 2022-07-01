/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:56:29 by molesen           #+#    #+#             */
/*   Updated: 2021/11/19 13:12:10 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const unsigned char	*pnt;
	unsigned char		new;
	size_t				i;

	i = 0;
	pnt = (const unsigned char *)str;
	new = (unsigned char)c;
	while (i < n)
	{
		if (pnt[i] == new)
			return ((void *)&pnt[i]);
		i++;
	}
	return (NULL);
}
