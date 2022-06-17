/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prec_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 19:00:00 by molesen           #+#    #+#             */
/*   Updated: 2022/03/30 19:00:02 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*	printing new string depending on given length	*/

static void	ft_basic_sp_prec(char *str, t_flag *flag, va_list *arg, int len)
{
	char	*new;

	new = ft_strnew(len);
	if (!new)
	{
		ft_str_error(str, flag);
		return ;
	}
	new = ft_strncpy(new, str, len);
	ft_strdel(&str);
	ft_apply_width(new, flag, arg);
}

/*	sets right signs and char in string if precision is true	*/

static void	*ft_prec_memset(char *new, t_flag *flag, int *i)
{
	if (spec_check(flag, 'o', 'x', 'X') == TRUE && flag->hash == TRUE)
		ft_hash_print(new, flag, i);
	if (spec_check(flag, 'c', 's', 'p') == TRUE)
		ft_memset(&new[*i], ' ', flag->prec - flag->len);
	else
		ft_memset(&new[*i], '0', flag->prec - flag->len);
	return (new);
}

/*	applies precision and adds if there is a sign	*/

static void	ft_if_prec(char *str, t_flag *flag, va_list *arg, int total)
{
	char	*new;
	int		s_i;
	int		i;

	s_i = 0;
	i = 0;
	if (str[0] == '-' && spec_check(flag, 'd', 'n', 'f') == TRUE)
		++s_i;
	new = ft_strnew(flag->prec + total);
	if (!new)
	{
		ft_str_error(str, flag);
		return ;
	}
	if (total > 0 && spec_check(flag, 'd', 'n', 'f') == TRUE)
		ft_sign_print(new, str, flag, &i);
	ft_prec_memset(new, flag, &i);
	if (flag->spec == 'o')
		ft_strcpy(&new[flag->prec - flag->len], &str[s_i]);
	else if (spec_check(flag, 'c', 's', 'p') == TRUE)
		ft_strcpy(new, str);
	else
		ft_strcpy(&new[i + flag->prec - flag->len], &str[s_i]);
	ft_strdel(&str);
	ft_apply_width(new, flag, arg);
}

/*	applies sign if no precision found	*/

static void	ft_no_prec(char *str, t_flag *flag, va_list *arg, int total)
{
	char	*new;
	int		s_i;
	int		i;

	s_i = 0;
	i = 0;
	if (str[0] == '-' && spec_check(flag, 'd', 'n', 'f') == TRUE)
		++s_i;
	new = ft_strnew(flag->len + total);
	if (!new)
	{
		ft_str_error(str, flag);
		return ;
	}
	if (total > 0 && spec_check(flag, 'd', 'n', 'f') == TRUE)
	{
		ft_sign_print(new, str, flag, &i);
	}
	if (spec_check(flag, 'o', 'x', 'X') == TRUE && flag->hash == TRUE)
		ft_hash_print(new, flag, &i);
	ft_strcpy(&new[i], &str[s_i]);
	ft_strdel(&str);
	ft_apply_width(new, flag, arg);
}

/*	creates new str with signs and precision applied	*/

void	ft_apply_prec(char *str, t_flag *flag, va_list *arg)
{
	int	total;

	flag->len = ft_init_checks(str, flag);
	total = ft_sign_check(flag, str);
	if (flag->spec == 'p' && ft_strcmp(str, "0x0") == 0 && flag->prec == 0)
		ft_basic_sp_prec(str, flag, arg, 2);
	else if (flag->prec < flag->len && flag->prec >= 0 && flag->spec == 's')
		ft_basic_sp_prec(str, flag, arg, flag->prec);
	else if (flag->prec >= 0 && flag->prec > flag->len)
		ft_if_prec(str, flag, arg, total);
	else if (total != 0 && spec_check(flag, 'c', 's', 'p') == FALSE)
		ft_no_prec(str, flag, arg, total);
	else
		ft_apply_width(str, flag, arg);
}
