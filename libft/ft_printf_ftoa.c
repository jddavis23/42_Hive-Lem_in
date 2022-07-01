/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:59:43 by molesen           #+#    #+#             */
/*   Updated: 2022/03/15 16:59:56 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	adds the needed zeros to the string	*/

static void	ft_itoa_add_zeros(unsigned long long nbr, char *str, int len, \
int neg)
{
	int	i;

	i = 0;
	if (nbr == 0 && len == 0)
		str[i++] = '0';
	while (nbr)
	{
		str[i++] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	while (i < len)
		str[i++] = '0';
	if (neg == -1)
		str[i++] = '-';
	ft_strrev_len(str, i);
	str[i] = '\0';
}

/*	takes number and stores it in a string	*/

static void	ft_fcalc(long long number, char *temp, int neg)
{
	long	nbr;

	if ((long long)number == 0)
	{
		if (neg == 1)
		{
			temp[0] = '-';
			temp[1] = '0';
		}
		else
			temp[0] = '0';
		return ;
	}
	nbr = (long long)number;
	if (neg == 1)
	{
		neg = -1;
		nbr *= neg;
	}
	ft_itoa_add_zeros((double)nbr, temp, 0, neg);
}

/*	calculates if we need to round up or not when deciding decimal length	*/

static int	ft_rounding(long double lnbr, int len, char *temp, int i)
{
	int	nbr;

	if (len != 0)
	{
		lnbr = lnbr * ft_pow(10, len);
		ft_itoa_add_zeros((unsigned long long)lnbr, &temp[i], len, 1);
		nbr = temp[ft_strlen(temp) - 1] - '0';
	}
	else
		nbr = temp[i - 2] - '0';
	lnbr = lnbr - (unsigned long long)lnbr;
	if (lnbr > 0.5)
		return (TRUE);
	else if (lnbr < 0.5)
		return (FALSE);
	if (nbr % 2 != 0)
		return (TRUE);
	return (FALSE);
}

/*	calculates digits	*/

static void	*ft_calc_decimals(long double lnbr, char *temp, int len, \
t_flag *flag)
{
	int		up;
	int		i;
	char	*str;

	i = ft_strlen(temp);
	if (lnbr < 0)
		lnbr *= -1;
	if (len != 0 || (len == 0 && flag->hash == TRUE))
		temp[i++] = '.';
	else
		++i;
	up = ft_rounding(lnbr, len, temp, i);
	str = ft_check_correct_end(temp, up);
	return (str);
}

/*	converts float(double) to str	*/

char	*ft_ftoa(long double number, int len, t_flag *flag)
{
	long double	lnbr;
	int			neg;
	char		*str;

	lnbr = number;
	neg = 0;
	if (1 / number < 0 && (long long)number == 0)
		neg = 1;
	str = ft_strnew(ft_long_len((long long)number) + len + 1 + neg);
	if (1 / number < 0)
		neg = 1;
	ft_fcalc(number, str, neg);
	lnbr = number - (long long)number;
	str = ft_calc_decimals(lnbr, str, len, flag);
	return (str);
}
