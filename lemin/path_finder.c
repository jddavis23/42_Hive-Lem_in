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

static void	initialize_path(t_room *pass, int i)
{
	pass->info[PATH][pass->links[0][i]] = 1;
	pass->info[CURRENT][i] = pass->links[0][i];
	pass->info[PREV][pass->links[0][i]] = 0;
}

static int	current_true(t_room *pass)
{
	int i;

	i = 0;
	while (i < pass->total)
	{
		if (pass->info[CURRENT][i] != 0)
		{
			return (FALSE);
		}
		++i;
	}
	return (TRUE);
}

static void	set_correct_current_index(t_room *pass, int *i, int new_indx)
{
	int	j;

	j = 0;
	pass->info[CURRENT][*i] = new_indx;
	while (j < pass->total)
	{
		if (pass->info[CURRENT][j] == 0)
		{
			*i = j;
			break ;
		}
		++j;
	}
}

// static int	check_check(t_room *pass, int indx)
// {
// 	int	i;

// 	while (indx != 0)//pass->info[PREV][indx] != 0)
// 	{
// 		i = 0;
// 		while (pass->links[indx][i] != -1)
// 		{
// 			if (pass->info[PATH][pass->links[indx][i]] == 0)
// 			{
// 				ft_printf("room %s  FINDDDDD %s\n", pass->rooms[indx], pass->rooms[pass->links[indx][i]]);
// 				return (TRUE); 
// 			} 
// 			++i;
// 		}
// 		indx = pass->info[PREV][indx];
// 	}
// 	return (FALSE);
// }

static void	find_new_branches(t_room *pass, int indx, int *i)
{
	int	j;

	j = 0;
	while (pass->links[indx][j] >= 0)
	{
		if (pass->info[PATH][pass->links[indx][j]] == 2)
		{
			pass->info[JUMP][pass->links[indx][j]] = indx;
			pass->info[PATH][pass->links[indx][j]] = 3;
			set_correct_current_index(pass, i, pass->links[indx][j]);
		}
		else if (pass->info[PATH][pass->links[indx][j]] == 0)
		{
			//allow to move
			if (pass->links[indx][j] == 0)
				pass->info[CURRENT][*i] = 0;
			else
			{
				pass->info[PATH][pass->links[indx][j]] = 1;
				pass->info[PREV][pass->links[indx][j]] = indx;
				set_correct_current_index(pass, i, pass->links[indx][j]);
			}
		}
		++j;
	}
	if (pass->info[PATH][pass->info[PREV][indx]] == 2)
	{
		pass->info[PATH][pass->info[PREV][indx]] = pass->info[PATH][indx];
		set_correct_current_index(pass, i, pass->info[PREV][indx]);
	}
}

/*	when moving through a locked_path it will check if it contains a 'jump' from a non-locked path to 	*/

static void	travel_locked_path(t_room *pass, int indx, int *i)
{
	if (pass->info[JUMP][indx])
	{
		//update value to 3
		if (pass->info[PREV][indx] != 0)
			pass->info[PATH][pass->info[PREV][indx]] = pass->info[PATH][indx];
		// unsure about this if statement
		// case of defirentiating between a jump meaning leave path or it having just entered
		if (pass->info[PATH][pass->info[NEXT][indx]] == 2 || pass->info[NEXT][indx] == pass->end)
		{
			set_correct_current_index(pass, i, pass->info[PREV][indx]);//pass->links[indx][j]);
		}
		else
		{
			// find new branch if jump statement
			find_new_branches(pass, indx, i);
		}
	}
	else
	{
		find_new_branches(pass, indx, i);
	}
}

/*
**	when moving through a non-locked path it will check for valid rooms to move into
**	valid rooms contain the value 0 or 2 in the pass->info[PATH]
*/

static void	travel_non_locked_path(t_room *pass, int indx, int *i)
{
	int	j;

	j = 0;
	while (pass->links[indx][j] >= 0)
	{
		if (pass->info[PATH][pass->links[indx][j]] == 0)
		{
			if (pass->links[indx][j] == 0)
				pass->info[CURRENT][*i] = 0;
			else
			{
				pass->info[PATH][pass->links[indx][j]] = pass->info[PATH][indx];
				pass->info[PREV][pass->links[indx][j]] = indx;
				set_correct_current_index(pass, i, pass->links[indx][j]);
			}
		}
		else if (pass->info[PATH][pass->links[indx][j]] == 2)
		{
			pass->info[JUMP][pass->links[indx][j]] = indx;
			pass->info[PATH][pass->links[indx][j]] = 3;
			pass->info[LOCKED][*i] = TRUE;
			set_correct_current_index(pass, i, pass->links[indx][j]);
		}
		++j;
	}
}

