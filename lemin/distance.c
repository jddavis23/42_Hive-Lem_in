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

void	recurs(t_room *pass, int **links, int dist, int indx, int prev)
{
	int	i;
	int	j;
	static int k = 0;

	j = 0;
	i = 0;
	while (links[indx][j] >= 0)
	{
		if (links[indx][j] == pass->end)
			return ;
		++j;
	}
	if ((j == 1 && indx != 0))// || (indx == 0 && dist > 0))
	{
		pass->distance[indx] = -1;
		++k;
		return ;
	}
	while (links[indx][i] >= 0)
	{
		//if (links[indx][i] == indx)
		//	++i; else 
		if (links[indx][i] == 0)
			++i;
		if (links[indx][i] < 0)
			return ;
		while ((links[indx][i] >= 0 && (dist + 1 < pass->distance[links[indx][i]])) || links[indx][i] == prev)// || pass->distance[links[indx][i]] == 1)
			++i;
		if (links[indx][i] < 0)
			return ;
		if (dist + 1 > pass->distance[links[indx][i]] ||  prev == 0)
		{
			//if (pass->distance[links[indx][i]] != 1)
				pass->distance[links[indx][i]] = dist + 1;
		}
		if (links[indx][i] != 0)
			recurs(pass, pass->links, pass->distance[links[indx][i]], links[indx][i], indx);
		if (k)
		{
			j = 0;
			while (pass->links[indx][j] != -1)
				++j;
			if (j < 3)
				pass->distance[indx] = -1;
			else
				--k;
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
	recurs(pass, pass->links, 0, 0, 0);
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
