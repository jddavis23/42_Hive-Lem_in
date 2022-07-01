/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:30:51 by molesen           #+#    #+#             */
/*   Updated: 2021/11/17 16:55:08 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	remains;
	size_t	i;

	dst_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	i = 0;
	remains = dstsize - dst_len - 1;
	while (i < remains && src[i] != '\0')
	{
		dest[i + dst_len] = src[i];
		i++;
	}	
	if (i == remains)
		dest[dstsize - 1] = '\0';
	else
		dest[dst_len + i] = '\0';
	return (dst_len + src_len);
}