/*	
**	breadth first algorithm
**	contains logic of moving through locked and non-locked paths
*/

static void	breadth_first(t_room *pass, int indx, int i)
{
	int	j;

	j = 0;
	if (pass->info[PATH][indx] == 1)
	{
		while (pass->links[indx][j] >= 0)
		{
			if (pass->links[indx][j] == pass->end)
			{
				pass->info[PATH][pass->end] = 1;
				return ;
			}
			++j;
		}
		travel_non_locked_path(pass, indx, &i);
	}
	else if (pass->info[PATH][indx] == 3)
		travel_locked_path(pass, indx, &i);
	if (pass->info[CURRENT][i] == indx)
		pass->info[CURRENT][i] = 0;
}

static void	print_output(t_room *pass)
{
	int	i;
	int	nbr;
	int	prev;
	int new;
	int start;

	new = 0;
	i = 0;
	start = pass->end;
	while (pass->links[start][i] >= 0)
	{
		nbr = pass->info[PATH][pass->links[start][i]];
		if (nbr != 0)
		{
			ft_printf("{green}PATH [%d] {uncolor}\n", new);
			prev = pass->info[PREV][pass->links[start][i]];
			ft_printf("%s\n", pass->rooms[pass->end]);
			ft_printf("%s\n", pass->rooms[pass->links[start][i]]);
			while (prev > 0)
			{
				ft_printf("%s\n", pass->rooms[prev]);
				prev = pass->info[PREV][prev];
			}
			new++;
		}
		++i;
	}
	i = 0;
	ft_printf("\n\n------------\nrooms path nbr:	PREV	NEXT	JUMP\n");
	while (i < pass->total)
	{
		ft_printf("[%s][%d]: [%d] 	[%s]	[%s]	[%s]\n",pass->rooms[i], i, pass->info[PATH][i], pass->rooms[pass->info[PREV][i]], pass->rooms[pass->info[NEXT][i]], pass->rooms[pass->info[JUMP][i]]);
		++i;
	}
}

static void	lock_path(t_room *pass, int indx)
{
	int	hold;

	pass->info[NEXT][indx] = pass->end; 
	ft_printf("FIRST INDX %s\n", pass->rooms[indx]);
	while (indx != 0)
	{
		if (pass->info[PATH][indx] == 3)
		{
			hold = pass->info[NEXT][indx];
			pass->info[NEXT][indx] = pass->info[PREV][indx];
			indx = hold;
			while (pass->info[JUMP][indx] != 0)
			{
				if (pass->info[PATH][indx] == 3)
					pass->info[PATH][indx] = 2;
				indx = pass->info[PREV][indx];
				//pass->info[NEXT][indx];
				//if (pass->info[PREV][indx] != pass->info[NEXT][indx])
			}
			if (pass->info[JUMP][indx] != 0)
				pass->info[PREV][indx] = pass->info[JUMP][indx];
		}
		pass->info[PATH][indx] = 2;
		if (pass->info[PREV][indx] != 0)
			pass->info[NEXT][pass->info[PREV][indx]] = indx;
		indx = pass->info[PREV][indx];
	}

}

static void	delete_non_found_paths(t_room *pass, int indx)
{
	int	i;

	lock_path(pass, indx);
	ft_printf("----LOCKED PATH-----\n");
	print_output(pass);
	
	i = 0;
	while (i < pass->total)
	{
		if (pass->info[PATH][i] == 1)
		{
			pass->info[PATH][i] = 0;
			pass->info[PREV][i] = 0;
			pass->info[NEXT][i] = 0;
			pass->info[LEN][i] = 0;//should be able to delete
		}
		else if (pass->info[PATH][i] == 3)
		{
			pass->info[PATH][i] = 2;
			pass->info[JUMP][i] = 0;
		}
		pass->info[CURRENT][i] = FALSE;
		++i;
	}
}


static int	compare_function(t_room *pass, int indx, int start)
{
	int	i;
	int	prev;

	i = 0;
	while (pass->links[0][i] != -1)
	{
		if (pass->info[PATH][pass->links[0][i]] == 2 && pass->links[0][i] != start)
		{
			if (pass->links[0][i] == indx)
			{
				prev = pass->info[PREV][pass->links[0][i]];
				prev = pass->info[PREV][prev];
				while (prev > 0 && prev != pass->end)
				{
					if (prev == indx)
					{
						return (FALSE);
					}
					prev = pass->info[PREV][prev];
				}
			}
			else
			{
				prev = pass->info[PREV][pass->links[0][i]];
				while (prev > 0 && prev != pass->end)
				{
					if (prev == indx)
					{
						return (FALSE);
					}
					prev = pass->info[PREV][prev];
				}
			}
		}
		++i;
	}
	return (TRUE);
}

