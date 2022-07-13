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

static void	make_temp(t_room *pass)
{
	// maps/subject3-1.map
	/*distance[0] = 0;
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
	distance[13] = 0;*/

	// maps/subject-short.map
	// pass->distance[0] = 0;
	// pass->distance[1] = 1;
	// pass->distance[2] = 2;
	// pass->distance[3] = pass->total;

	//maps/subject2-1.map
	pass->distance[0] = 0;
	pass->distance[1] = 1;
	pass->distance[2] = 1;
	pass->distance[3] = 2;
	pass->distance[4] = pass->total;
}

/*is it an error if there in the instructions shows a path connected to the same room twice?*/
/*
create a function that handles creating a new node with a variable and putting it to the linked list of indexes
make identical function for the path linked list.
*/

static t_index	*ft_indexnew(int index, int prev)
{
	t_index	*new_list;

	new_list = (t_index *)malloc(sizeof(t_index));
	if (!new_list)
		return (NULL);
	new_list->index = index;
	new_list->prev_index = prev;
	new_list->next = NULL;
	return (new_list);
}

static void	ft_indexadd_front(t_index **index, t_index *new)
{
	if (!index || !new)
		return ;
	new->next = *index;
	*index = new;
}

static void	create_index(t_index **move, t_path *path, int i, int prev_index)
{
	t_index	*new;

	new = NULL;
	if (!(*move))
	{
		*move = ft_indexnew(i, prev_index);
		path->index_head = *move;
		path->move = *move;
	}
	else
	{
		new = ft_indexnew(i, prev_index);
		ft_indexadd_front(&path->index_head, new);
	}
	path->len++;
}

static t_path	*ft_pathnew()
{
	t_path	*new;

	new = (t_path *)malloc(sizeof(t_path));
	if (!new)
		return (NULL);
	new->len = 0;
	new->move = NULL;
	new->next = NULL;
	return (new);
}

static void	ft_path_add(t_path **path, t_path *new)
{
	if (!path || !new)
		return ;
	(*path)->next = new;
	*path = (*path)->next;
}

static void	create_path(t_path **path, t_room *pass)
{
	t_path *new;

	new = *path;
	new = ft_pathnew();
	new->nbr = pass->path_nbr;
	new->found = FALSE;
	pass->path_nbr++;
	if (*path)
		ft_path_add(path, new);
	else
		*path = new;
	create_index(&(*path)->move, *path, pass->end, 0);
}

static void	copy_struct(t_path **path, t_room *pass, int i)
{
	int	first;
	t_path *new;
	t_path *src;
	t_path *head;

	first = TRUE;
	new = ft_pathnew();
	src = *path;
	src->move = src->index_head;
	head = new;
	while (src->move)
	{
		new->len++;
		if (first == TRUE)
		{
			new->move = ft_indexnew(src->move->index, src->move->prev_index);
			new->index_head = new->move;
			new->nbr = pass->path_nbr;
			pass->path_nbr++;
			first = FALSE;
		}
		else
		{
			new->move->next = ft_indexnew(src->move->index, src->move->prev_index);
			new->move = new->move->next;
		}
		if (new->move->index == i || src->move->next == NULL)
		{
			new->move->next = NULL;
			break ;
		}
		src->move = src->move->next;
	}
	ft_path_add(path, head);
}

static int	is_start(t_path *path, t_room *pass, int i, int len)
{
	int	j;

	j = 0;
	while (j < len)
	{
		if (pass->links[i][j] == 0)
		{
			ft_printf("FOUND START!\n");
			path->found = TRUE;
			return (TRUE);
		}
		++j;
	}
	return (FALSE);
}

static void	find_path(t_path *path, t_room *pass, int i, int prev_index)
{
	int	j;
	int	len;
	t_index *prev_path;

	j = 0;
	prev_path = path->move;
	//ft_printf("distance[i]: %d	prev: %d, prev_index: %d\n", pass->distance[i], pass->distance[prev_index], prev_index);
	if (pass->distance[i] <= pass->distance[prev_index])
	{
		create_index(&path->move, path, i, prev_index);
		len = len_array(pass->links[i]);
		if (is_start(path, pass, i, len) == TRUE)
			return ;
		while (j < len)
		{
			//ft_printf("distance[passlinks i j]: %d	prev: %d, prev_index: %d\n", pass->distance[pass->links[i][j]], pass->distance[prev_index], prev_index);
			if (pass->distance[pass->links[i][j]] <= pass->distance[prev_index] && pass->distance[pass->links[i][j]] != 0)
			{
				
				if (path->found == TRUE)
				{
					copy_struct(&path, pass, pass->links[i][j]);
					find_path(path, pass, pass->links[i][j], pass->distance[pass->links[i][j]]);
					path->found = FALSE;
				}
				else
				{
					find_path(path, pass, pass->links[i][j], pass->distance[pass->links[i][j]]);
				}
			}
			++j;
		}
	}
}

int	path_finder(t_room *pass)
{
	int	max;
	int	len;
	int	i;
	int	index;
	t_path *head;
	t_path	*path;

	len = len_array(pass->links[pass->end]);
	max = calc_max(len_array(pass->links[0]), len);
	if (max < 1)
		return (ERROR);
	make_temp(pass);
	path = NULL;
	pass->path_nbr = 1;
	i = 0;
	create_path(&path, pass);
	head = path;
	while (i < len)
	{
		index = pass->links[pass->end][i];
		if (index == 0)
		{
			//use path that leads directly to start. can move everything at the same time
			break ;
		}
		else if (i > 0)
			create_path(&path, pass);
		find_path(path, pass, index, pass->end);
		// if no path error exit
		++i;
	}
	path = head;
	i = 0;
	while (path)
	{
		path->move = path->index_head;
		ft_printf("path\nnbr: %d	Len: %d	nbr of struct: %d\n", path->nbr, path->len, i);
		while (path->move)
		{
			ft_printf("index: %d\n", path->move->index);
	
			path->move = path->move->next;
		}
		++i;
		path = path->next;
	}
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


/*
create a function that handles creating a new node with a variable and putting it to the linked list of indexes
make identical function for the path linked list.
*/