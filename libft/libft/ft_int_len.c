/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:24:05 by molesen           #+#    #+#             */
/*   Updated: 2022/02/28 15:24:16 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_calc(int nbr)
{
	int	counter;

	counter = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr /= 10;
		counter++;
	}
	return (counter);
}

int	ft_int_len(int n)
{
	if (n < 0)
	{
		if (n == -2147483648)
			return (11);
		else
		{
			n *= -1;
			return (ft_len_calc(n) + 1);
		}
	}
	return (ft_len_calc(n));
}