static int	unique_paths(t_room *pass)
{
	int	i;
	int	compare;
	int	prev;

	i = 0;
	while (pass->links[0][i] != -1)
	{
		if (pass->info[PATH][pass->links[0][i]] == 2)
		{
			prev = pass->info[PREV][pass->links[0][i]];
			compare = pass->links[0][i];
			if (compare_function(pass, compare, pass->links[0][i]) == FALSE)
				return (FALSE);
			while (prev > 0 && prev != pass->end)
			{
				compare = prev;
				if (compare_function(pass, compare, pass->links[0][i]) == FALSE)
				{
					return (FALSE);
				}
				prev = pass->info[PREV][prev];
			}
		}
		++i;
	}
	return (TRUE);
}

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

static void	calc_len(t_room *pass, int **len)
{
	int	i;
	int	prev;
	int	count;
	int	j;

	i = 0;
	j = 0;
	while (pass->links[0][i] != -1)
	{
		if (pass->info[PATH][pass->links[0][i]] == 2)
		{
			count = 1;
			prev = pass->links[0][i];
			while (prev != 0)
			{
				++count;
				prev = pass->info[PREV][prev];
			}
			pass->info[LEN][pass->links[0][i]] = count + 2;
			(*len)[j++] = pass->links[0][i];
		}
		++i;
	}
}

static void	copy_to_path(t_room *pass, t_path **path, int **len)
{
	int	i;
	int	next;
	int	nbr;

	nbr = 1;
	int m = 0;
	while ((*len)[m] != -1)
	{
		ft_printf("%d ", (*len)[m]);
		m++;
	}
	i = 0;
	while ((*len)[i] > 0)
	{
		next = pass->info[NEXT][(*len)[i]];
		create_path(path, pass, nbr, pass->info[LEN][(*len)[i]]);
		create_index(&(*path)->move_head, path, (*len)[i]);
		while (next > 0)
		{
			create_index(&(*path)->move_head, path, next);
			next = pass->info[NEXT][next];
		}
		pass->info[PATH][(*len)[i]] = 0;
		++i;
	}
	reset_len(len);
}

