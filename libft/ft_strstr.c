/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:46:32 by molesen           #+#    #+#             */
/*   Updated: 2021/11/18 12:50:35 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char const *haystack, const char *needle)
{
	int		i;
	int		needle_len;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	while (haystack[i] != '\0')
	{
		if (strncmp(&haystack[i], needle, needle_len) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
