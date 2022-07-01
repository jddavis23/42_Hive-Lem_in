/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:17:57 by molesen           #+#    #+#             */
/*   Updated: 2021/11/26 17:33:31 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_strsplit_calc(char **dest, char *pnt, char c)
{
	int	i;
	int	word;
	int	len;

	i = 0;
	word = 0;
	while (pnt[i] != '\0')
	{
		if (pnt[i] == c)
			i++;
		else
		{
			len = ft_strlen_stop(&pnt[i], c);
			dest[word] = (char *)malloc(sizeof(char) * (len + 1));
			if (!dest[word])
				return (ft_free2d(dest));
			ft_strncpy(dest[word], &pnt[i], len);
			dest[word][len] = '\0';
			word++;
			i += len;
		}
	}
	dest[word] = 0;
	return (dest);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**dest;
	char	*pnt;
	int		word_count;

	pnt = (char *)s;
	dest = NULL;
	if (s)
	{
		word_count = ft_word_count(pnt, c);
		dest = (char **)malloc(sizeof(char *) * (word_count + 1));
		if (!dest)
			return (NULL);
		dest = ft_strsplit_calc(dest, pnt, c);
	}
	return (dest);
}
