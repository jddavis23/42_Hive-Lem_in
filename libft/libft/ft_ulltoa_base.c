/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_oxtoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 09:50:31 by molesen           #+#    #+#             */
/*   Updated: 2022/03/15 09:50:37 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_ulltoa_helper(char *str, unsigned long long nbr, int base)
{
	int	digit;

	digit = 0;
	if (nbr == 0)
		*str++ = '0';
	else
	{
		while (nbr)
		{
			digit = nbr % base;
			if (digit > 9)
				*str = 'A' + digit - 10;
			else
				*str = '0' + digit;
			nbr = nbr / base;
			str++;
		}
	}
	*str = '\0';
}

char	*ft_ulltoa_base(unsigned long long nbr, int len, int base)
{
	char	*str;

	str = ft_strnew(len);
	ft_ulltoa_helper(str, nbr, base);
	ft_strrev(str);
	return (str);
}
