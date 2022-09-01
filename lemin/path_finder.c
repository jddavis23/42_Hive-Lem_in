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

static void	breadth_first_init(t_room *pass, int *i)
{
	int	c_len;

	c_len = current_len(pass);
	while (*i < c_len)
	{
		if (pass->info[CURRENT][*i] != 0)
		{
			breadth_first(pass, pass->info[CURRENT][*i], *i);
			if (pass->info[PATH][pass->end] == 1)
				return ;
		}
		++(*i);
	}
}

void	path_finder(t_path **path, t_room *pass)
{
	int	i;
	int	*len;
	int	increase;

	i = 0;
	len = NULL;
	create_len(pass->links[0], &len);
	while (pass->links[0][i] >= 0)
		initialize_path(pass, i++);
	increase = 0;
	while (!current_true(pass))
	{
		i = 0;
		breadth_first_init(pass, &i);
		if (pass->info[PATH][pass->end] == 1)
		{
			pass->info[PATH][0] = 0;
			delete_non_found_paths(pass, pass->info[CURRENT][i]);
			calc_len(pass, &len);
			path_select(path, pass, &len, &increase);
			if (increase > 5)
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
	}
	//print_output(pass);
	//pass->info[PREV][55] = 39;

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
