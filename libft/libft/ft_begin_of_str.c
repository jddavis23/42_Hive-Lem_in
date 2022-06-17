/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_begin_of_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:12:40 by molesen           #+#    #+#             */
/*   Updated: 2021/11/23 11:04:49 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_begin_of_str(char const *s, int (*f)(int))
{
	int	start;
	int	len;

	start = 0;
	len = ft_strlen((char *)s);
	while (f(s[start]) == 1 && start < len)
		start++;
	if (start == len)
		return (-1);
	return (start);
}
