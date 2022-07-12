/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:12:51 by jdavis            #+#    #+#             */
/*   Updated: 2022/07/12 14:07:46 by jdavis           ###   ########.fr       */
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
			ft_printf("END\n'");
			return ;
		}
		++j;
	}
	if (j == 1)
		return ;
	while (links[indx][i] >= 0)
	{
		ft_printf("room %s  room indx %i prev %i\n", pass->rooms[links[indx][i]], links[indx][i], indx);
		//if (indx == 1)
		//	exit (0);
		if (links[indx][i] == indx)
			++i;
		if (links[indx][i] == 0)
			++i;
		if (links[indx][i] < 0)
			return ;
		if (dist >= pass->distance[links[indx][i]] && pass->distance[links[indx][i]] != 0) //double check
			return ;
		if (dist + 1 < pass->distance[links[indx][i]] && pass->distance[links[indx][i]] != 0)
			pass->distance[links[indx][i]] = dist + 1;
		else if (dist + 1 > pass->distance[links[indx][i]] && pass->distance[links[indx][i]] == 0)
			pass->distance[links[indx][i]] = dist + 1;
		ft_printf("moon %s distance %i  prev dist %i\n\n", pass->rooms[links[indx][i]], pass->distance[links[indx][i]], dist);
		if (links[indx][i] != 0)
		{
			ft_printf("HERE\n");
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
	i = 0;
	while (i < pass->total)
	{
		ft_printf("room %s  distance %i\n", pass->rooms[i], pass->distance[i]);
		++i;
	}
}
