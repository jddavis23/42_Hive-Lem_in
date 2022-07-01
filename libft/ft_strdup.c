/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:45:51 by molesen           #+#    #+#             */
/*   Updated: 2021/11/02 13:00:49 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dup;
	char	*pnt;
	size_t	len;

	pnt = (char *)str;
	len = ft_strlen(str) + 1;
	dup = (char *)malloc(len * sizeof(char));
	if (dup != NULL)
		ft_strcpy(dup, pnt);
	return (dup);
}
