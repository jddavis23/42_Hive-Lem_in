/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 09:38:32 by molesen           #+#    #+#             */
/*   Updated: 2022/07/12 09:38:35 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

static int	calc_max(int nbr1, int nbr2)
{
	if (nbr1 < nbr2)
		return (nbr1);
	return (nbr2);
}

static int	len_array(int *links)
{
	int	i;

	i = 0;
	while (links[i] != -1)
		++i;
	return (i);
}

static void	*make_temp(int distance[500])
{
	distance[0] = 0;
	distance[1] = 1;
	distance[2] = 1;
	distance[3] = 2;
	distance[4] = 2;
	distance[5] = 2;
	distance[6] = 2;
	distance[7] = 1;
	distance[8] = 2;
	distance[9] = 3;
	distance[10] = 0;
	distance[11] = 0;
	distance[12] = 0;
	distance[13] = 0;
	return (distance);
}

/*is it an error if there in the instructions shows a path connected to the same room twice?*/

int	path_finder(t_room *pass)
{
	int distance[500];
	int	max;
	//t_path	*;

	pass->end = pass->total - 1;
	max = calc_max(len_array(pass->links[0]), len_array(pass->links[pass->end]));
	make_temp(distance);

	//find_paths()
	// if shortest path is connected to end - move every ant at once
	// 
	//pass->links[0]
	//return error if no connections are found. ex if every path the first room is connected to has the value 0 and it is not the end we know it hasn't been updated
	// loop through the list of the nbrs and creates paths based on that. keep doing that until no more can be created
	// store everything in a linked list
	/* typedef struct s_paths
	{
		char *str; (easiest to have integers for comparing the paths with eachother)
		int len;
		struct s_paths *next;
	}	t_paths
	keep track of how many paths found starting from each location.

	*/
	return (0);
}
