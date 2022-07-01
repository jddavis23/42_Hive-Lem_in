/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_of_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:13:16 by molesen           #+#    #+#             */
/*   Updated: 2021/11/17 15:22:12 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_end_of_str(char const *s, int (*f)(int))
{
	int	end;
	int	len;

	len = ft_strlen((char *)s);
	end = len - 1;
	while (f(s[end]) == 1 && end > 0)
		end--;
	return (end);
}
