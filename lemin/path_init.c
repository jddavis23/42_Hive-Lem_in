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

/*	checks if end has been correctly sorted	*/

// static int	is_sorted(t_room *pass, int indx)
// {
// 	int	i;

// 	i = 0;
// 	if (pass->links[indx][i] == -1 || pass->links[indx][i + 1] == -1)
// 		return (TRUE);
// 	while (pass->links[indx][i + 1] != -1)
// 	{
// 		if (pass->distance[pass->links[indx][i]] > pass->distance[pass->links[indx][i + 1]])
// 			return (FALSE);
// 		++i;
// 	}
// 	return (TRUE);
// }

static int	is_sorted_end(t_room *pass, int indx)
{
	int	i;

	i = 0;
	if (pass->links[indx][i] == -1 || pass->links[indx][i + 1] == -1)
		return (TRUE);
	while (pass->links[indx][i + 1] != -1)
	{
		if (pass->distance[pass->links[indx][i]] < pass->distance[pass->links[indx][i + 1]] && pass->distance[pass->links[indx][i]] == 0)
			return (FALSE);
		if (pass->distance[pass->links[indx][i]] > pass->distance[pass->links[indx][i + 1]] && pass->distance[pass->links[indx][i + 1]] != 0)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

/*	sorts the links of the end. Shortest paths in the beginning	*/

static void	sort_distance(t_room *pass)
{
	int	i;
	int	temp;
	int	indx;

	i = 0;
	indx = 1;
	// might remove is sorted from while loop and instead put in bottom - depends what is faster - check with bigger values
	i = 0;
	while (indx < pass->total)
	{
		i = 0;
		// if (indx == pass->end)
		// {
			while (is_sorted_end(pass, indx) == FALSE)
			{
				i = 0;
				if (pass->links[indx][i] == -1 || pass->links[indx][i + 1] == -1)
					break ;
				while (pass->links[indx][i + 1] != -1)
				{
					if (pass->distance[pass->links[indx][i]] > pass->distance[pass->links[indx][i + 1]] && pass->distance[pass->links[indx][i + 1]] != 0)
					{
						temp = pass->links[indx][i];
						pass->links[indx][i] = pass->links[indx][i + 1];
						pass->links[indx][i + 1] = temp;
					}
					else if (pass->distance[pass->links[indx][i]] < pass->distance[pass->links[indx][i + 1]] && pass->distance[pass->links[indx][i]] == 0)
					{
						temp = pass->links[indx][i];
						pass->links[indx][i] = pass->links[indx][i + 1];
						pass->links[indx][i + 1] = temp;
					}
					++i;
				}
			}
		// }
		// else
		// {
		// 	while (is_sorted(pass, indx) == FALSE)
		// 	{
		// 		i = 0;
		// 		if (pass->links[indx][i] == -1 || pass->links[indx][i + 1] == -1)
		// 			break ;
		// 		while (pass->links[indx][i + 1] != -1)
		// 		{
		// 			if (pass->distance[pass->links[indx][i]] > pass->distance[pass->links[indx][i + 1]])
		// 			{
		// 				temp = pass->links[indx][i];
		// 				pass->links[indx][i] = pass->links[indx][i + 1];
		// 			pass->links[indx][i + 1] = temp;
		// 			}
		// 			++i;
		// 		}
		// 	}
		// }
		++indx;
	}
}

static int	check_if_sorted(t_path *path)
{
	while (path && path->next)
	{
		if (path->len > path->next->len)
			return (FALSE);
		path = path->next;
	}
	return (TRUE);
}

static void	quick_sort(t_path **path)
{
	t_path *head;

	head = *path;
	while (check_if_sorted(*path) == FALSE)
	{

		*path = (*path)->next;
		//quick sort or any other sorting algo
	}
	*path = head;
}

// static void	printf_struct(t_room *pass)
// {
// 	t_path *final;
// 	t_index *temp;
// 	int i;
// 	final = pass->final_head;
// 	i = 0;
// 	ft_printf("\n{green}after sort: finalS:{uncolor} \n");
// 	while (final)
// 	{
// 		temp = final->move_head;
// 		final->move = final->move_head;
// 		ft_printf("final\nnbr: %d	Len: %d	nbr of struct: %d\n", final->nbr, final->len, i);
// 		while (final->move)
// 		{
// 			ft_printf("room: %s\n", pass->rooms[final->move->index]);
// 			final->move = final->move->next;
// 		}
// 		final->move_head = temp;
// 		++i;
// 		final = final->next;
// 	}
// }

int	initialize_path_finder(t_room *pass, char *input)
{
	int i;
	t_path	*path;
	t_path	*final;

	path = NULL;
	final = NULL;
	pass->path_nbr = 1;
	sort_distance(pass);
	// i = 0;
	// int p = 0;
	// int j = 0;
	// int m;
	// while (pass->rooms[p])
	// 			{
	// 				m = 0;
	// 				if (p == 0)
	// 				{
	// 					ft_printf("room %s-----\n\n", pass->rooms[p]);
	// 					while (pass->links[p][m] >= 0)
	// 					{
	// 						ft_printf("\nroom %s\n", pass->rooms[pass->links[p][m]]);
						
	// 						//ft_printf("\n%d { ", pass->links[m][]);
	// 						int q = 0;
	// 						while (pass->links[pass->links[p][m]][q] != -1)
	// 						{
						
	// 							ft_printf("\n%s ", pass->rooms[pass->links[pass->links[p][m]][q]]);
	// 							j = 0;
	// 							while (pass->links[pass->links[pass->links[p][m]][q]][j]  >= 0)
	// 							{
	// 								ft_printf("distance %i ", pass->distance[pass->links[pass->links[pass->links[p][m]][q]][j++]]);
	// 							}
	// 							q++;
	// 						}
	// 						m++;
	// 						ft_printf("}");
	// 					}
	// 					ft_printf("\n\n");
	// 				}
	// 				++p;
	// 			}
	// exit(0);
	// i = 0;
	// int p = 0;
	// int m;
	// while (pass->rooms[p])
	// {
	// 	m = 0;
	// 	if (p == pass->end)
	// 	{
	// 		ft_printf("room %s-----\n\n", pass->rooms[p]);
	// 		while (pass->links[p][m] >= 0)
	// 		{
	// 			ft_printf("\nroom %d\n", pass->distance[pass->links[p][m]]);
	// 			m++;
	// 		}
	// 		ft_printf("\n\n");
	// 	}
	// 	++p;
	// }
	i = 0;
	while (i < pass->total)
	{
		pass->info[PREV][i] = FALSE;
		++i;
	}
	i = 0;
	while (pass->rooms[i])
	{
		//int k = 0;
		ft_printf("ROOM{%s}-[%d]: \n", pass->rooms[i], pass->distance[i]);
		// while (pass->links[i][k] >= 0)
		// {
		// 	ft_printf("room[%s]-[%d]	", pass->rooms[pass->links[i][k]], pass->distance[pass->links[i][k]]);
		// 	++k;
		// }
		ft_printf("\n\n");
		++i;
	}
	pass->final_head = NULL;
	path_finder(&path, pass, 0);
	if (!pass->final_head)
		return (error_path(pass, input, TRUE));
	final = pass->final_head;
	i = 0;
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
	// try to test if this is ever happening??
	//exit(0);
	// ft_printf("found struct\n");
	// printf_struct(pass);
	// exit(0);
	// printf_struct(pass);
	quick_sort(&pass->final_head);
	//exit(0);
	// final = pass->final_head;
	// i = 0;
	// ft_printf("\n{green}after sort: finalS:{uncolor} \n");
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
	// exit (0);
	// if (pass->links)
	// 	pass->links = free2d_int(pass->links, pass->total, pass->end);
	// if (pass->distance)
	// 	free(pass->distance);
	// if (pass->used)
	// 	free(pass->used);
	// pass->links = NULL;
	// pass->distance = NULL;
	// pass->used = NULL;
	return (0);
}

/*

smallest path... based on amount of ants

*/
