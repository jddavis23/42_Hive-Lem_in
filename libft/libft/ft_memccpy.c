/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:18:47 by molesen           #+#    #+#             */
/*   Updated: 2021/11/19 13:12:25 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c,
size_t n)
{
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;
	unsigned char		new;

	dst_ptr = (unsigned char *)dst;
	src_ptr = (const unsigned char *)src;
	new = (unsigned char)c;
	while (n-- > 0)
	{
		*dst_ptr = *src_ptr;
		if (*src_ptr == new)
		{
			dst_ptr++;
			return (dst_ptr);
		}
		src_ptr++;
		dst_ptr++;
	}
	return (NULL);
}
