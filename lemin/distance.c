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
		while (links[indx][i] > 0 && dist >= pass->distance[links[indx][i]] && pass->distance[links[indx][i]] != 0) //double check
			++i;
		if (links[indx][i] <= 0)
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

/* copied from path_finder */

static int	current_true(t_room *pass)
{
	int i;

	i = 0;
	while (i < pass->total)
	{
		if (pass->info[CURRENT][i] != 0)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

static void	breadth_first_distance(t_room *pass, int indx, int i)
{
	int	j;
	int	k;

	j = 0;
	while (pass->links[indx][j] >= 0)
	{
		if (pass->links[indx][j] == pass->end)
		{
			pass->info[CURRENT][i] = 0;
			return ;
		}
		++j;
	}
	j = 0;
	while (pass->links[indx][j] >= 0)
	{
		if (pass->distance[pass->links[indx][j]] == 0 && pass->links[indx][j] != 0)
		{
			pass->distance[pass->links[indx][j]] = pass->distance[indx] + 1;
			pass->info[CURRENT][i] = pass->links[indx][j];
			k = 0;
			while (k < pass->total)
			{
				if (pass->info[CURRENT][k] == 0)
				{
					i = k;
					break ;
				}
				++k;
			}
		}
		++j;
	}
	if (pass->info[CURRENT][i] == indx)
		pass->info[CURRENT][i] = 0;
}

static void	initialize_path(t_room *pass, int i)
{
	pass->distance[pass->links[0][i]] = 1;
	pass->info[CURRENT][i] = pass->links[0][i];
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
	i = 0;
	pass->info[LEN][pass->end] = 1;
	while (pass->links[0][i] >= 0)
		initialize_path(pass, i++);
	while (!current_true(pass))
	{
		i = 0;
		while (i < pass->total)
		{
			if (pass->info[CURRENT][i] != 0)
			{
				breadth_first_distance(pass, pass->info[CURRENT][i], i);
			}
			++i;
		}
	}
	i = 0;
	while (i < pass->total)
	{
		pass->info[CURRENT][i++] = FALSE;
	}
	//recurs(pass, pass->links, pass->distance[0], 0);
	//recurse_check(pass, pass->links, pass->distance[0], 0, 0);
	pass->distance[pass->end] = pass->total;
	// i = 0;
	// ft_printf("\n");
	// while (i < pass->total)
	// {
	// 	ft_printf("room %s  distance %i\n", pass->rooms[i], pass->distance[i]);
	// 	++i;
	// }
	// ft_printf("\n");
	// exit(0);
}


/*

struct paths
{
	int				nbr;
	int				len;
	int				found;
	int				max_ants;
	t_index			*move_head;
	struct s_index	*move;
	struct s_path	*next;
	struct s_path	*prev;
}

struct index
{
	int		index;
	int		j;
	int		prev_split;//true or fall
	struct	*next;
	struct	*prev;
}

make distance just to eliminate how many structs we start with + dead ends

make a struct path for each path.
move each path until they reach a path that connects with multiple paths
- if path is occupied by another path - try the other free path
- if everything has been tried - check if the pieces occupying the non free path can pick another route
	if it can try to go down that
	else pick the shortest path to continue down.
  else
	delete the path (set its indexes in used to FALSE)
- delete a path if i merges with another path with no possibility of deterioating
it from the other (keep the path with the shortest length)
- 


- delete whole path - set the  indexes it had in used == FALSE and make sure other paths are still linked
- function that finds path which contains the index that blocks another path
	if it has another option it can move to
		move to that
	else
		keep the shortes path and delete the other
- create index function - adds index to existing index but can also create it if it hasn't already
- delete index function - deletes from the front


create all the paths and give them the first index
while all paths found != TRUE
{
	while path->next (loop through all the paths)
	{
		move all paths index until they are moved to a path with multiple options
	}
	while path->next (loop through all the paths AGAIN)
		decide which path each path should go down based on above logic
}




DISTANCE FUNCTION
- would have to update it so if it finds a branch that doesn't end with the end
	backtrack and delete it or set it to a value of -1
	if it is set to -1 make sure to sort the linked list so the -1 will be at the end
	

*/