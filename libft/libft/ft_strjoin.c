/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:10:00 by molesen           #+#    #+#             */
/*   Updated: 2021/11/16 12:52:31 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strjoin_calc(char const *s1, char const *s2, unsigned int
s1_len, unsigned int s2_len)
{
	char			*temp;
	unsigned int	i;
	unsigned int	j;

	temp = (char *)malloc(sizeof(char) * ((s1_len + s2_len) + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		temp[i] = (char)s1[i];
		i++;
	}
	j = 0;
	while (i < (s1_len + s2_len))
		temp[i++] = (char)s2[j++];
	temp[i] = '\0';
	return (temp);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	unsigned int	s1_len;
	unsigned int	s2_len;

	str = NULL;
	if (s1 && s2)
	{
		s1_len = ft_strlen((char *)s1);
		s2_len = ft_strlen((char *)s2);
		str = ft_strjoin_calc(s1, s2, s1_len, s2_len);
	}
	return (str);
}
