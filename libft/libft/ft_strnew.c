/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:18:24 by molesen           #+#    #+#             */
/*   Updated: 2021/11/19 13:11:23 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*pnt;
	size_t	i;

	i = 0;
	pnt = (char *)malloc(sizeof(char) * (size + 1));
	if (!pnt)
		return (NULL);
	while (i <= size)
	{
		pnt[i] = '\0';
		i++;
	}
	return (pnt);
}
