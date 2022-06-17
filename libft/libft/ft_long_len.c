/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:40:41 by molesen           #+#    #+#             */
/*   Updated: 2022/03/08 15:41:24 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_calc(long long nbr)
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

int	ft_long_len(long long nbr)
{
	if (nbr < 0)
	{
		if (nbr < -9223372036854775800)
			return (20);
		else
		{
			nbr *= -1;
			return (ft_len_calc(nbr) + 1);
		}
	}
	return (ft_len_calc(nbr));
}
