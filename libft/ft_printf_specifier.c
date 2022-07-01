/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:00:37 by molesen           #+#    #+#             */
/*   Updated: 2022/02/22 13:00:39 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	checks if any of the specifiers inputtet is correct	*/

int	spec_check(t_flag *flag, int a, int b, int c)
{
	if (flag->spec == a)
		return (TRUE);
	else if (flag->spec == b)
		return (TRUE);
	else if (flag->spec == c)
		return (TRUE);
	return (FALSE);
}

/*	readjustments on the flags before using them	*/

void	ft_flag_adjuster(t_flag *flag)
{
	if (flag->prec >= 0 && flag->spec != 'f')
		flag->zero = '1';
	if (flag->star_p == '*' && flag->prec < 0)
	{
		if (flag->width > flag->len && flag->zero == '0')
			flag->prec = -1;
		else
		{
			flag->prec = -1;
			flag->minus = '-';
		}
	}
	if (flag->star_w == '*' && flag->width < 0)
	{
		flag->width *= -1;
		flag->minus = '-';
		flag->zero = '1';
	}
	if (flag->prec >= flag->width && spec_check(flag, 'c', 's', 'p') == FALSE)
		flag->width = -1;
}

/*	narrows down correct specifier and resets i in main loop to correct pos	*/

void	ft_specifier_check(const char *format, t_flag *flag, va_list *arg)
{
	if (flag->space == ' ' && flag->plus == '+')
		flag->space = '1';
	if (flag->plus == '+')
		flag->space = '1';
	if (flag->minus == '-')
		flag->zero = '1';
	if (*format == 'c' || *format == 's' || *format == 'p')
		ft_csp_print(format, flag, arg);
	else if (*format == 'd' || *format == 'i' || *format == 'u')
		ft_diu_print(format, flag, arg);
	else if (*format == 'o' || *format == 'x' || *format == 'X')
		ft_ox_print(format, flag, arg);
	else if (*format == 'f' || *format == '%')
		ft_fp_print(format, flag, arg);
	else
		return ;
	ft_i_reset(format, flag);
}
