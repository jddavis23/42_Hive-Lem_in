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
	pass->info[LEN][pass->links[0][i]] = 1;
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

static void	remove_branch(t_room *pass, int *i)
{
	pass->info[CURRENT][*i] = 0;
	pass->info[LOCKED][*i] = 0;
	pass->info[MOVE][*i] = 0;
}

static void	find_new_branches(t_room *pass, int indx, int *i)
{
	int	j;
	int	temp;

	j = 0;
	temp = *i;
	while (pass->links[indx][j] >= 0)
	{
		if (pass->info[PATH][pass->links[indx][j]] == 2 && \
			pass->info[PATH][pass->info[PREV][pass->links[indx][j]]] >= 2)
		{
			if (pass->links[indx][j] != pass->info[PREV][indx])
			{
				pass->info[LOCKED][*i] = TRUE;
				pass->info[JUMP][pass->links[indx][j]] = indx;
			}
			pass->info[PATH][pass->links[indx][j]] = 3;
			set_correct_current_index(pass, i, pass->links[indx][j]);
		}
		else if (pass->info[PATH][pass->links[indx][j]] == 0)
		{
			if (pass->links[indx][j] == 0)
			{
				remove_branch(pass, i);
			}
			else
			{
				pass->info[PATH][pass->links[indx][j]] = 1;
				pass->info[PREV][pass->links[indx][j]] = indx;
				pass->info[LEN][pass->links[indx][j]] = pass->info[LEN][indx] + 1;
				set_correct_current_index(pass, i, pass->links[indx][j]);
			}
		}
		else if (pass->info[PATH][pass->links[indx][j]] == 1 && pass->info[LEN][indx] < pass->info[LEN][pass->links[indx][j]] && \
			pass->info[PATH][pass->info[PREV][pass->links[indx][j]]] == 3)
		{
			pass->info[PREV][pass->links[indx][j]] = indx;
			pass->info[LEN][pass->links[indx][j]] = pass->info[LEN][indx] + 1;
			set_correct_current_index(pass, i, pass->links[indx][j]);
		}
		++j;
	}
	if (pass->info[PATH][pass->info[PREV][indx]] == 3 && pass->info[MOVE][temp] == FALSE)
	{
		temp = *i;
		set_correct_current_index(pass, i, pass->info[PREV][indx]);
		pass->info[MOVE][temp] = TRUE;
	}
	else if (pass->info[PATH][pass->info[PREV][indx]] == 2)
	{
		pass->info[MOVE][*i] = FALSE;
		pass->info[PATH][pass->info[PREV][indx]] = 3;
		set_correct_current_index(pass, i, pass->info[PREV][indx]);
	}
	else if (pass->info[MOVE][temp] == TRUE)
	{
		pass->info[MOVE][temp] = FALSE;
	}
}

/*	when moving through a locked_path it will check if it contains a 'jump' from a non-locked path to 	*/

