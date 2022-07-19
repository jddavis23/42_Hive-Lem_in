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

/*	function that checks if a room is already in use	*/

static int	create_used(t_room *pass)
{
	int	i;

	i = 0;
	pass->used = (int *) malloc(pass->total * sizeof(int));
	if (!pass->used)
		return (error_path(pass, TRUE));
	while (i < pass->total)
		pass->used[i++] = FALSE;
	return (0);
}

/*	checks if end has been correctly sorted	*/

static int	is_sorted(t_room *pass)
{
	int	i;

	i = 0;
	while (i < (pass->len - 1))
	{
		if (pass->distance[pass->links[pass->end][i]] > pass->distance[pass->links[pass->end][i + 1]])
			return (FALSE);
		++i;
	}
	return (TRUE);
}

/*	sorts the links of the end. Shortest paths in the beginning	*/

static void	sort_end(t_room *pass)
{
	int	i;
	int	temp;

	i = 0;
	// might remove is sorted from while loop and instead put in bottom - depends what is faster - check with bigger values
	while (is_sorted(pass) == FALSE)
	{
		if (pass->distance[pass->links[pass->end][i]] > pass->distance[pass->links[pass->end][i + 1]])
		{
			temp = pass->links[pass->end][i];
			pass->links[pass->end][i] = pass->links[pass->end][i + 1];
			pass->links[pass->end][i + 1] = temp;
		}
		if (i < (pass->len - 1))
			++i;
		else
			i = 0;
	}
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
	if (create_used(pass) == ERROR)
		return (ERROR);
	sort_end(pass);
	pass->final_head = NULL;
	initialize_path_finder(&path, pass);
	if (!pass->final_head)
	{
		ft_printf("ERROR\n");
		// int i;
		// i = 0;
		// while ( i < pass->total)
		// {
		// 	while (links[i] != -1)
		// 	ft_printf("pass->links[%d]: %p\n", i, pass->links[i]);
		// 	++i;
		// }
		return (error_path(pass, TRUE));
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
	error_path(pass, FALSE);
	return (0);
}

/*

	TO DO:

	if amount of ants < len of paths
		pick path with fewest turns

	do we want to collect the shortest path also?

	try out with example we tried on paper





	check leaks and make sure everything is freed

	EXIT if we can't find a room that get referenced in the connections (now it segmentfault)



	make the function for printing out the final ants movement.

*/