static void	printf_struct(t_room *pass)
{
	t_path *final;
	t_index *temp;
	int i;
	final = pass->final_head;
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


// static int	diff_prev(int **len, int current)
// {
// 	int count;
// 	int	i;

// 	i = 0;
// 	count = 0;
// 	while ((*len)[i] != -1)
// 	{
// 		if ((*len)[i] == current)
// 			break ;
// 		count += current - (*len)[i];
// 		++i;
// 	}
// 	return (count);
// }

// static int max_ant_calc(int ants, int **len, int current)
// {
// 	int	dif;
// 	int	i;
// 	int	prev;
// 	int	max_ants;

// 	i = 0;
// 	dif = 0;
// 	while ((*len)[i] != 1 && (*len)[i] != 0 && (*len)[i] != current)
// 		++i;
// 	prev = i - 1;
// 	if (prev < 0)
// 		return (FALSE);
// 	dif = diff_prev(len, (*len)[prev]) + ((current - (*len)[prev]) * i);
// 	max_ants = dif + i;
// 	if (ants <= max_ants)
// 		return (TRUE);
// 	return (FALSE);
// }

// static void	current_path(t_room *pass)
// {
// 	int i;

// 	i = 0;

// 	ft_printf("PATH LOCKED OR NOT\n");
// 	while (i < pass->total)
// 	{
// 		ft_printf("room %s: %d PREV %s\n", pass->rooms[i], pass->info[PATH][i], pass->rooms[pass->info[PREV][i]]);
// 		++i;
// 	}
// }

static int	compare_struct(t_room *pass, float mean, int count)
{
	int	len;
	float	mean_old;
	int path_count;
	t_path *temp;

	temp = pass->final_head;
	len = 0;
	while (temp)
	{
		len += temp->len;
		path_count = temp->nbr;
		temp = temp->next;
	}
	mean_old = (float)len / (float)path_count;
	if (path_count < count)
		return (TRUE);
	if (path_count > count)
		return (FALSE);
	if (mean_old > mean)
		return (TRUE);
	return (FALSE);
}

static int	better_choice(t_room *pass, int **len)
{
	int	len_total;
	int	path_count;
	float	mean;

	path_count = 0;
	len_total = 0;
	path_count = 0;
	calc_len(pass, len);
	while ((*len)[path_count] > 0)
	{
		len_total += pass->info[LEN][(*len)[path_count]];
		++path_count;
	}
	mean = (float)len_total / (float)path_count;
	/*

	//if (max_ant_calc(pass->ants, len, pass->info[LEN][pass->info[CURRENT][i]]) == TRUE)
	// 	break ;

	*/
	if (compare_struct(pass, mean, path_count) == TRUE)
		return (TRUE);
	return (FALSE);
}

static int	current_len(t_room *pass)
{
	int i;

	i = pass->total;
	while (i > 0)
	{
		if (pass->info[CURRENT][i--] != 0)
			break; 
	}
	return (i + 2);
}

void	path_finder(t_path **path, t_room *pass)
{
	int	i;
	int	c_len;
	int	*len;

	i = 0;
	len = NULL;
	create_len(pass->links[0], &len);
	pass->info[LEN][0] = 1;
	pass->info[PATH][0] = 0;
	// b
	pass->info[PATH][1] = 2;
	pass->info[PREV][1] = 0;
	pass->info[NEXT][1] = 2;
	// c
	pass->info[PATH][2] = 2;
	pass->info[PREV][2] = 1;
	pass->info[NEXT][2] = 9;
	// j
	pass->info[PATH][9] = 2;
	pass->info[PREV][9] = 2;
	pass->info[NEXT][9] = 17;
	// o
	pass->info[PATH][13] = 2;
	pass->info[PREV][13] = 0;
	pass->info[NEXT][13] = 3;
	// d
	pass->info[PATH][3] = 2;
	pass->info[PREV][3] = 13;
	pass->info[NEXT][3] = 16;
	// q
	pass->info[PATH][15] = 2;
	pass->info[PREV][15] = 16;
	pass->info[NEXT][15] = 17;

	// x
	pass->info[PATH][16] = 2;
	pass->info[PREV][16] = 3;
	pass->info[NEXT][16] = 15;
	
	while (pass->links[0][i] >= 0)
	{
		if (pass->links[0][i] == 5)
			initialize_path(pass, i++);
		i++;
	}
	int nbr = 0;
	print_output(pass);
	while (!current_true(pass))
	{
		i = 0;
		c_len = current_len(pass);
		ft_printf("c_len: %d\n", c_len);
		while (i < c_len)
		{
			if (pass->info[CURRENT][i] != 0)
			{
				breadth_first(pass, pass->info[CURRENT][i], i);
				if (pass->info[PATH][pass->end] == 1)
				{
					break ;
				}
				//print_output(pass);
				//if (pass->info[PREV][9] == 2 && pass->info[PATH][1] == 2)
				//	exit (0);
			}
			++i;
		}
		if (pass->info[PATH][pass->end] == 1)
		{
			print_output(pass);
			exit(0);
			pass->info[PATH][0] = 0;
			delete_non_found_paths(pass, pass->info[CURRENT][i]);
			ft_printf("----- AFTER CLEAN -----");
			print_output(pass);
			nbr++;
			if (nbr == 2)
				exit(0);
			if (!pass->final_head)// && new_path_better(pass, path) == FALSE)
			{
				calc_len(pass, &len);
				copy_to_path(pass, path, &len);
			}
			else if (better_choice(pass, &len) == TRUE)
			{
				del_path(&pass->final_head);
				*path = NULL;
				copy_to_path(pass, path, &len);
			}
			ft_printf("\n\n-------PATH IN STRUCT-------\n");
			printf_struct(pass);
			ft_printf("\n\n-------PATH IN STRUCT FINISH-------\n");
			i = 0;
			while (pass->links[pass->end][i] >= 0)
			{
				if (pass->info[PATH][pass->links[pass->end][i]] == 0)
					initialize_path(pass, i);
				++i;
			}
			//current_path(pass);
		}
		//print_output(pass);
	}
	//print_output(pass);
	if (*len)
		i = 0;
	//current_path(pass);
	if (unique_paths(pass) == FALSE)
		ft_printf("FALSE\n");
	else
		ft_printf("TRUE\n");
	delete_non_found_paths(pass, 0);
	ft_printf("{green}PRINT PRINT{uncolor}\n");
	i = 0;
	while (pass->links[0][i] != -1)
	{
		if (pass->info[PATH][pass->links[0][i]] == 2)
		{
			ft_printf("rooms: %s\n", pass->rooms[pass->links[0][i]]);
			int o = pass->info[PREV][pass->links[0][i]];
			while (o > 0)
			{
				ft_printf("prev: %s\n", pass->rooms[o]);
				o = pass->info[PREV][o];
			}
			ft_printf("\n");
		}
		++i;
	}
	if (!pass->final_head)// && new_path_better(pass, path) == FALSE)
	{
		copy_to_path(pass, path, &len);
	}
	else if (better_choice(pass, &len) == TRUE)
	{
		del_path(&pass->final_head);
		*path = NULL;
		copy_to_path(pass, path, &len);
	}
	printf_struct(pass);
	//exit(0);
}
