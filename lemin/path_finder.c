/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_initialize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:31:10 by molesen           #+#    #+#             */
/*   Updated: 2022/07/19 10:31:12 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

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

static void	printf_struct(t_room *pass)
{
	t_path *final;
	t_index *temp;
	int i;
	final = pass->head;
	i = 0;
	ft_printf("\n{green}after sort: finalS:{uncolor} \n");
	while (final)
	{
		temp = final->move_head;
		final->move = final->move_head;
		ft_printf("final\nnbr: %d	Len: %d	nbr of struct: %d\n", final->nbr, final->len, i);
		while (final->move)
		{
			ft_printf("room: %s\n", pass->rooms[final->move->index]);
			final->move = final->move->next;
		}
		final->move_head = temp;
		++i;
		final = final->next;
	}
}

static void	compare_and_copy(t_path **path, t_room *pass)
{
	int	final_length;

	ft_printf("found struct\n");
	printf_struct(pass);
	if (pass->final_head)
	{
		final_length = loop_to_end(pass->final_head);
		if (final_length < (*path)->nbr)
		{
			del_path(&pass->final_head);
			pass->final_head = cpy_pth(pass->head);
			//ft_printf("finish struct!\n");
		}
		else if (final_length == (*path)->nbr)
		{
			if (count_moves(pass->final_head) > count_moves(pass->head))
			{
				del_path(&pass->final_head);
				pass->final_head = cpy_pth(pass->head);
			}
			
		}
	}
	else
	{
		pass->final_head = cpy_pth(pass->head);
	}
}

static void	find_path(t_path **path, t_room *pass, int i, int prev_index, int k)
{
	//int	len;
	int	j;

	if (pass->distance[i] <= pass->distance[prev_index] && pass->distance[i] != 0)
	{
		create_index(&(*path)->move_head, *path, i);
		// ft_printf("found new rooom\n");
		// printf_struct(pass);
		pass->used[i] = TRUE;
		//len = len_array(pass->links[i]);
		j = 0;
		while (pass->links[i][j] != -1)
		{
			if (pass->links[i][j] == 0)
			{
				//ft_printf("head: %p, move_head: %p, index: %d\n", pass->head, pass->head->move_head, pass->head->move_head->index);
				//ft_printf("FOUND START!\n");
				pass->head->found = TRUE;
				path_finder(path, pass, k);
				return ;
			}
			if (pass->distance[pass->links[i][j]] <= pass->distance[i] && pass->distance[pass->links[i][j]] != 0 && pass->links[i][j] != prev_index && pass->used[pass->links[i][j]] == FALSE)
			{
				// ft_printf("found new rooom\n");
				// printf_struct(pass);
				find_path(&(*path), pass, pass->links[i][j], i, k);
				pass->used[pass->links[i][j]] = FALSE;
				del_first_index(*path);
				//ft_printf("recurse back\n");
			}
			j++;
		}
		pass->used[i] = FALSE;
	}
}

void	path_finder(t_path **path, t_room *pass, int i)
{
	// static int	i = 0;
	static int	count = 0;
	int start;

	//ft_printf("link: %d\n", pass->distance[pass->links[pass->end][i]]);
	//exit(0);
	start = i;
	i = 0;
	if (pass->links[pass->end][i] == 0)
	{
		create_path(path, pass);
		pass->head->found = TRUE;
	}
	else
	{
		//while (pass->links[pass->end][i] > 0)
		//while (1)
		while (pass->links[pass->end][i] > 0)
		{
			// temp solution to the constant looping problem
			// if (count > 100 || pass->final_head)
			// {
			// 	return ;
			// }
			if (pass->used[pass->links[pass->end][i]] == FALSE)// && pass->distance[pass->links[pass->end][i]] != 0)// pass->distance[pass->end])// && pass->distance[i] != 0)
			{
				//if (len != -1 && pass->distance[i])
				//{
					// ft_printf("found new rooom\n");
					// printf_struct(pass);
					create_path(path, pass);
					find_path(&(*path), pass, pass->links[pass->end][i], pass->end, i);
					//ft_printf("recurse back\n");
					del_last_path(path, pass);
				//}
			}
			++i;
			// if (pass->links[pass->end][i] == -1)
			// {
			// 	i = 0;
			// }
			// if (i == start)
			// 	break ;
		}
	}
	if (pass->head && pass->head->found == TRUE)
	{
		compare_and_copy(path, pass);
		pass->head->found = FALSE;
		count++;
	}
	//ft_printf("recurse back\n");
}


/*

creater than amount of ants - compare and copy emmidiately
- if it is less moves() than the final_path we already have


BEFORE CHANGES
time ./lem-in -r < big2.txt
- 107 rows (max limit is 72)
- ./lem-in -r < big2.txt  2.30s user 0.03s system 90% cpu 2.584 total

time ./lem-in -r < big1.txt
- 69 rows (max limit is 54)
- ./lem-in -r < big1.txt  2.45s user 0.01s system 98% cpu 2.494 total


try to add:
- sort distance by lowest each time
- if connected to start dont try any other connections


*/