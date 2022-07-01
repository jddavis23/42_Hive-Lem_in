/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:27:51 by molesen           #+#    #+#             */
/*   Updated: 2021/11/18 12:58:06 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_word_count(char *str, char c)
{
	int	word_count;
	int	i;

	word_count = 0;
	i = 0;
	if (str[0] != c)
		word_count++;
	while (str[i] != '\0')
	{
		if (str[i] != c && str[i - 1] == c)
			word_count++;
		i++;
	}
	return (word_count);
}
