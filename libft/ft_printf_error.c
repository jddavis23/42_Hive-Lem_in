/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:23:17 by molesen           #+#    #+#             */
/*   Updated: 2022/03/28 11:23:19 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	error when creating string	*/

void	ft_str_error(char *str, t_flag *flag)
{
	if (str)
		ft_strdel(&str);
	flag->ret = -1;
}

/*	error anywhere else	*/

int	ft_error(t_flag *flag)
{
	if (flag)
		free(flag);
	return (-1);
}
