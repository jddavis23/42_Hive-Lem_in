/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:35:34 by molesen           #+#    #+#             */
/*   Updated: 2021/11/01 13:12:23 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t	dst_len;
	size_t	i;

	i = 0;
	dst_len = ft_strlen(dest);
	ft_strcpy(&dest[i + dst_len], src);
	return (dest);
}
