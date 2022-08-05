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
	pass->info[PATH][pass->links[pass->end][i]] = 1;
	pass->info[CURRENT][i] = pass->links[pass->end][i];
	pass->info[PREV][pass->links[pass->end][i]] = pass->end;
	pass->info[LEN][pass->links[pass->end][i]] = pass->info[LEN][pass->end] + 1;
}

static int	current_true(t_room *pass)
{
	int i;

	i = 0;
	while (i < pass->total)
	{
		if (pass->info[CURRENT][i] != 0)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

static int	other_connections(t_room *pass, int indx)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (pass->links[indx][i] != -1)
	{
		if (pass->info[PREV][pass->links[indx][i]] == indx)
			++count;
		++i;
	}
	if (count > 1)
		return (TRUE);
	return (FALSE);
}

static void	breadth_first(t_room *pass, int indx, int i, int found)
{
	int	j;
	int	k;
	//static int	found_count = 0;

	j = 0;
	while (pass->links[indx][j] >= 0)
	{
		if (pass->links[indx][j] == 0)// && found_count == found)
		{
			pass->info[PATH][0] = 1;
			//found_count = 0;
			return ;
			found = 0;
		}
		// else if (pass->links[indx][j] == 0 && found_count < found)
		// {
		// 	++found_count;
		// 	pass->info[CURRENT][i] = 0;
		// 	return ;
		// }
		++j;
	}
	j = 0;
	while (pass->links[indx][j] >= 0)
	{
		if (pass->info[PATH][pass->links[indx][j]] == 0 && pass->info[PATH][pass->links[indx][j]] != 2)
		{
			if (pass->links[indx][j] == pass->end)
				pass->info[CURRENT][i] = 0;
			else
			{
				pass->info[PATH][pass->links[indx][j]] = pass->info[PATH][indx];
				pass->info[PREV][pass->links[indx][j]] = indx;
				pass->info[LEN][pass->links[indx][j]] = pass->info[LEN][indx] + 1;
				pass->info[CURRENT][i] = pass->links[indx][j];
				k = 0;
				while (k < pass->total)
				{
					if (pass->info[CURRENT][k] == 0)
					{
						i = k;
						break ;
					}
					++k;
				}
			}
		}
		else if (pass->info[LEN][pass->info[PREV][pass->links[indx][j]]] == pass->info[LEN][indx])
		{
			if (other_connections(pass, pass->info[PREV][pass->links[indx][j]]) == TRUE)
				pass->info[PREV][pass->links[indx][j]] = indx;
		}
		++j;
	}
	if (pass->info[CURRENT][i] == indx)
		pass->info[CURRENT][i] = 0;
}

static void	lock_path(t_room *pass, int indx)
{
	int	i;
	int prev;

	i = 0;
	while (pass->links[0][i] >= 0)
	{
		if (pass->links[0][i] == indx)
		{
			prev = pass->info[PREV][pass->links[0][i]];
			pass->info[PATH][pass->links[0][i]] += 1;
			while (prev > 0 && prev != pass->end)
			{
				pass->info[PATH][prev]++;
				prev = pass->info[PREV][prev];
			}
			break ;
		}
		++i;
	}
}

static void	delete_non_found_paths(t_room *pass, int indx)
{
	int	i;

	lock_path(pass, indx);
	i = 0;
	while (i < pass->total)
	{
		if (pass->info[PATH][i] == 1)
			pass->info[PATH][i] = 0;
		pass->info[CURRENT][i] = FALSE;
		++i;
	}
}

static void	print_output(t_room *pass)
{
	int	i;
	int	nbr;
	int	prev;
	int new;

	new = 0;
	i = 0;
	while (pass->links[0][i] >= 0)
	{
		nbr = pass->info[PATH][pass->links[0][i]];
		if (nbr != 0)
		{
			ft_printf("{green}PATH [%d] LEN[%d]{uncolor}\n", new, pass->info[LEN][pass->links[0][i]]);
			prev = pass->info[PREV][pass->links[0][i]];
			ft_printf("%s\n", pass->rooms[pass->links[0][i]]);
			while (prev > 0)
			{
				ft_printf("%s\n", pass->rooms[prev]);
				prev = pass->info[PREV][prev];
			}
			new++;
		}
		++i;
	}
	// i = 0;
	// ft_printf("\n\n------------\nrooms path nbr:\n");
	// while (i < pass->total)
	// {
	// 	ft_printf("[%s]: [%d] \n",pass->rooms[i], pass->info[PATH][i]);
	// 	++i;
	// }
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

static int	all_zero(t_room *pass)
{
	int	i;

	i = 0;
	while (pass->links[0][i] != -1)
	{
		if (pass->info[PATH][pass->links[0][i]] != 0)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

static void	copy_to_path(t_room *pass, t_path **path)
{
	int	i;
	int	prev;
	int	nbr;
	int shortest;

	nbr = 1;
	while (all_zero(pass) == FALSE)
	{
		i = 0;
		shortest = -1;
		while (pass->links[0][i] != -1)
		{
			if (pass->info[PATH][pass->links[0][i]] == 2)
			{
				if (pass->info[LEN][shortest] >= pass->info[LEN][pass->links[0][i]] || shortest == -1)
				{
					shortest = pass->links[0][i];
				}
			}
			++i;
		}
		i = 0;
		while (pass->links[0][i] != -1)
		{
			if (pass->links[0][i] == shortest)
			{
				prev = pass->info[PREV][pass->links[0][i]];
				create_path(path, pass, nbr, pass->info[LEN][pass->links[0][i]]);
				create_index(&(*path)->move_head, path, pass->links[0][i]);
				while (prev > 0)
				{
					create_index(&(*path)->move_head, path, prev);
					prev = pass->info[PREV][prev];
				}
				pass->info[PATH][pass->links[0][i]] = 0;
				break ;
			}
			++i;
		}
		nbr++;
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

static void	move_to_right(int **len, int begin)
{
	int	i;

	i = begin;
	while ((*len)[i] != -1 && (*len)[i] != 0)
		++i;
	while (i > begin)
	{
		(*len)[i] = (*len)[i - 1];
		--i;
	}
}

static void	add_len(int nbr, int **len)
{
	int	i;

	i = 0;
	while ((*len)[i] != -1 && (*len)[i] != 0)
	{
		if ((*len)[i] > nbr)
		{
			move_to_right(len, i);
			break ;
		}
		++i;
	}
	(*len)[i] = nbr;
}

static int	diff_prev(int **len, int current)
{
	int count;
	int	i;

	i = 0;
	count = 0;
	while ((*len)[i] != -1)
	{
		if ((*len)[i] == current)
			break ;
		count += current - (*len)[i];
		++i;
	}
	return (count);
}

static int max_ant_calc(int ants, int **len, int current)
{
	int	dif;
	int	i;
	int	prev;
	int	max_ants;

	i = 0;
	dif = 0;
	while ((*len)[i] != 1 && (*len)[i] != 0 && (*len)[i] != current)
		++i;
	prev = i - 1;
	if (prev < 0)
		return (FALSE);
	dif = diff_prev(len, (*len)[prev]) + ((current - (*len)[prev]) * i);
	max_ants = dif + i;
	if (ants <= max_ants)
		return (TRUE);
	return (FALSE);
}

void	path_finder(t_path **path, t_room *pass, int found, int **len)
{
	int	i;

	i = 0;
	pass->info[LEN][pass->end] = 1;
	while (pass->links[pass->end][i] >= 0)
		initialize_path(pass, i++);
	while (!current_true(pass))
	{
		i = 0;
		while (i < pass->total)
		{
			if (pass->info[CURRENT][i] != 0)
			{
				breadth_first(pass, pass->info[CURRENT][i], i, found);
				if (pass->info[PATH][0] == 1)
				{
					break ;
				}
			}
			++i;
		}
		if (pass->info[PATH][0] == 1)
		{
			pass->info[PATH][0] = 0;
			add_len(pass->info[LEN][pass->info[CURRENT][i]], len);
			if (max_ant_calc(pass->ants, len, pass->info[LEN][pass->info[CURRENT][i]]) == TRUE)
				break ;
			delete_non_found_paths(pass, pass->info[CURRENT][i]);
			i = 0;
			while (pass->links[pass->end][i] >= 0)
			{
				if (pass->info[PATH][pass->links[pass->end][i]] == 0)
					initialize_path(pass, i);
				++i;
			}
			//found = 0;
		}
		// print_output(pass);
	}
	print_output(pass);
	if (unique_paths(pass) == FALSE)
		ft_printf("FALSE\n");
	else
		ft_printf("TRUE\n");
	delete_non_found_paths(pass, 0);
	if (!pass->final_head)// && new_path_better(pass, path) == FALSE)
	{
		copy_to_path(pass, path);
	}
	// else
	// {
	// 	del_path(&pass->final_head);
	// 	copy_to_path(pass, path);
	// }
	ft_printf("Here\n");
	printf_struct(pass);
	//exit(0);
}