static void	travel_locked_path(t_room *pass, int indx, int *i)
{
	if (pass->info[JUMP][indx] && pass->info[LOCKED][*i] == TRUE)
	{
		pass->info[LOCKED][*i] = FALSE;
		ft_printf("here\n");
		if (pass->info[PREV][indx] != 0)
		{
			pass->info[PATH][pass->info[PREV][indx]] = pass->info[PATH][indx];
			set_correct_current_index(pass, i, pass->info[PREV][indx]);
		}
	}
	else
	{
		ft_printf("%s [%d]\n", pass->rooms[indx], pass->info[PATH][indx]);
		
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
				remove_branch(pass, i);
			else
			{
				pass->info[PATH][pass->links[indx][j]] = pass->info[PATH][indx];
				pass->info[PREV][pass->links[indx][j]] = indx;
				pass->info[LEN][pass->links[indx][j]] = pass->info[LEN][indx] + 1;
				ft_printf("ASSIGN LEN %s [%d] -> %s [%d]\n", pass->rooms[indx], pass->info[LEN][indx], pass->rooms[pass->links[indx][j]], pass->info[LEN][pass->links[indx][j]]);
				set_correct_current_index(pass, i, pass->links[indx][j]);
			}
		}
		else if (pass->info[PATH][pass->links[indx][j]] == 2 && \
			pass->info[PATH][pass->info[PREV][pass->links[indx][j]]] >= 2)
		{
			ft_printf("CHANGE -----------\n");
			pass->info[JUMP][pass->links[indx][j]] = indx;
			pass->info[LOCKED][*i] = TRUE;
			pass->info[PATH][pass->links[indx][j]] = 3;
			//pass->info[LEN][pass->links[indx][j]] = pass->info[LEN][indx] + 1;
			set_correct_current_index(pass, i, pass->links[indx][j]);
		}
		else if (pass->info[PATH][pass->links[indx][j]] == 1 && \
			pass->info[LEN][indx] + 1 < pass->info[LEN][pass->links[indx][j]] && \
			pass->links[indx][j] != pass->info[PREV][indx]
		)
		{
			pass->info[PREV][pass->links[indx][j]] = indx;
			pass->info[LEN][pass->links[indx][j]] = pass->info[LEN][indx] + 1;
			ft_printf("ASSIGN LEN %s [%d] -> %s [%d]\n", pass->rooms[indx], pass->info[LEN][indx], pass->rooms[pass->links[indx][j]], pass->info[LEN][pass->links[indx][j]]);
				
			//set_correct_current_index(pass, i, pass->links[indx][j]);
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
		remove_branch(pass, &i);
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
	ft_printf("\n\n------------\nrooms path nbr:	PREV	NEXT	JUMP	LEN\n");
	while (i < pass->total)
	{
		ft_printf("[%s][%d]: [%d] 	[%s]	[%s]	[%s]	[%d]\n",pass->rooms[i], i, pass->info[PATH][i], pass->rooms[pass->info[PREV][i]], pass->rooms[pass->info[NEXT][i]], pass->rooms[pass->info[JUMP][i]], pass->info[LEN][i]);
		++i;
	}
}


static int	len_check(t_room *pass, int indx)
{
	int	i;
	int	start;

	i = pass->info[LEN][pass->info[JUMP][indx]];
	i += pass->info[LEN][indx];
	start = indx;
	ft_printf("room [%s] jump from [%s] front len [%i]   back LEN [%i]\n", pass->rooms[indx], pass->rooms[pass->info[JUMP][indx]], pass->info[LEN][pass->info[JUMP][indx]], pass->info[LEN][indx]);
	while (pass->info[NEXT][indx] != pass->end && pass->info[PATH][indx])
	{
		if (pass->info[JUMP][indx])
			ft_printf("CHECKING LENNNN+++++ start [%s]  current [%s] LEN [%i]    [%i] [%i]\n", pass->rooms[start], pass->rooms[indx], pass->info[LEN][i], pass->info[LEN][pass->info[JUMP][indx]], pass->info[LEN][indx]);
		indx = pass->info[NEXT][indx];
		if (pass->info[JUMP][indx] && pass->info[PATH][pass->info[JUMP][indx]] == 1 \
		 && pass->info[LEN][pass->info[JUMP][indx]] + pass->info[LEN][indx] < i )// && pass->info[JUMP][indx] != start)
		{
			ft_printf("HHHHHHHHHHH\n");
			ft_printf("CHECKING LENNNN+++++ start [%s]  current [%s] LEN [%i]\n", pass->rooms[start], pass->rooms[indx], pass->info[LEN][pass->info[JUMP][indx]]);
			return (FALSE);
		} 
	}
	return (TRUE);
}

// static void	jump_check(t_rooom *pass, int indx)
// {
// 	int	i;

// 	i = 0;
// 	while (pass->links[indx][i] != -1)
// 	{
// 		if (pass->info[JUMP][pass->links[indx][i]] == indx)
// 			return (TRUE);
// 		++i;
// 	}
// 	return (FALSE);
// }

static void	lock_path(t_room *pass, int indx)
{
	int	hold;
	int	for_now;
	int	value;
	int	next;
	int	HELP = 0;

	next = 0;
	hold = 0;
	pass->info[NEXT][indx] = pass->end; 
	while (indx != 0)
	{
		for_now = indx;
		value = pass->info[PATH][indx];
		if (pass->info[PATH][indx] == 1)
			pass->info[PATH][indx] = 4;
		//pass->info[PATH][indx] = 2;
		if (!next)
			indx = pass->info[PREV][indx];
		else
			indx = next;
		next = 0;
		if ((pass->info[PATH][indx] == 3 && value == 1) || (pass->info[PATH][indx] == 1 && value == 3) || pass->info[PATH][indx] == 1)
		{
			hold = 0;
			ft_printf("@ [%s]\n", pass->rooms[indx]);
			ft_printf("room [%s] front len [%i]   back LEN [%i]\n", pass->rooms[indx], pass->info[LEN][pass->info[JUMP][indx]], pass->info[LEN][indx]);
			if (value == 1 && pass->info[PATH][indx] != 1)
			{
				next = pass->info[NEXT][indx];
				//if (pass->info[JUMP][indx])
				//{
					ft_printf("%% [%s]\n", pass->rooms[indx]);
				//	hold = 1;
				//}
			}
			pass->info[NEXT][indx] = for_now;
		}
		else if (pass->info[PATH][indx] == 3 && value == 3 && pass->info[JUMP][indx] && !hold)
		{
			ft_printf("- [%s]\n", pass->rooms[indx]);
			//if (len_check(pass, indx))
			++HELP;
				if (HELP == 20)
					exit (0);
			if ((len_check(pass, indx) && !hold))
			{
				ft_printf("MADE IT\n");
				pass->info[PREV][indx] = pass->info[JUMP][indx];
				pass->info[JUMP][indx] = 0;
				hold = 1;
			}
			else
			{
				ft_printf("MAYBE HERE\n");
				next = pass->info[NEXT][indx];
				pass->info[PREV][indx] = 0;
				//pass->info[NEXT][indx] = 0;

			}
			/*else
			{
				next = pass->info[NEXT][indx];
				pass->info[NEXT][indx] = for_now;
				hold = 0;
			}*/
		}
		else if (pass->info[PATH][indx] == 3 && value == 3 && pass->info[JUMP][indx] && hold)
		{
			next = pass->info[NEXT][indx];
			ft_printf("= [%s]\n", pass->rooms[indx]);
			pass->info[NEXT][indx] = for_now;
			//pass->info[PREV][indx] = pass->info[JUMP][indx];
			hold = 0;
		}
		else if (pass->info[PATH][indx] == 3 && value == 3 && !pass->info[JUMP][indx])
		{
			ft_printf("+ [%s]\n", pass->rooms[indx]);
			next = pass->info[NEXT][indx];
			if (!hold)
			{
				pass->info[PREV][indx] = 0;
				pass->info[NEXT][indx] = 0;
				//pass->info[PATH][indx] = 0;
			}
			else
			{
				pass->info[NEXT][indx] = for_now;
			}
			hold = 0;
		}
	}
}

static void	len_back_front(t_room *pass)
{
	int	i;
	int	j;
	int	prev;

	i = 1;
	j = 0;
	while (pass->links[pass->end][j] != -1)
	{
		if (pass->info[NEXT][pass->links[pass->end][j]] == pass->end)
		{
			prev = pass->links[pass->end][j];
			while (prev != 0)
			{
				pass->info[LEN][prev] = i++;
				prev = pass->info[PREV][prev];
			}
			i = 1;
		}
		++j;
	}
}

static void	delete_non_found_paths(t_room *pass, int indx)
{
	int	i;
	int	prev;

	ft_printf("BEFORE LOCKING________   finished path end room [%s]\n", pass->rooms[indx]);
	print_output(pass);
	len_back_front(pass);
	lock_path(pass, indx);
	//ft_printf("----LOCKED PATH-----\n");
	//print_output(pass);
	i = 0;
	int count;
	while (pass->links[pass->end][i] >= 0)
	{
		count = 1;
		if (pass->info[NEXT][pass->links[pass->end][i]] == pass->end)//(pass->info[PATH][pass->links[pass->end][i]] == 1)
		{
			prev = pass->links[pass->end][i];
			while (prev != 0)
			{
				pass->info[PATH][prev] = 2;
				pass->info[LEN][prev] = count++;
				prev = pass->info[PREV][prev];
			}
		}
		++i;
	}
	i = 0;
	int next = 0;
	while (pass->links[0][i] >= 0)
	{
		count = 1;
		if (pass->info[PATH][pass->links[0][i]] == 2)//(pass->info[PATH][pass->links[pass->end][i]] == 1)
		{
			next = pass->links[0][i];
			while (next != 0)
			{
				pass->info[LEN][next] = count++;
				next = pass->info[NEXT][next];
			}
		}
		++i;
	}
	i = 0;
	while (i < pass->total)
	{
		if (i == 2)
		ft_printf("rooom [%s] PATH [%d] PREV [%s] NEXT [%s]\n", pass->rooms[i], pass->info[PATH][i], pass->rooms[pass->info[PREV][i]], pass->rooms[pass->info[NEXT][i]]);
		if (pass->info[PATH][i] != 2)
		{
			pass->info[PATH][i] = 0;
			pass->info[PREV][i] = 0;
			pass->info[NEXT][i] = 0;
			pass->info[LEN][i] = 0;//should be able to delete
			pass->info[JUMP][i] = 0;
			pass->info[LOCKED][i] = 0;
			pass->info[MOVE][i] = 0;
		}
		else if (pass->info[PATH][i] == 2)
		{
			//pass->info[LEN][i] = 0;//should be able to delete
			pass->info[JUMP][i] = 0;
			pass->info[LOCKED][i] = 0;
			pass->info[MOVE][i] = 0;
		}
		/*if (pass->info[NEXT][i] && pass->info[PATH][i] == 3)
			pass->info[PATH][i] = 2;*/
		/*else if (pass->info[PATH][i] == 3)
		{
			pass->info[PATH][i] = 2;
			pass->info[JUMP][i] = 0;
			pass->info[LOCKED][i] = 0;
			pass->info[MOVE][i] = 0;
		}*/
		pass->info[CURRENT][i] = FALSE;
		++i;
	}
	//exit (0);
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

static void reset_len(t_room *pass, int **len)
{
	int i;

	i = 0;
	while ((*len)[i] != -1)
	{
		(*len)[i] = 0;
		++i;
	}
	i = 0;
	while (i < pass->total)
	{
		if (pass->info[PATH][i] != 2)
			pass->info[LEN][i] = 0;
		++i;
	}
}

static void	bubble_len(t_room *pass, int **len)
{
	int	a;
	int	b;
	int	temp;
	/*int	p;

	p = 0;
	ft_printf("\nNOT SORTED LENNNNNN\n");
	while ((*len)[p] > 0)
	{
		ft_printf("ROOM [%s]   LEN [%i]\n", pass->rooms[(*len)[p]], pass->info[LEN][(*len)[p]]);
		++p;
	}*/

	a = 0;
	while ((*len)[a]  > 0)
	{
		b = a + 1;
		while ((*len)[b] > 0)
		{
			if (pass->info[LEN][(*len)[a]] > pass->info[LEN][(*len)[b]])
			{
				temp = (*len)[a];
				(*len)[a] = (*len)[b];
				(*len)[b] = temp;
			}
			++b;
		}
		++a;
	}
	/*p = 0;
	ft_printf("\nSORTED LENNNNNN\n");
	while ((*len)[p] > 0)
	{
		ft_printf("ROOM [%s]   LEN [%i]\n", pass->rooms[(*len)[p]], pass->info[LEN][(*len)[p]]);
		++p;
	}*/

}
static void	calc_len(t_room *pass, int **len)
{
	int	i;
	int	prev;
	int	count;
	int	j;

	i = 0;
	j = 0;
	while (pass->links[pass->end][i] != -1)
	{
		if (pass->info[PATH][pass->links[pass->end][i]] == 2 && pass->info[NEXT][pass->links[pass->end][i]] == pass->end)
		{
			count = 1;
			prev = pass->links[pass->end][i];
			while (prev != 0)
			{
				++count;
				prev = pass->info[PREV][prev];
			}
			pass->info[LEN][pass->links[pass->end][i]] = count;
			ft_printf("ROOM %s LEN: %d\n", pass->rooms[pass->links[pass->end][i]], pass->info[LEN][pass->links[pass->end][i]]);
			(*len)[j++] = pass->links[pass->end][i];
		}
		++i;
	}
	bubble_len(pass, len);
}

static void	copy_to_path(t_room *pass, t_path **path, int **len)
{
	int	i;
	int	prev;
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
		prev = pass->info[PREV][(*len)[i]];
		create_path(path, pass, nbr++, pass->info[LEN][(*len)[i]]);
		create_index(&(*path)->move_head, path, pass->end);
		create_index(&(*path)->move_head, path, (*len)[i]);
		while (prev > 0)
		{
			create_index(&(*path)->move_head, path, prev);
			prev = pass->info[PREV][prev];
		}
		++i;
	}
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

static int	diff_prev(t_room *pass, int **len, int current)
{
	int count;
	int	i;

	i = 0;
	count = 0;
	while (pass->info[LEN][(*len)[i]] != -1)
	{
		if (pass->info[LEN][(*len)[i]] == current)
			break ;
		count += current - pass->info[LEN][(*len)[i]];
		++i;
	}
	return (count);
}

static int max_ant_calc(t_room *pass, int **len, int current)
{
	int	dif;
	int	i;
	int	prev;
	int	max_ants;

	i = 0;
	dif = 0;
	while (pass->info[LEN][(*len)[i]] != 1 && pass->info[LEN][(*len)[i]] != 0 && pass->info[LEN][(*len)[i]] != current)
		++i;
	prev = i - 1;
	if (prev < 0)
		return (FALSE);
	dif = diff_prev(pass, len, pass->info[LEN][(*len)[prev]]) + ((current - pass->info[LEN][(*len)[prev]]) * i);
	max_ants = dif + i;
	if (pass->ants <= max_ants)
		return (TRUE);
	return (FALSE);
}

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

static int	 calc_min_row(t_room *pass, int **len)
{
	int	path_count;
	int last_len;
	int remain_ants;
	int dif;
	
	remain_ants = pass->ants;
	path_count = 1;
	if ((*len)[path_count] == 0)
		return ((pass->info[LEN][(*len)[path_count - 1]] - 1) + remain_ants);
	while (remain_ants > 0)
	{
		if (pass->info[LEN][(*len)[path_count]] - pass->info[LEN][(*len)[path_count - 1]] != 0)
		{
			ft_printf("value %d - %d != 0\n", pass->info[LEN][(*len)[path_count]], pass->info[LEN][(*len)[path_count - 1]]);

			dif = pass->info[LEN][(*len)[path_count]] - pass->info[LEN][(*len)[path_count - 1]];
			dif *= path_count;
			ft_printf("dif [%d] == (%d - %d) * %d\n", dif, pass->info[LEN][(*len)[path_count]], pass->info[LEN][(*len)[path_count - 1]], path_count);
			remain_ants -= dif;
			ft_printf("dif == %d	remain_ants: %d\n", dif, remain_ants);
			
		}
		last_len = pass->info[LEN][(*len)[path_count]];
		++path_count;
		if ((*len)[path_count] <= 0)
			break ;
	}
	dif = remain_ants / path_count;
	ft_printf("dif == %d	remain_ants: %d / path_count: %d\n", dif, remain_ants, path_count);
	if (remain_ants % path_count != 0)
		dif += 1;
	return ((last_len - 1) + dif);
}

static int	current_len(t_room *pass)
{
	int i;

	i = pass->total - 1;
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
	int	increase;
	int	temp_row;

	i = 0;
	len = NULL;
	create_len(pass->links[0], &len);
	int nbr = 0;
	while (pass->links[0][i] >= 0)
	{
		initialize_path(pass, i++);
	}
	print_output(pass);
	increase = 0;
	while (!current_true(pass))
	{
		i = 0;
		c_len = current_len(pass);
		while (i < c_len)
		{
			if (pass->info[CURRENT][i] != 0)
			{
				ft_printf("room alive %s\n", pass->rooms[pass->info[CURRENT][i]]);
				breadth_first(pass, pass->info[CURRENT][i], i);
				if (pass->info[PATH][pass->end] == 1)
				{
					break ;
				}
			}
			++i;
		}
		if (pass->info[PATH][pass->end] == 1)
		{
			ft_printf("BEFORE LOCK FUCTION ---------------\n");
			print_output(pass);
			pass->info[PATH][0] = 0;
			//if (nbr++ == 0)
			//	exit(0);
			delete_non_found_paths(pass, pass->info[CURRENT][i]);
			ft_printf("----- AFTER CLEAN -----");
			print_output(pass);
			//ft_printf("BREAK\n");
			calc_len(pass, &len);
			temp_row = calc_min_row(pass, &len);
			if (max_ant_calc(pass, &len, pass->info[LEN][pass->info[CURRENT][i]]) == TRUE)
				i = 0;
				//break ;
			if (!pass->final_head)
			{
				pass->min_row = temp_row;
				ft_printf("-------START ROW COUNT: %d-------\n", pass->min_row);
				copy_to_path(pass, path, &len);
			}
			else if (temp_row < pass->min_row)//better_choice(pass, &len, &increase) == TRUE)
			{
				del_path(&pass->final_head);
				*path = NULL;
				copy_to_path(pass, path, &len);
				pass->min_row = temp_row;
				ft_printf("-------NEW ROW COUNT: %d-------\n", pass->min_row);

			}
			else
			{
				ft_printf("-------NO NEW ROW COUNT: %d-------\n", pass->min_row);
				if (increase++ > 5)
					break ;
				ft_printf("increase is now: %d\n", increase);
			}
			nbr++;
			printf_struct(pass);
			// if (nbr == 30)
			// 	break;
			/*
			big-superposition
			1: 5-7 83/83
			2: 7-10& 54/54
			3: 7&8&9 89/89
			4: 5   65/65	oldversion: 66/65
			5 : 12   66/66

			big
			1: 44/54	8 54/54
			2: 11   72/72	old version: 73/72
			3: 13-14 43/45
			4: 13-15 48/67
			5: 17 44/56

			*/
			//ft_printf("\n\n-------PATH IN STRUCT-------\n");
			//printf_struct(pass);
			//ft_printf("\n\n-------PATH IN STRUCT FINISH-------\n");
			
			reset_len(pass, &len);
			i = 0;
			while (pass->links[0][i] >= 0)
			{
				if (pass->info[PATH][pass->links[0][i]] == 0)
					initialize_path(pass, i);
				++i;
			}
			//current_path(pass);
		}
		//print_output(pass);
	}
	print_output(pass);
	//current_path(pass);
	if (unique_paths(pass) == FALSE)
	{
		exit (0);
	}
		//ft_printf("FALSE\n");
	else
		ft_printf("TRUE\n");
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
	printf_struct(pass);
	//exit(0);
}
