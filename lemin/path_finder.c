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

static void	print_output(t_room *pass)
{
	int	i;
	int	nbr;
	int	prev;

	i = 0;
	while (pass->links[0][i] >= 0)
	{
		nbr = pass->info[PATH][pass->links[0][i]];
		if (nbr != 0)
		{
			ft_printf("{green}PATH [%d] LEN[%d]{uncolor}\n", nbr, pass->info[LEN][pass->links[0][i]]);
			prev = pass->info[PREV][pass->links[0][i]];
			ft_printf("%s\n", pass->rooms[pass->links[0][i]]);
			while (prev > 0)
			{
				ft_printf("%s\n", pass->rooms[prev]);
				prev = pass->info[PREV][prev];
			}
		}
		++i;
	}
	i = 0;
	ft_printf("\n\n------------\nrooms path nbr:\n");
	while (i < pass->total)
	{
		ft_printf("%s: %d \n",pass->rooms[i], pass->info[PATH][i]);
		++i;
	}
}

static void	update_values(t_room *pass, int i, int indx, int nbr)
{
	pass->info[PATH][pass->links[indx][i]] = nbr;
	pass->info[PREV][pass->links[indx][i]] = indx;
	pass->info[LEN][pass->links[indx][i]] = pass->info[LEN][indx] + 1;
	pass->info[CURRENT][nbr - 1] = pass->links[indx][i];
}

