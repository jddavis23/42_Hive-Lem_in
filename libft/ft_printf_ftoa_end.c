/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:21:22 by molesen           #+#    #+#             */
/*   Updated: 2022/03/26 16:21:24 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	rounds up if conditions are meet	*/

static int	ft_round_up(char *str)
{
	if (str[0] == '9')
	{
		str[0] = '0';
		return (TRUE);
	}
	else
	{
		str[0] = str[0] + 1;
		return (FALSE);
	}
}

/*	loops through string to have correct digits	*/

static int	ft_correct_end_loop(char *str, int add, int up)
{
	int	total;
	int	i;

	total = ft_strlen(str) - 1;
	i = total;
	while (i >= 0 && (i >= total || add == TRUE))
	{
		if (str[i] == '.')
			i -= 1;
		if (add == TRUE || up == TRUE)
		{
			if (up == TRUE)
			{
				up = FALSE;
				add = ft_round_up(&str[i]);
			}
			else
				add = ft_round_up(&str[i]);
		}
		i -= 1;
	}
	return (add);
}

/*	correct ending to float calculator based on precision	*/

char	*ft_check_correct_end(char *str, int up)
{
	int		add;
	char	*temp;

	add = FALSE;
	add = ft_correct_end_loop(str, add, up);
	if (add == TRUE)
	{
		temp = ft_strnew(ft_strlen(str) + 1);
		temp[0] = '1';
		ft_strcat(temp, str);
		ft_strdel(&str);
		return (temp);
	}
	else
		return (str);
}
