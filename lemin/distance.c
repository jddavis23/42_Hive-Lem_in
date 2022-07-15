/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:12:51 by jdavis            #+#    #+#             */
/*   Updated: 2022/07/12 16:53:09 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	recurs(t_room *pass, int **links, int dist, int indx)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (links[indx][j] >= 0)
	{
		if (links[indx][j] == pass->end)
		{
			return ;
		}
		++j;
	}
	if (j == 1 && indx != 0)
		return ;
	while (links[indx][i] >= 0)
	{
		//if (indx == 1)
		//	exit (0);
		if (links[indx][i] == indx)
			++i;
		if (links[indx][i] == 0)
			++i;
		if (links[indx][i] < 0)
			return ;
		while (links[indx][i] >= 0 && dist >= pass->distance[links[indx][i]] && pass->distance[links[indx][i]] != 0) //double check
			++i;
		if (links[indx][i] < 0)
			return ;
		if (dist + 1 < pass->distance[links[indx][i]] && pass->distance[links[indx][i]] != 0)
			pass->distance[links[indx][i]] = dist + 1;
		else if (dist + 1 > pass->distance[links[indx][i]] && pass->distance[links[indx][i]] == 0)
			pass->distance[links[indx][i]] = dist + 1;
		if (links[indx][i] != 0)
		{
			recurs(pass, pass->links, pass->distance[links[indx][i]], links[indx][i]);
		}
		++i;
	}
}

void	distance(t_room *pass)
{
	int	i;

	i = 0;
	pass->distance = (int *) malloc(pass->total * sizeof(int));
	if (!pass->distance)
	{
		//free evrything
		exit (0);
	}
	while (i < pass->total)
		pass->distance[i++] = 0;
	recurs(pass, pass->links, pass->distance[0], 0);
	pass->distance[pass->end] = pass->total;
	i = 0;
	ft_printf("\n");
	while (i < pass->total)
	{
		ft_printf("room %s  distance %i\n", pass->rooms[i], pass->distance[i]);
		++i;
	}
	ft_printf("\n");
}
