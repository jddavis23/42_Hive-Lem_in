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
	// if (pass->distance[6] == 10)
	// 	exit(0);
	while (links[indx][j] >= 0)
	{
		if (links[indx][j] == pass->end)
		{
			ft_printf("HERE1111111\n");
			return ;
		}
		++j;
	}
	ft_printf("^^^\n");
	if ((j == 1 && indx != 0) || (indx == 0 && dist > 0))
	{
		ft_printf("HELLO JEFF\n");
		return ;
	}
	while (links[indx][i] >= 0)
	{
		//if (indx == 1)
		//	exit (0);
		if (links[indx][i] == indx)
			++i;
		else if (links[indx][i] == 0)
			++i;
		if (links[indx][i] < 0)
		{
			ft_printf("HELLLLLLLLOOOOO\n");
			return ;
		}
		while (links[indx][i] >= 0 && dist + 1 <= pass->distance[links[indx][i]])// && pass->distance[links[indx][i]] != 0) //double check
		{
			ft_printf("links[indx][i]: %d, dist %d, distance: %d\n", links[indx][i], dist, pass->distance[links[indx][i]]);
			++i;
		}
		ft_printf("ROOM: %s	distance: %d\n", pass->rooms[links[indx][i]], pass->distance[links[indx][i]]);
		if (links[indx][i] < 0)
		{
			ft_printf("$$$$$$$$$$\n");
			return ;
		}
		if (dist + 1 > pass->distance[links[indx][i]])// && indx != 0)// && pass->distance[links[indx][i]] != 0 && indx != 0)
		{
			pass->distance[links[indx][i]] = dist + 1;
		}
		// else if (dist + 1 > pass->distance[links[indx][i]] && pass->distance[links[indx][i]] == 0 && indx != 0)
		// {
		// 	pass->distance[links[indx][i]] = dist + 1;
		// 	ft_printf("ROOM: %s	distance: %d\n", pass->rooms[links[indx][i]], pass->distance[links[indx][i]]);
			
		// } 
		if (links[indx][i] != 0)// && pass->distance[links[indx][i]] + 1 <=  )
		{
			ft_printf("ANYTHING i : %d\n", i);
			//ft_printf("ROOM: %s	distance: %d\n", pass->rooms[9], pass->distance[9]);
		
			recurs(pass, pass->links, pass->distance[links[indx][i]], links[indx][i]);
		}
		ft_printf("after i : %i %s\n", i, pass->rooms[links[indx][i]]);
		++i;
		if (links[indx][i] == 8)
			++i;
		ft_printf("after i : %i %s, came from room %s\n", i, pass->rooms[links[indx][i]], pass->rooms[indx]);
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
