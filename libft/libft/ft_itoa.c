/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:30:28 by molesen           #+#    #+#             */
/*   Updated: 2021/11/18 12:57:30 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_to_string(char *dst, int nb)
{
	if (nb / 10 == 0)
	{
		*dst = nb + '0';
		dst++;
		*dst = '\0';
		return (dst);
	}
	dst = ft_to_string(dst, nb / 10);
	*dst = nb % 10 + '0';
	dst++;
	*dst = '\0';
	return (dst);
}

static char	*ft_neg_calc(char *dst, int n)
{
	dst[0] = '-';
	if (n == -2147483648)
	{
		dst[1] = '2';
		n = 147483648;
		ft_to_string(&dst[2], n);
	}
	else
	{
		n *= -1;
		ft_to_string(&dst[1], n);
	}
	return (dst);
}

char	*ft_itoa(int n)
{
	char	*dst;
	size_t	len;

	len = ft_int_len(n);
	dst = (char *)ft_memalloc(sizeof(char) * len + 1);
	if (!dst)
		return (NULL);
	if (n < 0)
		ft_neg_calc(dst, n);
	else
		ft_to_string(dst, n);
	return (dst);
}
