/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:47:11 by molesen           #+#    #+#             */
/*   Updated: 2022/03/01 12:47:13 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	createed string from arg depending on specifier	*/

static char	*ft_str_creater(char *str_arg, char c)
{
	char	*str;

	if (c == 'c')
		str = ft_strnew(1);
	else if (!str_arg)
		str = ft_strnew(ft_strlen("(null)"));
	else
		str = ft_strnew(ft_strlen(str_arg));
	if (!str)
		return (NULL);
	if (c == 'c')
		ft_strncpy(str, "\0", 1);
	else if (!str_arg)
		ft_strcpy(str, "(null)");
	else
		ft_strcpy(str, str_arg);
	return (str);
}

/*	calls function that will calculate string	*/

static void	ft_print_str(char *str, t_flag *flag, va_list *arg)
{
	if (!str && flag->spec != 'c')
	{
		ft_str_error(str, flag);
		return ;
	}
	ft_print_calc(str, flag, arg);
}

/*	narrows down specifier and get arg	*/

void	ft_csp_print(const char *format, t_flag *flag, va_list *arg)
{
	char	*str;

	str = NULL;
	flag->zero = '1';
	if (*format == 'c')
	{
		flag->spec = 'c';
		str = ft_str_creater(" ", flag->spec);
	}
	else if (*format == 's')
	{
		flag->spec = 's';
		str = ft_str_creater((char *)va_arg(*arg, char *), flag->spec);
	}
	else if (*format == 'p')
	{
		flag->spec = 'p';
		str = addr_to_str((unsigned long long)va_arg(*arg, unsigned long long), \
		flag->prec);
	}
	ft_print_str(str, flag, arg);
}
