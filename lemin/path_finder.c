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
			return (FALSE);
		++i;
	}
	return (TRUE);
}

// static void	set_correct_current_index(t_room *pass, int *i, int new_indx)
// {
// 	int	j;

// 	j = 0;
// 	pass->info[CURRENT][*i] = new_indx;
// 	while (j < pass->total)
// 	{
// 		if (pass->info[CURRENT][j] == 0)
// 		{
// 			*i = j;
// 			break ;
// 		}
// 		++j;
// 	}
// }

// static void	print_output(t_room *pass)
// {
// 	int	i;
// 	int	nbr;
// 	int	prev;
// 	int new;
// 	int start;

// 	new = 0;
// 	i = 0;
// 	start = pass->end;
// 	while (pass->links[start][i] >= 0)
// 	{
// 		nbr = pass->info[PATH][pass->links[start][i]];
// 		if (nbr != 0)
// 		{
// 			ft_printf("{green}PATH [%d] {uncolor}\n", new);
// 			prev = pass->info[PREV][pass->links[start][i]];
// 			ft_printf("%s\n", pass->rooms[pass->end]);
// 			ft_printf("%s\n", pass->rooms[pass->links[start][i]]);
// 			while (prev > 0)
// 			{
// 				ft_printf("%s\n", pass->rooms[prev]);
// 				prev = pass->info[PREV][prev];
// 			}
// 			new++;
// 		}
// 		++i;
// 	}
// 	i = 0;
// 	ft_printf("\n\n------------\nrooms path nbr:	PREV	NEXT	JUMP	LEN\n");
// 	while (i < pass->total)
// 	{
// 		ft_printf("[%s][%d]: [%d] 	[%s]	[%s]	[%s]	[%d]\n",pass->rooms[i], i, pass->info[PATH][i], pass->rooms[pass->info[PREV][i]], pass->rooms[pass->info[NEXT][i]], pass->rooms[pass->info[JUMP][i]], pass->info[LEN][i]);
// 		++i;
// 	}
//}

static int	unique_paths(t_room *pass)
{
	int	current;
	int	compare;
	int	i;
	int	j;

	current = 0;
	while (pass->links[pass->end][current] != -1)
	{
		if (pass->info[NEXT][pass->links[pass->end][current]] == pass->end)
		{
			compare = current + 1;
			while (pass->links[pass->end][compare] != -1)
			{
				if (pass->info[NEXT][pass->links[pass->end][compare]] == pass->end)
				{
					//ft_printf("          PATH [%i]     \n", current);
					i = pass->links[pass->end][current];
					while (i != 0)
					{
						//ft_printf("current room [%s]\n", pass->rooms[i]);
						j = pass->links[pass->end][compare];
						while (j != 0)
						{
							//ft_printf("compare [%s]\n", pass->rooms[j]);
							if (i == j)
								return (FALSE);
							j = pass->info[PREV][j];
						}
						i = pass->info[PREV][i];
					}
				}
				++compare;
			}
		}
		++current;
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
			//ft_printf("ROOM %s LEN: %d\n", pass->rooms[pass->links[pass->end][i]], pass->info[LEN][pass->links[pass->end][i]]);
			(*len)[j++] = pass->links[pass->end][i];
		}
		++i;
	}
	bubble_len(pass, len);
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
	while ((*len)[path_count] > 0)
	{
		if (pass->info[LEN][(*len)[path_count]] - pass->info[LEN][(*len)[path_count - 1]] != 0)
		{
			dif = pass->info[LEN][(*len)[path_count]] - pass->info[LEN][(*len)[path_count - 1]];
			dif *= path_count;
			remain_ants -= dif;
		}
		last_len = pass->info[LEN][(*len)[path_count]];
		++path_count;
	}
	dif = remain_ants / path_count;
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
	while (pass->links[0][i] >= 0)
		initialize_path(pass, i++);
	increase = 0;
	while (!current_true(pass))
	{
		i = 0;
		c_len = current_len(pass);
		while (i < c_len)
		{
			if (pass->info[CURRENT][i] != 0)
			{
				breadth_first(pass, pass->info[CURRENT][i], i);
				if (pass->info[PATH][pass->end] == 1)
					break ;
			}
			++i;
		}
		if (pass->info[PATH][pass->end] == 1)
		{
			pass->info[PATH][0] = 0;
			delete_non_found_paths(pass, pass->info[CURRENT][i]);
			calc_len(pass, &len);
			temp_row = calc_min_row(pass, &len);
			if (!pass->final_head)
			{
				copy_to_path(pass, path, &len);
				pass->min_row = temp_row;
			}
			else if (temp_row < pass->min_row)
			{
				del_path(&pass->final_head);
				*path = NULL;
				copy_to_path(pass, path, &len);
				pass->min_row = temp_row;
			}
			else
			{
				if (increase++ > 5)
					break ;
			}
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
		}
	}
	//print_output(pass);
	//pass->info[PREV][55] = 39;
	if (unique_paths(pass) == FALSE)
	{
		//ft_printf("FAILED\n");
		exit (0);
	}
	// ft_printf("{green}PRINT PRINT{uncolor}\n");
	// i = 0;
	// while (pass->links[0][i] != -1)
	// {
	// 	if (pass->info[PATH][pass->links[0][i]] == 2)
	// 	{
	// 		ft_printf("rooms: %s\n", pass->rooms[pass->links[0][i]]);
	// 		int o = pass->info[PREV][pass->links[0][i]];
	// 		while (o > 0)
	// 		{
	// 			ft_printf("prev: %s\n", pass->rooms[o]);
	// 			o = pass->info[PREV][o];
	// 		}
	// 		ft_printf("\n");
	// 	}
	// 	++i;
	// }
	// printf_struct(pass);
	//exit(0);
}
