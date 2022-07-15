/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 09:38:32 by molesen           #+#    #+#             */
/*   Updated: 2022/07/15 13:30:59 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

// static void	copy_struct(t_path **path, t_room *pass, int i)
// {
// 	t_path *new;
// 	t_path *src;
// 	t_path *head;

// 	src = *path;
// 	src->move = src->move_head;
// 	while (src->move)
// 	{
// 		if (src->move->index == i || src->move->next == NULL)
// 			break ;
// 		src->move = src->move->next;
// 	}
// 	new = NULL;
// 	head = NULL;
// 	copy_path(&new, &src, pass, &head);
// 	new->move->next = NULL;
// 	(*path)->next = head;
// 	*path = (*path)->next;
// }

static void	find_path(t_path **path, t_room *pass, int i, int prev_index)
{
	int	len;
	int	j;

	if (pass->distance[i] <= pass->distance[prev_index] && pass->distance[i] != 0)
	{
		if (prev_index == pass->end)
			create_path(path, pass);
		create_index(&(*path)->move, *path, i);
		pass->used[i] = TRUE;
		len = len_array(pass->links[i]);
		j = 0;
		while (j < len)
		{
			if (pass->links[i][j] == 0)
			{
				ft_printf("FOUND START!\n");
				(*path)->found = TRUE;
				// if ((*path)->len > pass->longest_path)
				// 	pass->longest_path = (*path)->len;
				ft_printf("path: %d\n", (*path)->nbr);
				initialize_path_finder(path, pass);
				//del_last_path(*path, pass);
				//return ;
			}
			if (pass->distance[pass->links[i][j]] <= pass->distance[i] && pass->distance[pass->links[i][j]] != 0 && pass->links[i][j] != prev_index && pass->used[pass->links[i][j]] == FALSE)
			{
				find_path(&(*path), pass, pass->links[i][j], i);
				pass->used[pass->links[i][j]] = FALSE;
				del_first_index(*path);
			}
			j++;
		}
		pass->used[i] = FALSE;
	}
}

/*

compare two structs and their paths

i want the comparison to be a comparison between the amount of index elements in each path each struct contains

ex if you have

struct 1
ABC
FDK

struct2
ABC
FDBML

i want struct1 to return 6 and struct2 to return 8. because struct1 returned 1 we want to keep struct1

*/

static int	count_moves(t_path *path)
{
	int	i;

	i = 0;
	while (path)
	{
		i += path->len;
		path = path->next;
	}
	return (i);
}

static int	loop_to_end(t_path *file)
{
	while (file->next)
	{
		file = file->next;
	}
	return (file->nbr);
}

static void	compare_and_copy(t_path **path, t_room *pass)
{
	if (pass->final_head)
	{
		int	final_length;
		
		final_length = loop_to_end(pass->final_head);
		ft_printf("final: %d, path: %d\n", final_length, (*path)->nbr);
		if (final_length < (*path)->nbr)
		{
		ft_printf("pass->head: %p\n", pass->head);
	
			// free(pass->final_head);
			// pass->final_head = cpy_pth(pass->head);
			ft_printf("final: %d, path: %d\n", final_length, (*path)->nbr);
		}
		else if (final_length == (*path)->nbr)
		{
			if (count_moves(pass->final_head) > count_moves(*path))
			{
				// ft_printf("pass->head: %p\n", pass->head);
	
				// free(pass->final_head);
				pass->final_head = cpy_pth(pass->head);
			}
		}
	}
	else
	{
		// int	final_length;
		// t_path *final;
		// int i;
		
		pass->final_head = cpy_pth(pass->head);
	// 	final_length = loop_to_end(pass->final_head);
	// 	ft_printf("final: %d, path: %d\n", final_length, (*path)->nbr);
	// 	final = pass->head;
	// i = 0;
	// ft_printf("\n{green}finalS:{uncolor} \n");
	// while (final)
	// {
	// 	final->move = final->move_head;
	// 	ft_printf("final\nnbr: %d	Len: %d	nbr of struct: %d\n", final->nbr, final->len, i);
	// 	while (final->move)
	// 	{
	// 		ft_printf("room: %s\n", pass->rooms[final->move->index]);
	
	// 		final->move = final->move->next;
	// 	}
	// 	++i;
	// 	final = final->next;
	// }
	// 	exit(0);
	}
}

void	initialize_path_finder(t_path **path, t_room *pass)
{
	int	i;

	i = pass->i;
	pass->path_nbr = 1;
	pass->i++;
	while (i < pass->len)
	{
		ft_printf("i = %i\n", i);
		if (pass->links[pass->end][i] == 0)
		{
			create_path(path, pass);
			ft_printf("FOUND START!\n");
			// path->found = TRUE;
			// if (path->len > pass->longest_path)
			// 	pass->longest_path = path->len;
			break ;
		}
		if (pass->used[pass->links[pass->end][i]] == FALSE)
		{
			find_path(&(*path), pass, pass->links[pass->end][i], pass->end);
			del_last_path(path, pass);
		}
		++i;
	}
	// check with stored path
	ft_printf("finish struct!\n");
	compare_and_copy(path, pass);
}

static void	create_used(t_room *pass)
{
	int	i;

	i = 0;
	pass->used = (int *) malloc(pass->total * sizeof(int));
	if (!pass->used)
		exit(0);
	while (i < pass->total)
		pass->used[i++] = FALSE;
}

int	path_finder(t_room *pass)
{
	int i;
	t_path	*path;
	t_path	*final;

	path = NULL;
	final = NULL;
	pass->path_nbr = 1;
	pass->longest_path = 0;
	create_used(pass);
	pass->i = 0;
	pass->final_head = NULL;
	initialize_path_finder(&path, pass);
	if (!path)
	{
		ft_printf("ERROR\n");
		exit(0);
	}
	final = pass->final_head;
	i = 0;
	ft_printf("\n{green}finalS:{uncolor} \n");
	while (final)
	{
		final->move = final->move_head;
		ft_printf("final\nnbr: %d	Len: %d	nbr of struct: %d\n", final->nbr, final->len, i);
		while (final->move)
		{
			ft_printf("room: %s\n", pass->rooms[final->move->index]);
	
			final->move = final->move->next;
		}
		++i;
		final = final->next;
	}
	// t_path *help = NULL;
	// t_path *top;
	// help = cpy_pth(path);
	// top = help;
	// while (path && help)
	// {
	// 	ft_printf("nbr %i  len %i  found %i\n", path->nbr, path->len, path->found);
	// 	ft_printf("nbr %i  len %i  found %i\n\n", help->nbr, help->len, help->found);
	// 	path->move = path->move_head;
	// 	while (path->move && path->move)
	// 	{
	// 		ft_printf("index %i\n", path->move->index);
	// 		ft_printf("index %i\n", help->move->index);
	// 		path->move = path->move->next;
	// 		help->move = help->move->next;
	// 	}
	// 	ft_printf("\n");
	// 	path = path->next;
	// 	help = help->next;
	// }

	// help = top;
	// help->move = help->move_head;
	// ft_printf("nbr %i", help->move);
	// ft_printf("nbr2 %i\n", help->move->next);
	// del_first_index(help);
	// ft_printf("nbr %i", help->move);

	
	return (0);
}

/*

	TO DO:

	if amount of ants < len of paths
		pick path with fewest turns

	do we want to collect the shortest path also.

	try out with example we tried on paper




	check leaks and make sure everything is freed

	make the function for printing out the final ants movement.


*/
