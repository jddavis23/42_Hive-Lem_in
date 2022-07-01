/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fp_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 09:36:03 by molesen           #+#    #+#             */
/*   Updated: 2022/03/15 09:36:31 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	converts to correct float based on flags	*/

static char	*ft_convert_length_f(char *str, t_flag *flag, double number,
			long double b_nbr)
{
	if (flag->prec != -1)
	{
		if (flag->b_l)
			str = ft_ftoa(b_nbr, flag->prec, flag);
		else
			str = ft_ftoa((double)number, flag->prec, flag);
	}
	else
	{
		if (flag->b_l)
			str = ft_ftoa(b_nbr, 6, flag);
		else
			str = ft_ftoa((double)number, 6, flag);
	}
	return (str);
}

/*	percentage calculator & cals digit print function	*/

static void	ft_percentage_print(const char *format, t_flag *flag, va_list *arg)
{
	char	*str;

	str = NULL;
	flag->prec = -1;
	if (*format == '%')
	{
		flag->spec = 'u';
		str = ft_strnew(1);
		str[0] = '%';
		ft_print_calc(str, flag, arg);
	}
}

/*	checks if the specifier is float or percentage sign	*/

void	ft_fp_print(const char *format, t_flag *flag, va_list *arg)
{
	double		number;
	long double	b_number;
	char		*str;

	str = NULL;
	if (*format == 'f')
	{
		b_number = -1;
		number = -1;
		flag->spec = 'f';
		if (flag->b_l == TRUE)
		{
			b_number = va_arg(*arg, long double);
			str = ft_convert_length_f(str, flag, number, b_number);
		}
		else
		{
			number = va_arg(*arg, double);
			str = ft_convert_length_f(str, flag, number, b_number);
		}
		ft_print_calc(str, flag, arg);
	}
	else
		ft_percentage_print(format, flag, arg);
}
