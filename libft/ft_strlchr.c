/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:07:05 by jdavis            #+#    #+#             */
/*   Updated: 2022/07/11 13:07:10 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_strlchr(const char *str, int c, int len)
{
	int	i;

	i = 0;
	if (str)
	{
		while (i < len)
		{
			if (str[i] == c)
				return (&str[i]);
			++i;
		}
	}
	return (NULL);
}
