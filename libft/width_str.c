/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 19:01:44 by molesen           #+#    #+#             */
/*   Updated: 2022/03/30 19:01:45 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*	prints final string	*/

static void	ft_print_final_str(char *str, t_flag *flag, char c)
{
	if (flag->spec == 'c' && flag->minus == '-')
		flag->ret += write(1, &c, 1);
	flag->ret += write(1, str, ft_strlen(str));
	if (flag->spec == 'c' && flag->minus == '1')
		flag->ret += write(1, &c, 1);
	flag->len = ft_strlen(str);
	ft_strdel(&str);
}

/*	join string based on minus flag	*/

static char	*ft_minus_decide_join(char *temp, char *str, t_flag *flag, int i)
{
	char	*new;

	if (flag->minus == '1')
		new = ft_strjoin(temp, &str[i]);
	else
		new = ft_strjoin(str, temp);
	ft_strdel(&str);
	ft_strdel(&temp);
	return (new);
}

/*	width get's applied to the string	*/

static char	*ft_collect_remainder_width(char *str, t_flag *flag, int len)
{
	char	*temp;
	char	*new;
	int		i;

	i = 0;
	temp = ft_strnew(flag->width - len + ft_sign_check(flag, str));
	if (!temp)
		return (NULL);
	if (spec_check(flag, 'o', 'x', 'X') == TRUE && flag->hash == TRUE && \
		flag->zero == '0' && flag->prec == -1)
		ft_hash_print(temp, flag, &i);
	if (spec_check(flag, 'c', 's', 'p') == FALSE && flag->zero == '0')
	{
		if (flag->prec == -1 && flag->minus == '1')
			ft_sign_print(temp, str, flag, &i);
		else if (flag->prec < len && flag->spec == 'f')
			ft_sign_print(temp, str, flag, &i);
		ft_memset(&temp[i], '0', flag->width - len);
	}
	else
		ft_memset(&temp[i], ' ', flag->width - len);
	new = ft_minus_decide_join(temp, str, flag, i);
	return (new);
}

/*	applies the width and calls function to print final string	*/

void	ft_apply_width(char *str, t_flag *flag, va_list *arg)
{
	int		len;
	char	c;
	char	*new;

	len = ft_strlen(str);
	if (flag->spec == 'c')
	{
		len = 1;
		c = (char)va_arg(*arg, int);
	}
	if (flag->width > len)
	{
		new = ft_collect_remainder_width(str, flag, len);
		if (!new)
		{
			ft_str_error(str, flag);
			return ;
		}
		ft_print_final_str(new, flag, c);
	}
	else
		ft_print_final_str(str, flag, c);
}
