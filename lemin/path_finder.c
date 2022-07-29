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

	// ft_printf("\nfound struct\n\n");
	// printf_struct(pass);
	if (pass->final_head)
	{
		final_length = loop_to_end(pass->final_head);
		// if (final_length == 3)
		// 	exit(0);
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

// static void	find_path(t_path **path, t_room *pass, int i, int prev_index, int k)
// {
// 	//int	len;
// 	int	j;
// 	//static int count = 0;

// 	//if (pass->distance[i] != 0)//pass->distance[i] <= pass->distance[prev_index] && pass->distance[i] != 0)
// 	if (pass->distance[i] <= pass->distance[prev_index] && pass->distance[i] != 0)
// 	{
// 		create_index(&(*path)->move_head, *path, i);
// 		// ft_printf("found new rooom\n");
// 		// printf_struct(pass);
// 		pass->used[i] = TRUE;
// 		//len = len_array(pass->links[i]);
// 		j = 0;
// 		while (pass->links[i][j] != -1)
// 		{
// 			if (ft_strcmp(pass->rooms[i], "Dhw8") == 0)
// 			{
// 				ft_printf("room: %s	distance: %d <= %d	%d != 0, %d != previndex[%d], used %d == 0(FALSE)\n", pass->rooms[pass->links[i][j]], pass->distance[pass->links[i][j]], pass->distance[i], pass->distance[pass->links[i][j]], pass->links[i][j], prev_index, pass->used[pass->links[i][j]]);
// 			}
// 			if (pass->links[i][j] == 0)
// 			{
// 				//ft_printf("head: %p, move_head: %p, index: %d\n", pass->head, pass->head->move_head, pass->head->move_head->index);
// 				//ft_printf("FOUND START!\n");
// 				pass->head->found = TRUE;
// 				path_finder(path, pass, k);
// 				pass->used[i] = FALSE;
// 				return ;
// 			}
// 			//if (pass->distance[pass->links[i][j]] != 0 && pass->links[i][j] != prev_index && pass->used[pass->links[i][j]] == FALSE)//pass->distance[pass->links[i][j]] <= pass->distance[i] && pass->distance[pass->links[i][j]] != 0 && pass->links[i][j] != prev_index && pass->used[pass->links[i][j]] == FALSE)
// 			if (pass->distance[pass->links[i][j]] <= pass->distance[i] && pass->distance[pass->links[i][j]] != 0 && pass->links[i][j] != prev_index && pass->used[pass->links[i][j]] == FALSE)
// 			{
// 				// ft_printf("found new rooom\n");
// 				// printf_struct(pass);
// 				find_path(&(*path), pass, pass->links[i][j], i, k);
// 				pass->used[pass->links[i][j]] = FALSE;
// 				del_first_index(*path);
// 				//ft_printf("recurse back\n");
// 			}
// 			j++;
// 		}
// 		pass->used[i] = FALSE;
// 		if (ft_strcmp(pass->rooms[i], "Dhw8") == 0)
// 		{
// 			exit(0);
// 		}
// 	}
// }

// void	path_finder(t_path **path, t_room *pass, int i)
// {
// 	// static int	i = 0;
// 	static int	count = 0;
// 	int start;

// 	//ft_printf("link: %d\n", pass->distance[pass->links[pass->end][i]]);
// 	//exit(0);
// 	// if (pass->final_head && loop_to_end(pass->final_head) >= 6)
// 	// 	return ;
// 	if (i != 0)
// 	{
// 		start = pass->head->found;
// 		pass->head->found = FALSE;
// 	}
// 	i = 0;
// 	if (pass->links[pass->end][i] == 0)
// 	{
// 		create_path(path, pass);
// 		pass->head->found = TRUE;
// 	}
// 	else
// 	{
// 		//while (pass->links[pass->end][i] > 0)
// 		//while (1)
// 		while (pass->links[pass->end][i] > 0)
// 		{
// 			// temp solution to the constant looping problem
// 			// if (count > 100 || pass->final_head)
// 			// {
// 			// 	return ;
// 			// }
// 			if (pass->used[pass->links[pass->end][i]] == FALSE)// && pass->distance[pass->links[pass->end][i]] != 0)// pass->distance[pass->end])// && pass->distance[i] != 0)
// 			{
// 				//if (len != -1 && pass->distance[i])
// 				//{
// 					// ft_printf("found new rooom\n");
// 					// printf_struct(pass);
// 					create_path(path, pass);
// 					//++i;
// 					find_path(&(*path), pass, pass->links[pass->end][i], pass->end, i);
// 					//ft_printf("recurse back\n");
// 					if (pass->head->found == FALSE)
// 					{
// 						del_last_path(path, pass);
// 						break ;
// 					}
// 					else
// 						del_last_path(path, pass);
// 					pass->used[pass->links[pass->end][i]] = FALSE;
// 				//}
// 			}
// 			// else
// 				++i;
// 			// if (pass->links[pass->end][i] == -1)
// 			// {
// 			// 	i = 0;
// 			// }
// 			// if (i == start)
// 			// 	break ;
// 		}
// 	}
// 	if (pass->head && start == TRUE)
// 	{
// 		//ft_printf("struct\n");
// 		compare_and_copy(path, pass);
// 		pass->head->found = FALSE;
// 		count++;
// 	}
// 	//ft_printf("recurse back\n");
// }
//////////

static int	all_paths_found(t_path *path)
{
	while (path)
	{
		if (path->found == FALSE)
			return (FALSE);
		path = path->next;
	}
	return (TRUE);
}

static void	index_until_conflict(t_path **path, t_room *pass, int prev, int indx)
{
	int	count;
	int n;

	count = 0;
	n = 0;
	while (pass->links[indx][n] > -1)
	{
		if (pass->links[indx][n] == 0)
		{
			(*path)->found = TRUE;
			return ;
		}
		++n;
		++count;
	}
	if (count == 2)
	{
		n = 0;
		if (pass->links[indx][n] == prev)
			++n;
		if (pass->used[pass->links[indx][n]] == FALSE)
		{
			pass->used[pass->links[indx][n]] = TRUE;
			create_index(&(*path)->move_head, *path, pass->links[indx][n]);
			(*path)->move->j = 0;
			index_until_conflict(path, pass, indx, pass->links[indx][n]);
		}
		else
		{
			ft_printf("check connection\n");
			
			check_other_connection(path, pass, pass->links[indx][n]);
		}
	}
}

static void	create_paths(t_path **path, t_room *pass)
{
	int	i;

	*path = pass->head;
	i = 0;
	while (pass->distance[pass->links[pass->end][i]] > 0)
	{
		if ((*path)->found == FALSE)
		{
			if (pass->used[pass->links[pass->end][i]] == TRUE)
			{
				ft_printf("check connection\n");
			
				check_other_connection(path, pass, pass->links[pass->end][i]);
			}
			pass->used[pass->links[pass->end][i]] = TRUE;
			create_index(&(*path)->move_head, *path, pass->links[pass->end][i]);
			(*path)->move->j = 0;
			index_until_conflict(path, pass, pass->end, pass->links[pass->end][i]);
		}
		++i;
		*path = (*path)->next;
	}
}

static t_path	*locate_path_split(t_path *path, t_room *pass, int nbr)
{
	t_path	*head;

	head = pass->head;
	while (head)
	{
		head->move = head->move_head;
		while (head->move)
		{
			if (head->move->index == nbr && path->nbr != head->nbr)
			{
				return (head);
			}
			head->move = head->move->next;
		}
		head = head->next;
	}
	return (NULL);
}

static void	check_other_connection(t_path **path, t_room *pass, int nbr)
{
	/*
				make function that finds the path that contains the current index
					checks if it has other options ex other FREE routes to go down
					if it doesn't
						return NULL pointer
					else if it has another option that is free(check all of it's options)
						delete every index that comes after the current index and try to go down this route
						now the checked index should be free and we can give this path the index now.
					else if it has another option but it isn't free
						call maybe same function and check if whatever index this is connected to if that one has other options
						if it has change it so it becomes free
							delete every index that comes after the current index and try to go down this route
							now the checked index should be free and we can give this path the index now.
						else
							check ALL the conflicting paths that are being compared and get rid of the longest one
			*/
	t_path *temp;

	temp = locate_path_split(*path, pass, nbr);
	if (!temp)
		return ;
	if ((*path)->move_head->prev_split == FALSE && temp->move->prev_split == FALSE)
	{
		if ((*path)->len > temp->len)
		{
			ft_printf("delete path\n");
			// delete path
		}
		else
		{
			ft_printf("delete temp\n");
			// delete temp
		}
	}
	else if ((*path)->move_head->prev_split == FALSE && temp->move->prev_split == TRUE)
	{
		// if current path is == FALSE and the other is TRUE // try to change that path
		// change the temp to earliest previous
		// if ()
		// check_other_connection(&temp, pass, temp->move->index);

	}//if current is true - loop back and try to make the other choise if it is still available
	// if it is not delete the longest branch up until this point.

}

static int	conflict_logic(t_path **path, t_room *pass, int prev, int indx)
{
	int	start;

	start = (*path)->move->j;
	while (pass->links[indx][(*path)->move->j] > 0 && pass->distance[pass->links[indx][(*path)->move->j]] > 0)
	{
		if (pass->info[PREV][pass->links[indx][(*path)->move->j]] == FALSE)
		{
			pass->info[PREV][pass->links[pass->end][(*path)->move->j]] = TRUE;
			create_index(&(*path)->move_head, *path, pass->links[pass->end][(*path)->move->j]);
			return (TRUE);
		}
		if (pass->links[indx][(*path)->move->j] <= 0)
			(*path)->move->j = 0;
		else
			(*path)->move->j++;
		if (start == (*path)->move->j)
			break ;
	}
	return (FALSE);
	
	//solve conflict
}

static void	recursive(t_path **path, t_room *pass)
{
	*path = pass->head;
	while (all_paths_found(pass->head) == FALSE)
	{
		if ((*path)->found == FALSE)
		{
			*path = pass->head;
			while (*path)
			{
				if ((*path)->found == FALSE)
					if (conflict_logic(path, pass, (*path)->move_head->next->index, (*path)->move_head->index) == FALSE)
						return ; 
				*path = (*path)->next;
			}
			*path = pass->head;
			while (*path)
			{
				if ((*path)->found == FALSE)
					index_until_conflict(path, pass, (*path)->move_head->next->index, (*path)->move_head->index);
				*path = (*path)->next;
			}
			recursive(path, pass);
			// *path = pass->head;
			// while (*path)
			// {
			// 	index_until_conflict(path, pass, (*path)->move_head->next->index, (*path)->move_head->index);
			// 	*path = (*path)->next;
			// }
		}
		// while path next (loop thoruhg all the paths)
		// {
		// 	move all paths index until they are moved to a path with multiple options
		// }
		// while path->next (loop through all the paths AGAIN)
		// 	decide which path each path should go down based on above logic
	}
	if (pass->head)
	{
		//ft_printf("struct\n");
		compare_and_copy(path, pass);
	}
}

static void	update_values(t_room *pass, int i, int indx, int nbr)
{
	pass->info[PATH][pass->links[indx][i]] = nbr;
	pass->info[PREV][pass->links[indx][i]] = indx;
	pass->info[LEN][pass->links[indx][i]] = pass->info[LEN][indx] + 1;
	pass->info[CURRENT][nbr - 1] = pass->links[indx][i];
}

static void	move_index(t_room *pass, int prev, int indx, int nbr)
{
	int count;
	int i;

	i = 0;
	if (!pass->info[CONNECT][indx])
	{
		while (pass->distance[pass->links[indx][i]] > 0)
		{
			if (pass->links[indx][i] == 0)
			{
				//start found;
				pass->info[CURRENT][nbr - 1] = 0;
			}
			pass->info[CONNECT][indx]++;
			i++;
		}
	}
	i = 0;
	if (pass->info[CONNECT][indx] == 2)
	{
		while (pass->distance[pass->links[indx][i]] > 0)
		{
			if (pass->info[PATH][pass->links[indx][i]] == 0 && pass->info[PATH][pass->links[indx][i]] != prev)
			{
				update_values(pass, i, indx, nbr);
				move_index(pass, indx, pass->links[indx][i], nbr);
			}
			++i;
		}
	}

}

static int	all_paths_found(t_room *pass)
{
	int	i;

	i = 0;
	while (i < pass->total)
	{
		if (pass->info[CURRENT][i] != 0)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

static void solve_conflict(t_room *pass)
{
	
}

void	path_finder(t_path **path, t_room *pass, int i)
{
	int i;
	int	total;
	
	i = 0;
	while (pass->distance[pass->links[pass->end][i]] > 0)
	{
		if (pass->info[PATH][pass->links[pass->end][i]] == 0)
		{
			update_values(pass, i, pass->end, i + 1);
			// pass->info[PATH][pass->links[pass->end][i]] = i + 1;
			// pass->info[PREV][pass->links[pass->end][i]] = pass->end;
			// pass->info[LEN][pass->links[pass->end][i]] = pass->info[LEN][pass->end] + 1;
			// pass->info[CURRENT][i] = pass->links[pass->end][i];
			move_index(pass, pass->end, pass->links[pass->end][i], i + 1);
		}
		++i;
	}
	total = i;
	while (all_paths_found(pass) == FALSE)
	{
		i = 0;
		while (i < total)
		{
			if (pass->info[CURRENT][i] != 0)
				solve_conflict(pass);
		}
		i = 0;
		while (i < total)
		{
			if (pass->info[CURRENT][i] != 0)
				move_index(pass, pass->info[PREV][pass->info[CURRENT][i]], pass->info[CURRENT][i], i + 1);
			++i;
		}
	}
	// create all the paths and give them the first index
	// create_paths(path, pass);
	// i = 0;
	// ft_printf("\nfound struct\n\n");
	// printf_struct(pass);
	// recursive(path, pass);
	// while (all_paths_found(pass->head) == FALSE)
	// {
		
	// 	if ((*path)->found == FALSE)
	// 	{
	// 		*path = pass->head;
	// 		while (*path)
	// 		{
	// 			index_until_conflict(path, pass, (*path)->move_head->next->index, (*path)->move_head->index);
	// 			*path = (*path)->next;
	// 		}
	// 		// *path = pass->head;
	// 		// while (*path)
	// 		// {
	// 		// 	index_until_conflict(path, pass, (*path)->move_head->next->index, (*path)->move_head->index);
	// 		// 	*path = (*path)->next;
	// 		// }
	// 	}
	// 	// while path next (loop thoruhg all the paths)
	// 	// {
	// 	// 	move all paths index until they are moved to a path with multiple options
	// 	// }
	// 	// while path->next (loop through all the paths AGAIN)
	// 	// 	decide which path each path should go down based on above logic
	// }
	ft_printf("end found\n");
	//exit(0);
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

/*

used = index of previous

how to solve conflict
	if everything is occupied
		go to first acted upon conflict of other path
			if it can choose another path
				choose the other path
				move current J to now opened path
			else if other path is occupied
				need to check that path if it has other options
					if it has other option go to that and update current
					else
						you look at all the paths uptil this point and delete the longest
			else if it no other path
				keep the shortest path

used 2d
- keep count of connections of each room

*/