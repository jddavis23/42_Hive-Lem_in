/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 19:03:03 by molesen           #+#    #+#             */
/*   Updated: 2022/03/30 19:03:05 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	initial checks before creating the new string	*/

int	ft_init_checks(char *str, t_flag *flag)
{
	int	len;

	len = ft_strlen(str);
	if (str[0] == '-' && spec_check(flag, 'd', 'n', 'f') == TRUE)
		--len;
	if (ft_strcmp(str, "0") == 0 && flag->prec == 0 && \
		spec_check(flag, 'c', 's', 'p') == FALSE && flag->spec != 'f')
	{
		str[0] = '\0';
		len = 0;
	}
	else if (ft_strcmp(str, "0") == 0 && flag->prec <= 1 && flag->spec == 'o')
		flag->hash = FALSE;
	return (len);
}

/*	puts 0x into string	*/

void	*ft_hash_print(char *temp, t_flag *flag, int *index)
{
	ft_memset(temp, '0', 1);
	++(*index);
	if (flag->spec == 'x')
	{
		++(*index);
		ft_memset(&temp[1], 'x', 1);
	}
	if (flag->spec == 'X')
	{
		++(*index);
		ft_memset(&temp[1], 'X', 1);
	}
	return (temp);
}

/*	if the corresponding flag is true we put it into the string	*/

void	*ft_sign_print(char *new, char *str, t_flag *flag, int *i)
{
	if (str[0] == '-')
	{
		ft_memset(new, '-', 1);
		++(*i);
	}
	else if (flag->plus == '+')
	{
		ft_memset(new, '+', 1);
		++(*i);
	}
	else if (flag->space == ' ')
	{
		ft_memset(new, ' ', 1);
		++(*i);
	}
	return (new);
}

/*	checks if we need to have enough malloc for a sign or hash	*/

int	ft_sign_check(t_flag *flag, char *str)
{
	int	total;

	total = 0;
	if (spec_check(flag, 'c', 's', 'p') == FALSE)
	{
		if (str[0] == '-' || flag->plus == '+' || flag->space == ' ')
			++total;
		if (flag->hash == TRUE && spec_check(flag, 'o', 'x', 'X') == TRUE)
			++total;
		if (flag->hash == TRUE && spec_check(flag, 'n', 'x', 'X') == TRUE)
			++total;
	}
	return (total);
}

/*	calculates length of str that needs to be malloced	*/

void	ft_print_calc(char *str, t_flag *flag, va_list *arg)
{
	int		len_until_dec;
	int		decimal_len;
	char	*temp;

	flag->len = ft_strlen(str);
	ft_flag_adjuster(flag);
	if (flag->spec == 'f' && flag->prec == -1)
	{
		len_until_dec = ft_strlen_stop(str, '.') + 1;
		decimal_len = ft_strlen(&str[len_until_dec]);
		if (decimal_len != 6)
		{
			temp = str;
			str = ft_strjoin(temp, "0");
			ft_strdel(&temp);
			++flag->len;
		}
	}
	ft_apply_prec(str, flag, arg);
}
