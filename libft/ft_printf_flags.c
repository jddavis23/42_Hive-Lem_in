/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:00:28 by molesen           #+#    #+#             */
/*   Updated: 2022/02/22 13:00:30 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	if length has been found it will be stored in the struct 	*/

static int	ft_hhll_flag_check(const char *format, t_flag *flag, int on,
			int *pnt)
{
	if (*format == 'h' && format[1] == 'h')
	{
		flag->hh = on;
		*pnt += 1;
	}
	else if (*format == 'h')
		flag->h = on;
	else if (*format == 'l' && format[1] == 'l')
	{
		flag->ll = on;
		*pnt += 1;
	}
	else if (*format == 'l')
		flag->l = on;
	else if (*format == 'L')
		flag->b_l = on;
	else
		return (FALSE);
	*pnt += 1;
	return (TRUE);
}

/*	if width or precision is found the numbers will be stored in struct	*/

static void	ft_width_calc(const char *format, int *digit, int *pnt, \
va_list *arg)
{
	int	i;
	int	first;
	int	nbr;

	i = 0;
	first = TRUE;
	*digit = 0;
	if (format[i] == '*')
	{
		nbr = va_arg(*arg, int);
		*digit = nbr;
		++i;
	}
	else
	{
		while (ft_isdigit(format[i]) == 1)
		{
			if (first == FALSE)
				*digit *= 10;
			nbr = format[i++] - '0';
			*digit += nbr;
			first = FALSE;
		}
	}
	*pnt += i;
}

/*	first flag check - basic flags #0-+' ' - result saved in struct	*/

static int	ft_flag_check(const char *format, t_flag *flag, int on, int *pnt)
{
	if (*format == '-')
		flag->minus = '-';
	else if (*format == '+')
		flag->plus = '+';
	else if (*format == ' ')
		flag->space = ' ';
	else if (*format == '0' && format[-1] != '0')
		flag->zero = '0';
	else if (*format == '#')
		flag->hash = on;
	else
		return (FALSE);
	*pnt += 1;
	return (on);
}

/*	loops through the different flag posibilities in order	*/

static void	ft_flag_loop(const char *format, t_flag *flag, va_list *arg,
			int *pnt)
{
	while (flag->spec == '1' && ft_flag_check(&format[*pnt], flag, TRUE, pnt) \
		== TRUE)
		ft_specifier_check(&format[*pnt], flag, arg);
	while (flag->spec == '1' && (ft_isdigit(format[*pnt]) == 1 || \
		format[*pnt] == '*'))
	{
		if (format[*pnt] == '*')
			flag->star_w = '*';
		ft_width_calc(&format[*pnt], &flag->width, pnt, arg);
		ft_specifier_check(&format[*pnt], flag, arg);
	}
	while (flag->spec == '1' && format[*pnt] == '.')
	{
		*pnt += 1;
		if (format[*pnt] == '*')
			flag->star_p = '*';
		ft_width_calc(&format[*pnt], &flag->prec, pnt, arg);
		ft_specifier_check(&format[*pnt], flag, arg);
	}
	if (flag->spec == '1' && ft_hhll_flag_check(&format[*pnt], flag, TRUE, \
		pnt) == TRUE)
		ft_specifier_check(&format[*pnt], flag, arg);
}

/*	keeps track of if specifier has been found or not	*/

void	ft_flag_checker(const char *format, t_flag *flag, va_list *arg)
{
	int		i;
	int		*pnt;

	i = 0;
	pnt = &i;
	ft_specifier_check(&format[i], flag, arg);
	if (flag->spec == '1')
		ft_flag_loop(format, flag, arg, pnt);
	if (flag->spec == '1')
		flag->ret = 0;
}
