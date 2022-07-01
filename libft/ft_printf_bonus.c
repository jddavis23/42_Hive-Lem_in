/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:10:09 by molesen           #+#    #+#             */
/*   Updated: 2022/03/14 16:10:10 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	checks each string to see if it is what user has written	*/

static int	ft_color_check(const char *str, int len)
{
	if (ft_strncmp(str, "reset", len) == 0)
		ft_putstr("\033[0m");
	else if (ft_strncmp(str, "bold", len) == 0)
		ft_putstr("\033[1m");
	else if (ft_strncmp(str, "red", len) == 0)
		ft_putstr("\033[31m");
	else if (ft_strncmp(str, "green", len) == 0)
		ft_putstr("\033[32m");
	else if (ft_strncmp(str, "yellow", len) == 0)
		ft_putstr("\033[33m");
	else if (ft_strncmp(str, "blue", len) == 0)
		ft_putstr("\033[34m");
	else if (ft_strncmp(str, "purple", len) == 0)
		ft_putstr("\033[35m");
	else if (ft_strncmp(str, "cyan", len) == 0)
		ft_putstr("\033[36m");
	else if (ft_strncmp(str, "white", len) == 0)
		ft_putstr("\033[37m");
	else if (ft_strncmp(str, "uncolor", len) == 0)
		ft_putstr("\033[39m");
	else
		return (FALSE);
	return (TRUE);
}

/*	bonus color print - starts the loop to check if there is a valid color	*/

int	ft_color_print(const char *str, t_flag *flag)
{
	int	len;

	len = ft_strlen_stop((char *)str, '}');
	if (ft_color_check(str, len) == FALSE)
		return (FALSE);
	flag->i += len;
	return (TRUE);
}
