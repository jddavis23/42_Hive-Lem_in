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
	pass->distance[0] = 0;
	pass->distance[1] = 1;
	pass->distance[2] = 2;
	pass->distance[3] = 0;
}

static t_index	*ft_indexnew(int index)
{
	t_index	*new_list;

	new_list = (t_index *)malloc(sizeof(t_index));
	if (!new_list)
		return (NULL);
	new_list->index = index;
	new_list->next = NULL;
	return (new_list);
}

static t_path	*ft_pathnew()
{
	t_path	*new;

	new = (t_path *)malloc(sizeof(t_path));
	if (!new)
		return (NULL);
	new->len = 0;
	new->index = NULL;
	new->next = NULL;
	return (new);
}

static void	ft_indexadd(t_index **index, t_index *new)
{
	if (!index || !new)
		return ;
	new->next = *index;
	*index = new;
}

static void	ft_path_index_add(t_path **path, t_path *new)
{
	if (!path || !new)
		return ;
	new->next = *path;
	*path = new;
}

static void	copy_struct(t_room *pass, int i)
{
	int	j;
	t_path *new;
	t_path *temp;
	t_path *head;

	j = pass->end;
	new = ft_pathnew();
	temp = pass->head;
	head = new;
	while (temp->index->next)
	{
		new->len++;
		new->index = ft_indexnew(temp->index->index);
		if (new->index->index == i)
			break ;
		temp->index = temp->index->next;
		new->index = new->index->next;
	}
	ft_path_index_add(&pass->head, head);
}

static void	find_path(t_path *path, t_room *pass, int i, int prev)
{
	int	j;
	int	len;
	int	first;
	t_index *prev_path;

	j = 0;
	prev_path = path->index;
	first = TRUE;
	// if (i == 0)
	// {
	// 	path->index = path->index->next;
	// 	path->index = ft_indexnew(0);
	// 	ft_indexadd(&prev_path, path->index);
	// 	//path->index = path->index->next;
	// 	//path->next = NULL;
	// 	path->len++;
	// 	//
	// 	//put end.
	// }
	// else 
	ft_printf("distance[i]: %d	prev: %d\n", pass->distance[i], prev);
		
	if (pass->distance[i] <= prev && i != 0)
	{
		if (path->index == NULL)
		{
			path->index = ft_indexnew(i);
		}
		else
		{
			path->index = path->index->next;
			path->index = ft_indexnew(i);
			ft_indexadd(&prev_path, path->index);
		}
		path->len++;
		len = len_array(pass->links[i]);
		while (j < len)
		{
			ft_printf("distance[passlinks i j]: %d	prev: %d\n", pass->distance[pass->links[i][j]], prev);
			if (pass->distance[pass->links[i][j]] <= prev && i != 0)
			{
				if (first == FALSE)
				{
					// ft_printf("HEllo\n");
					// //path = path->next;
					// ft_printf("len: %d\n", path->len);
					// t_path *hello;
					
					// hello = pass->head;
					// while (pass->head)
					// {
					// 	while (pass->head->index)
					// 	{
					// 		ft_printf("index: %d\n", pass->head->index->index);
					
					// 		pass->head->index = pass->head->index->next;
					// 	}
					// 	pass->head = pass->head->next;
					// }
					copy_struct(pass, i);
					// ft_printf("len: %d\n", pass->head->len);
					
					// pass->head = hello;
					// while (pass->head)
					// {
					// 	while (pass->head->index)
					// 	{
					// 		ft_printf("index: %d\n", pass->head->index->index);
					
					// 		pass->head->index = pass->head->index->next;
					// 	}
					// 	pass->head = pass->head->next;
					// }
					// ft_printf("len: %d\n", pass->head->len);
					// pass->head = hello;
					// NEED TO MAKE FUNCTION TO COPY STRUCT
					//copy struct and all its values until certain point
					// until 'i' has been found.
				}
				else
					first = FALSE;
				find_path(path, pass, pass->links[i][j], pass->distance[pass->links[i][j]]);
			}
			++j;
		}
		
		// collect new number to string 
		// update length
		// set next == null.
		//(void)path;
	}
}

/*is it an error if there in the instructions shows a path connected to the same room twice?*/

int	path_finder(t_room *pass)
{
	int	max;
	int	len;
	int	i;
	int	index;
	t_path	*path;

	len = len_array(pass->links[pass->end]);
	max = calc_max(len_array(pass->links[0]), len);
	if (max < 1)
		return (ERROR);
	make_temp(pass);
	path = ft_pathnew();
	i = 0;
	t_path *head;
	head = path;
	pass->head = path;
	while (i < len)
	{
		index = pass->links[pass->end][i];
		if (index == 0)
		{
			//use path that leads directly to start. can move everything at the same time
			break ;
		}
		else if (i > 0)
		{
			path->next = ft_pathnew();
			path = path->next;
			pass->head = path;
		}
		find_path(path, pass, index, pass->distance[index]);
		//move the path
		//path->nextf
		ft_printf("len: %d\n", path->len);
		++i;
	}
	i = 0;
	t_index *temp;
	path = head;
	while (path)
	{
		temp = path->index;
		while (path->index)
		{
			ft_printf("index: %d\n", path->index->index);
	
			path->index = path->index->next;
		}
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
