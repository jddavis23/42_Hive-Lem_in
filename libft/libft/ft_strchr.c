/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:20:06 by molesen           #+#    #+#             */
/*   Updated: 2021/11/08 15:46:25 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*pnt;
	int		i;

	i = 0;
	pnt = (char *)str;
	while (pnt[i] != c)
	{
		i++;
		if (pnt[i - 1] == '\0')
			return (NULL);
	}
	return (&pnt[i]);
}
