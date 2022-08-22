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

static int	is_sorted(t_room *pass, int indx)
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

static void set_to_minus_one(t_room *pass, int indx)
{
	//int	next;
	int	i;

	i = 0;
	while (pass->links[indx][i] != -1)
	{
		++i;
	}
	if (i == 2)
	{
		pass->distance[indx] = -1;
		i = 0;
		while (pass->links[indx][i] != -1)
		{
			if (pass->distance[pass->links[indx][i]] != -1)
			{
				set_to_minus_one(pass, pass->links[indx][i]);
			}
			++i;
		}
	}

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
		if (pass->links[indx][i] == -1 || (pass->links[indx][i + 1] == -1 && indx != pass->end && indx != 0))
		{
			if (pass->links[indx][i] != -1)
			{
				pass->distance[indx] = -1;
				set_to_minus_one(pass, pass->links[indx][i]);
			}
		}
		else
		{
			while (is_sorted(pass, indx) == FALSE)
			{
				i = 0;
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
		}
		++indx;
	}
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

static void	create_len(int *array, int **len)
{
	int	i;

	i = 0;
	while (array[i] != -1)
	{
		i++;
	}
	*len = (int *)malloc(sizeof(int) * (i + 1));
	i = 0;
	while (array[i] != -1)
	{
		(*len)[i] = 0;
		++i;
	}
	(*len)[i] = -1;
}

static void reset_len(int **len)
{
	int i;

	i = 0;
	while ((*len)[i] != -1)
	{
		(*len)[i] = 0;
		++i;
	}
}

static void	start_connect(t_room *pass, int *connect)
{
	while (pass->links[0][*connect] != -1)
	{
		(*connect)++;
	}
}

int	initialize_path_finder(t_room *pass, char *input)
{
	t_path	*path;
	t_path	*final;
	int	*len;
	int	i;
	int connect;

	path = NULL;
	final = NULL;
	len = NULL;
	sort_distance(pass);
	create_len(pass->links[0], &len);
	pass->final_head = NULL;
	i = 0;
	connect = 0;
	start_connect(pass, &connect);
	while (i < connect)
	{
		ft_printf("NUMBER OF TRIES %d\n", i);
		path_finder(&path, pass, i, &len);
		// if (pass->final_head && i != connect - 1)
		// {
		// 	del_path(&pass->final_head);
		// 	pass->final_head = NULL;
		// 	path = NULL;
		// }
		int k = 0;
		while (k < pass->total)
		{
			pass->info[PATH][k] = FALSE;
			pass->info[PREV][k] = FALSE;
			pass->info[LEN][k++] = FALSE;
		}
		reset_len(&len);
		++i;
	}
	if (!pass->final_head)
		return (error_path(pass, input, TRUE));
	final = pass->final_head;
	return (0);
}

/*

Fix one path deletes two paths problem
- idea 1: go through original copy and eliminate paths
- idea 2: reset where we start each time

smallest path... based on amount of ants

*/

/*

- when breath first finds beginning but want to find next shortest path - make sure it acts as we want it to

- decide between paths logic ex update struct or not

*/