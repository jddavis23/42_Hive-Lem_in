/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:23:32 by molesen           #+#    #+#             */
/*   Updated: 2021/11/25 09:26:14 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_new_str(char const *s, char *str, int start, int end)
{
	int	i;

	i = 0;
	while (start < end + 1)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s)
{
	char	*str;
	int		len;
	int		start;
	int		end;

	str = NULL;
	if (s)
	{
		len = 0;
		start = ft_begin_of_str(s, &ft_isspace_s);
		if (start != -1)
		{
			end = ft_end_of_str(s, &ft_isspace_s);
			len = end - start + 1;
		}
		str = (char *)malloc(sizeof(char) * (len + 1));
		if (!str)
			return (NULL);
		if (start != -1)
			str = ft_new_str(s, str, start, end);
		else
			str[0] = '\0';
	}
	return (str);
}
