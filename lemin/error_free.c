/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:31:48 by molesen           #+#    #+#             */
/*   Updated: 2022/09/13 15:31:49 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*	frees all the elements in 2d int array	*/

int	**free2d_int(int **links, int j, int end)
{
	int	i;

	i = 0;
	if (links[i])
	{
		free(links[i]);
		links[i] = NULL;
	}
	++i;
	while (i < j)
	{
		free(links[i]);
		links[i] = NULL;
		++i;
	}
	if (links[end])
	{
		free(links[end]);
		links[end] = NULL;
	}
	free(links);
	return (NULL);
}

/*	frees allocated rooms	*/

char	**ft_free_rooms(t_room *pass, char **dest)
{
	int	i;

	i = 0;
	while (i < pass->total)
	{
		if (dest[i])
			ft_strdel(&dest[i]);
		i++;
	}
	free(dest);
	return (NULL);
}
