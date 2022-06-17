/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:17:23 by molesen           #+#    #+#             */
/*   Updated: 2021/11/23 11:05:57 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *haystack, const char *needle, size_t len)
{
	int		i;
	int		needle_len;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	while (haystack[i] != '\0' && i <= (int)len - needle_len)
	{
		if (needle_len <= (int)len)
		{
			if (strncmp(&haystack[i], needle, needle_len) == 0)
				return ((char *)&haystack[i]);
		}
		else
			if (strncmp(&haystack[i], needle, (int)len - i + 1) == 0)
				return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