static int check_connect(t_room *pass, int indx, int nbr)
{
	int i;
	int non;

	i = 0;
	if (!pass->info[CONNECT][indx])
		non = TRUE;
	else
		non = FALSE;
	while (pass->distance[pass->links[indx][i]] >= 0 && pass->links[indx][i] != -1)
	{
		if (non == TRUE)
			pass->info[CONNECT][indx]++;
		//ft_printf("found start, room: %s, link: %s\n", pass->rooms[indx], pass->rooms[pass->links[indx][i]]);
		if (pass->links[indx][i] == 0)
		{
			//start found;
			//ft_printf("found start, room: %s, link: %s, nbr: %d\n", pass->rooms[indx], pass->rooms[pass->links[indx][i]], nbr - 1);
			pass->info[CURRENT][nbr - 1] = 0;
			pass->info[CONNECT][indx] = 0;
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

static int	future_conflict_free(t_room *pass, int prev, int indx, int nbr)
{
	int	i;

	if (check_connect(pass, indx, nbr) == FALSE)
		return (TRUE);
	i = 0;
	ft_printf("----room: %s %d  [%d]\n", pass->rooms[indx], pass->info[PATH][indx], pass->info[CONNECT][indx]);
	if (pass->info[CONNECT][indx] == 2)
	{
		while (pass->distance[pass->links[indx][i]] > 0 && pass->links[indx][i] != -1)
		{
			ft_printf("----room: %s %d\n", pass->rooms[pass->links[indx][i]], pass->info[PATH][pass->links[indx][i]]);
			if (pass->info[PATH][pass->links[indx][i]] == 0 && pass->links[indx][i] != prev)
			{
				if (future_conflict_free(pass, indx, pass->links[indx][i], nbr) == TRUE)
				{
					return (TRUE);
				}
			}
			++i;
		}
		ft_printf("RETURNS FALSE\n");
		return (FALSE);
	}
	return (TRUE);
	// else
	// {
	// 	while (pass->distance[pass->links[indx][i]] >= 0 && pass->links[indx][i] != -1)
	// 	{
	// 		if (pass->info[PATH][pass->links[indx][i]] == 0 && pass->links[indx][i] != prev && \
	// 			pass->info[PREV][pass->links[indx][i]] == 0)
	// 		{
	// 			return (TRUE);
	// 		}
	// 		++i;
	// 	}
	// }
	return (FALSE);
}

static int	future_conflict_free_recursive(t_room *pass, int prev, int indx, int nbr)
{
	int	i;
	//static int save = 0;

	if (pass->save)
	{
		return (pass->save);
	}
	if (check_connect(pass, indx, nbr) == FALSE)
		return (0);
	i = 0;
	//save = 0;
	if (pass->info[CONNECT][indx] == 2)
	{
		while (pass->distance[pass->links[indx][i]] > 0 && pass->links[indx][i] != -1)
		{
			if (pass->info[PATH][pass->links[indx][i]] == 0 && pass->links[indx][i] != prev && \
				pass->info[PREV][pass->links[indx][i]] == 0)
			{
				if (!pass->save && future_conflict_free_recursive(pass, indx, pass->links[indx][i], nbr) == 0)
				{
					return (0);
				}
			}
			else if (pass->links[indx][i] != prev && pass->info[PATH][pass->links[indx][i]] != pass->info[PATH][indx])
			{
				pass->save = pass->links[indx][i];
			}
			++i;
		}
	}
	return (pass->save);
}

static void	move_index(t_room *pass, int prev, int indx, int nbr)
{
	int i;

	if (check_connect(pass, indx, nbr) == FALSE)
		return ;
	i = 0;
	if (pass->info[CONNECT][indx] == 2)
	{
		ft_printf("HERE\n");
		while (pass->distance[pass->links[indx][i]] > 0 && pass->links[indx][i] != -1)
		{
			if (pass->info[PATH][pass->links[indx][i]] == 0 && pass->links[indx][i] != prev && \
				pass->info[PREV][pass->links[indx][i]] == 0)
			{
				update_values(pass, i, indx, nbr);
				move_index(pass, indx, pass->links[indx][i], nbr);
				return ;
			}
			++i;
		}
	}

}

static int	all_paths_found(t_room *pass)
{
	int	i;

	i = 0;
	ft_printf("all paths found: ");
	while (i < pass->total)
	{
		ft_printf("%d \n", pass->info[CURRENT][i]);
		if (pass->info[CURRENT][i] != 0)
		{
			return (FALSE);
		}
		++i;
	}
	return (TRUE);
}

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

*/

static void	delete_begin(t_conflict **temp)
{
	t_i_conf	*pnt;
	t_i_conf	*move;

	pnt = (*temp)->move_head;
	while (pnt && pnt->index != (*temp)->move->index)
	{
		move = pnt;
		pnt = pnt->next;
		free(move);
	}
	(*temp)->move_head = pnt;
}

static t_i_conf	*ft_newindex(int index)
{
	t_i_conf *new;

	new = (t_i_conf *)malloc(sizeof(t_i_conf));
	if (!new)
		return (NULL);
	new->index = index;
	new->i = 0;
	new->next = NULL;
	return (new);
}

static void	create_conflict(t_room *pass, int nbr)
{
	t_conflict	*node;
	t_conflict	*temp;

	node = (t_conflict *)malloc(sizeof(t_conflict));
	if (!node)
		return ;
	node->nbr = nbr + 1;
	node->move = ft_newindex(pass->info[CURRENT][nbr]);
	node->move_head = node->move;
	node->next = NULL;
	if (!pass->conf_head)
	{
		pass->conf_head = node;
	}
	else
	{
		temp = pass->conf_head;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = node;
	}
}

static void	add_conflict(t_room *pass, int index, int nbr)
{
	t_conflict	*temp;
	t_i_conf	*new;

	temp = pass->conf_head;
	while (temp && temp->nbr != nbr)
	{
		temp = temp->next;
	}
	new = NULL;
	if (temp && !temp->move)
	{
		temp->move = ft_newindex(index);
		temp->move_head = temp->move;
	}
	else if (temp)
	{
		new = ft_newindex(index);
		new->next = temp->move_head;
		temp->move_head = new;
	}
}

static int	check_neighbors(t_room *pass, int prev, int indx, int nbr)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	ft_printf("HERE\n");
	if (check_connect(pass, indx, nbr) == FALSE)
		return (TRUE);
	ft_printf("MAIN ROOM: %s\n", pass->rooms[indx]);
	while (pass->distance[pass->links[indx][i]] >= 0 && pass->links[indx][i] != -1)
	{
		ft_printf("roooooom: %s %d\n", pass->rooms[pass->links[indx][i]], pass->info[PATH][pass->links[indx][i]]);
		if (pass->info[PATH][pass->links[indx][i]] == 0 && pass->links[indx][i] != prev && \
			pass->info[PREV][pass->links[indx][i]] == 0 && future_conflict_free(pass, indx, pass->links[indx][i], nbr) == TRUE)
		{
			update_values(pass, i, indx, nbr);
			return (TRUE);
		}
		// else if (pass->info[PATH][pass->links[indx][i]] != prev)
		// {
		// 	pass->info[CONFLICT][j++] = pass->info[PATH][pass->links[indx][i]];
		// }
		++i;
	}
	return (FALSE);
}

static void	delete_path(t_room *pass, int nbr)
{
	int	i;

	i = 0;
	while (i < pass->total)
	{
		if (pass->info[PATH][i] == nbr)
		{
			pass->info[CURRENT][nbr - 1] = 0;
			pass->info[PREV][i] = 0;
			pass->info[PATH][i] = 0;
			pass->info[LEN][i] = 0;
		}
		++i;
	}
}

static void	print_struct(t_room *pass)
{
	t_conflict *temp;
	temp = pass->conf_head;
	while (temp)
	{
		temp->move = temp->move_head;
		ft_printf("\npath nbr[%d]: ", temp->nbr);
		while (temp->move)
		{
			ft_printf("room %s[%d] ", pass->rooms[temp->move->index], temp->move->index);
			temp->move = temp->move->next;
		}
		temp->move = temp->move_head;
		ft_printf("\n");
		temp = temp->next;
	}
}

static void	removes_path_cur_pos(t_room *pass, int indx, int nbr)
{
	int	element;
	int	next;
	int	i;

	if (pass->info[CURRENT][nbr - 1] == 0)
	{
		i = 0;
		while (pass->links[0][i] != -1 && pass->info[PATH][pass->links[0][i]] != nbr)
		{
			++i;
		}
		element = pass->links[0][i];
	}
	else
		element = pass->info[CURRENT][nbr - 1];
	next = pass->info[PREV][element];
	pass->info[CURRENT][pass->info[PATH][element] - 1] = 0;
	pass->info[PATH][element] = 0;
	pass->info[LEN][element] = 0;
	pass->info[PREV][element] = 0;
	while (next != indx)
	{
		element = next;
		next = pass->info[PREV][next];
		pass->info[CURRENT][pass->info[PATH][element] - 1] = 0;
		pass->info[PATH][element] = 0;
		pass->info[LEN][element] = 0;
		pass->info[PREV][element] = 0;
	}
}

/*

make function that loops through struct of the conflicting path


*/

int	can_block_change(t_room *pass, int orig, int indx, int nbr);

static int	recursive(t_room *pass, t_conflict *temp, int indx, int nbr)
{
	int	i;

	i = 0;
	//ft_printf("orig room: %s	\n", pass->rooms[temp->move->index]);
	while (pass->links[temp->move->index][i] != -1 && pass->distance[pass->links[temp->move->index][i]] > 0)
	{
		//ft_printf("room: %s	\n", pass->rooms[pass->links[temp->move->index][i]]);
		if (pass->info[PATH][pass->links[temp->move->index][i]] == 0 && \
		pass->info[PATH][pass->links[temp->move->index][i]] != nbr && \
		pass->info[PATH][temp->move->index] != pass->info[PATH][pass->links[temp->move->index][i]] && \
		pass->links[temp->move->index][i] != pass->end)
		{
			// ft_printf("free path BEFORE------\n");
			// print_output(pass);
			removes_path_cur_pos(pass, temp->move->index, pass->info[PATH][temp->move->index]);//indx we want the deleting to stop and number of path we want to delete
			delete_begin(&temp);
			update_values(pass, i, temp->move->index, pass->info[PATH][temp->move->index]);
			// ft_printf("free path AFTER-----\n");
			// print_output(pass);
			temp->move = temp->move_head;
			return (TRUE);
		}
		else if (pass->info[PATH][pass->links[temp->move->index][i]] != nbr && \
		pass->info[PATH][temp->move->index] != pass->info[PATH][pass->links[temp->move->index][i]] && \
		pass->links[temp->move->index][i] != pass->end)
		{
			// want to call this function when having to recurse to next spot to see if we can free a path somewhere else
			//ft_printf("FrEEE room: %s\n", pass->rooms[pass->links[temp->move->index][i]]);
			if (can_block_change(pass, temp->move->index, pass->links[temp->move->index][i], pass->info[PATH][temp->move->index]) == TRUE)
			{
				recursive(pass, temp, temp->move->index, pass->info[PATH][temp->move->index]);
				temp->move = temp->move_head;
				return (TRUE);
			}
		}
		++i;
	}
	//ft_printf("notnot free\n");
	if (indx)
		++i;
	return (FALSE);
}


int	can_block_change(t_room *pass, int orig, int indx, int nbr)
{
	t_conflict *temp;
	int	i;

	temp = pass->conf_head;
	ft_printf("ROOM: %s\n", pass->rooms[indx]);
	if (pass->info[LEN][indx] > pass->info[LEN][orig])
		pass->longest = pass->info[PATH][indx];
	while (temp && temp->nbr != pass->info[PATH][indx])
	{
		temp = temp->next;
	}
	ft_printf("HEIREJOFIF\n");
	i = 0;
	temp->move = temp->move_head;
	ft_printf("HEIREJOFIF\n");
	if (temp->move->index == pass->info[CURRENT][pass->info[PATH][indx] - 1])
	{
		// while (temp && temp->move->next && temp->move->index != indx)
		// 	temp->move = temp->move->next;
		ft_printf("ROOM: %s\n", pass->rooms[temp->move->index]);
		while (temp->move->next)
		{
			temp->move = temp->move->next;
			if (recursive(pass, temp, indx, nbr) == TRUE)
			{
				// 	removes_path_cur_pos(pass, 8, 3);//indx we want the deleting to stop and number of path we want to delete
				return (TRUE);
			}
		}
		temp->move = temp->move_head;
	}
	else
	{
		ft_printf("ROOM2: %s\n", pass->rooms[temp->move->index]);
	
		while (temp->move)
		{
			if (recursive(pass, temp, indx, nbr) == TRUE)
			{
				//removes_path_cur_pos(pass, 8, 3);//indx we want the deleting to stop and number of path we want to delete
				return (TRUE);
			}
			temp->move = temp->move->next;
		}
		temp->move = temp->move_head;
	}
	if (orig)
		++i;
	ft_printf("not free path\n");
	return (FALSE);
	/*
		we cant use it if it is the following

		if block is the current of the path we have to look at the conflict before that to see if we can change the path
		if current is beginning we can still try and change the path.
		if the paths block is the same as the current path and the orig paths number
	*/
	/*
	while (pass->links[indx][i] != -1 && pass->distance[pass->links[indx][i]] >= 0)
	{
	*/
}

static int	nothing_blocks(t_room *pass, int prev, int indx, int nbr)
{
	// check number of blocking paths go one number at a time
	t_conflict *temp;
	int	i;
	int	pnt;

	temp = pass->conf_head;
	i = 0;
	pass->save = 0;
	while (pass->links[indx][i] != -1 && pass->distance[pass->links[indx][i]] >= 0)
	{
		pnt = future_conflict_free_recursive(pass, indx, pass->links[indx][i], nbr);
		//future_conflict_free(pass, indx, pass->links[indx][i], nbr) == TRUE
		ft_printf("save: [%s]\n", pass->rooms[pnt]);
	
		if (pnt != 0)
		{
			if (can_block_change(pass, prev, pnt, nbr) == TRUE)
			{
				//change it
				ft_printf("block can can change: %s, %d\n", pass->rooms[indx], nbr);
				update_values(pass, i, indx, nbr);
				move_index(pass, indx, pass->links[indx][i], nbr);
				
				print_struct(pass);
				print_output(pass);
				ft_printf("block shouldn't change: %s, %d\n", pass->rooms[pass->links[indx][i]], nbr);
				
				//exit(0);
				return (TRUE);
			}
		}
		else if (can_block_change(pass, prev, pass->links[indx][i], nbr) == TRUE)
		//if (can_block_change(pass, prev, pass->links[indx][i], nbr) == TRUE)
		{
			//change it
			ft_printf("block can jhihiid change: %s, %d\n", pass->rooms[indx], nbr);
			//removes_path_cur_pos(pass, indx, pass->info[PATH][indx]);//indx we want the deleting to stop and number of path we want to delete
			ft_printf("UPDATEDVALUES %s\n", pass->rooms[pass->info[CURRENT][pass->info[PATH][indx] - 1]]);
				
			if (indx == pass->info[CURRENT][pass->info[PATH][indx] - 1])
			{
				update_values(pass, i, indx, nbr);
			}
			
			print_struct(pass);
			print_output(pass);
			//exit(0);
			return (TRUE);
		}
		++i;
	}
	return (FALSE);
}

static void solve_conflict(t_room *pass, int prev, int indx, int nbr)
{
	if (check_connect(pass, indx, nbr) == FALSE)
		return ;//returns if start is found;
	// if something is free choose that
	if (check_neighbors(pass, prev, indx, nbr) == TRUE)
	{
		//clean_conflict(pass);
		return ;
		
	}
	// if we reach here it means a path hasn't been choosen / found
	// check if we can move another path
	ft_printf("CONFLICT-----------------------\n");
	print_output(pass);

	ft_printf("\n\nconflict, room: %s\n", pass->rooms[indx]);
	// check nbr of all connections - compare longest nbr value of each path and delete the worst one
	// if (check_connections(pass, indx, nbr) == FALSE)
	pass->longest = nbr;
	if (nothing_blocks(pass, indx, indx, nbr) == FALSE)
	{
		ft_printf("NEGATIVE\n");
		delete_path(pass, pass->longest);
		nothing_blocks(pass, indx, indx, nbr);
	}
	//clean_conflict(pass);
	print_output(pass);
	ft_printf("\n\nEND CONFLICT-----------------------\n");
}

void	path_finder(t_path **path, t_room *pass, int i)
{
	//int i;
	int	total;
	
	i = 0;
	pass->info[PREV][pass->end] = -1;
	pass->info[LEN][pass->end] = 1;
	pass->conf_head = NULL;
	while (pass->distance[pass->links[pass->end][i]] > 0)
	{
		if (pass->info[PATH][pass->links[pass->end][i]] == 0 && pass->info[PREV][pass->links[pass->end][i]] == 0)
		{
			update_values(pass, i, pass->end, i + 1);
			move_index(pass, pass->end, pass->links[pass->end][i], i + 1);
			create_conflict(pass, i);
		}
		++i;
	}
	total = i;
	print_struct(pass);
	print_output(pass);
	while (all_paths_found(pass) == FALSE)
	{
		i = 0;
		while (i < total)
		{
			//ft_printf("i: %d, current: %s, connect: %d\n", i, pass->rooms[pass->info[CURRENT][i]], pass->info[CONNECT][i]);
			if (pass->info[CURRENT][i] != 0 && pass->info[CONNECT][pass->info[CURRENT][i]] != 2)
			{
				solve_conflict(pass, pass->info[PREV][pass->info[CURRENT][i]], pass->info[CURRENT][i], i + 1);
			}
			++i;
		}
		ft_printf("-----\n");
		
		i = 0;
		while (i < total)
		{
			//ft_printf("i: %d, current: %s\n", i, pass->rooms[pass->info[CURRENT][i]]);
			if (pass->info[CURRENT][i] != 0)
			{
				ft_printf("CURRENT BEFORE MVOE INDEX %s\n", pass->rooms[pass->info[CURRENT][i]]);
					
				move_index(pass, pass->info[PREV][pass->info[CURRENT][i]], pass->info[CURRENT][i], i + 1);
				if (pass->info[CURRENT][i] != 0)
				{
					ft_printf("CURRENT BEFORE UPDATE CONFLICT %s\n", pass->rooms[pass->info[CURRENT][i]]);
					add_conflict(pass, pass->info[CURRENT][i], pass->info[PATH][pass->info[CURRENT][i]]);
				}
			}
			
			++i;
		}
		//print_struct(pass);
	}
	ft_printf("finished\n");
	print_struct(pass);
	print_output(pass);
	if (!(*path))
		++i;
	
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

