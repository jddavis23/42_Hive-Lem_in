/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 11:28:12 by molesen           #+#    #+#             */
/*   Updated: 2022/02/21 13:28:27 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	keep track of the index of the main string	*/

void	ft_i_reset(const char *format, t_flag *flag)
{
	int		i;

	i = 0;
	while (format[i - 1] != '%')
		i--;
	i *= -1;
	flag->i += i;
}

/*	initializes flags or reset them	*/

static void	ft_initialize_flag(t_flag *flag, int first)
{
	flag->spec = '1';
	flag->hash = FALSE;
	flag->space = '1';
	flag->minus = '1';
	flag->plus = '1';
	flag->zero = '1';
	flag->width = -1;
	flag->prec = -1;
	flag->hh = FALSE;
	flag->h = FALSE;
	flag->l = FALSE;
	flag->ll = FALSE;
	flag->b_l = FALSE;
	flag->len = 0;
	flag->star_w = '1';
	flag->star_p = '1';
	if (first == TRUE)
	{
		flag->i = 0;
		flag->ret = 0;
	}
}

/*	check each char in the main str	*/

static void	ft_check_char(const char *format, t_flag *flag, va_list *arg)
{
	char	c;

	c = '{';
	if (format[flag->i] != '%')
	{
		if (format[flag->i] == '{')
		{
			++flag->i;
			if (ft_color_print(&format[flag->i], flag) == FALSE)
				flag->ret += write(1, &format[--flag->i], 1);
		}
		else
			flag->ret += write(1, &format[flag->i], 1);
	}
	else
	{
		++flag->i;
		ft_flag_checker(&format[flag->i], flag, arg);
		ft_initialize_flag(flag, FALSE);
	}
}

/*	initializes flags, calls function to make the loop	*/

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	t_flag	*flag;
	int		ret;

	flag = (t_flag *) malloc(sizeof(t_flag));
	if (!flag)
		return (ft_error(flag));
	ft_initialize_flag(flag, TRUE);
	va_start(arg, format);
	if (format)
	{
		if (!(ft_strcmp(format, "%") == 0))
		{
			while (format[flag->i] != '\0' && flag->ret != -1)
			{
				ft_check_char(format, flag, &arg);
				++flag->i;
			}
		}
	}
	va_end(arg);
	ret = flag->ret;
	free(flag);
	return (ret);
}
