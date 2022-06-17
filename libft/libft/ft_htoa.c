/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:29:06 by molesen           #+#    #+#             */
/*   Updated: 2022/03/14 18:29:09 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_count(uintptr_t addr)
{
	int	count;

	count = 0;
	while (addr > 0)
	{
		++count;
		addr /= 16;
	}
	return (count);
}

char	*ft_htoa(char *dst, uintptr_t addr)
{
	unsigned int	len;
	unsigned int	i;
	unsigned int	mod;

	len = ft_count(addr) + 1;
	i = len - 2;
	while (addr > 0)
	{
		mod = addr % 16;
		if (mod >= 10)
			dst[i--] = (mod - 10) + 'a';
		else
			dst[i--] = mod + '0';
		addr /= 16;
	}
	dst[len - 1] = '\0';
	return (dst);
}
