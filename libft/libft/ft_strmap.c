/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:50:13 by molesen           #+#    #+#             */
/*   Updated: 2021/11/11 15:49:32 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*dst;
	int		i;
	int		len;

	dst = NULL;
	if (s)
	{
		len = ft_strlen((char *)s);
		dst = (char *)malloc(sizeof(char) * len + 1);
		if (!dst)
			return (NULL);
		i = 0;
		while (i < len)
		{
			dst[i] = f((char)s[i]);
			i++;
		}
		dst[len] = '\0';
	}
	return (dst);
}
