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

/*	checks if there are anymore alive paths	*/

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

void	print_output(t_room *pass)
{
	int	i;
	//int	nbr;
	//int	prev;
	//int new;
	//int start;

	//new = 0;
	i = 0;
	//start = pass->end;
	// while (pass->links[start][i] >= 0)
	// {
	// 	nbr = pass->info[PATH][pass->links[start][i]];
	// 	if (nbr != 0)
	// 	{
	// 		ft_printf("{green}PATH [%d] {uncolor}\n", new);
	// 		prev = pass->info[PREV][pass->links[start][i]];
	// 		ft_printf("%s\n", pass->rooms[pass->end]);
	// 		ft_printf("%s\n", pass->rooms[pass->links[start][i]]);
	// 		while (prev > 0)
	// 		{
	// 			ft_printf("%s\n", pass->rooms[prev]);
	// 			prev = pass->info[PREV][prev];
	// 		}
	// 		new++;
	// 	}
	// 	++i;
	// }
	i = 0;
	ft_printf("\n\n------------\nrooms path nbr:	PREV	NEXT	JUMP	LEN\n");
	while (i < pass->total)
	{
		if (pass->info[PATH][i] != 0)
			ft_printf("[%s][%d]: [%d] 	[%s]	[%s]	[%s]	[%d]\n",pass->rooms[i], i, pass->info[PATH][i], pass->rooms[pass->info[PREV][i]], pass->rooms[pass->info[NEXT][i]], pass->rooms[pass->info[JUMP][i]], pass->info[LEN][i]);
		++i;
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

/*	reduces the slots we are looking at in CURRENT	*/

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

/*	breadth first initializer	*/

static void	breadth_first_init(t_room *pass, int *i)
{
	int	c_len;

	c_len = current_len(pass);
	while (*i < c_len)
	{
		if (pass->info[CURRENT][*i] != 0)// && pass->info[LEN][pass->info[CURRENT][*i]] == shortest)
		{
			breadth_first(pass, pass->info[CURRENT][*i], *i);
			if (pass->info[PATH][pass->end] == 1)
				return ;
		}
		++(*i);
	}
}

/*	checks if CURRENT has any paths that are moving on the locked path	*/

static int	on_lock_path(t_room *pass, int i, int c_len)
{
	while (i < c_len)
	{
		if (pass->info[PATH][pass->info[CURRENT][i]] >= 2)
			return (TRUE);
		++i;
	}
	return (FALSE);
}

static void	breadth_first_init2(t_room *pass, int *i, int *end)
{
	int	c_len;

	c_len = current_len(pass);
	if (on_lock_path(pass, *i, c_len) == TRUE)
	{
		while (*i < c_len)
		{
			if (pass->info[CURRENT][*i] != 0 && pass->info[PATH][pass->info[CURRENT][*i]] >= 2)
				breadth_first(pass, pass->info[CURRENT][*i], *i);
			++(*i);
		}
	}
	else
	{
		while (*i < c_len)
		{
			if (pass->info[CURRENT][*i] != 0)
			{
				breadth_first(pass, pass->info[CURRENT][*i], *i);
				if (pass->info[PATH][pass->end] == 1)
				{
					pass->info[CURRENT][*i] = 0;
					*end = 1;
				}
			}
			++(*i);
		}
	}
}

static int	choose_shortest_path(t_room *pass)
{
	int	i;
	int	shortest;

	i = 0;
	shortest = 0;
	while (pass->links[pass->end][i] >= 0)
	{
		if (pass->info[PATH][pass->links[pass->end][i]] == 1 && (!shortest || pass->info[LEN][pass->links[pass->end][i]] < pass->info[LEN][shortest]))
			shortest = pass->links[pass->end][i];
		++i;
	}
	return (shortest);
}

static void	clean_everything(t_room *pass)
{
	int i = 0;

	while (i < pass->total)
	{
		pass->info[PATH][i] = FALSE;
		pass->info[PREV][i] = FALSE;
		pass->info[LEN][i] = FALSE;
		pass->info[NEXT][i] = FALSE;
		pass->info[JUMP][i] = FALSE;
		pass->info[LOCKED][i] = FALSE;
		pass->info[MOVE][i] = FALSE;
		pass->info[CURRENT][i++] = FALSE;
	}
}

/*	core logic of calling breadth first and locking the paths	*/

int	path_finder(t_path **path, t_room *pass)
{
	int	i;
	int	*len;
	int	increase;

	i = 0;
	len = NULL;
	if (create_len(pass->links[0], &len) == ERROR)
	{
		del_path(&pass->final_head);
		return (-1);
	}
	while (pass->links[0][i] >= 0)
		initialize_path(pass, i++);
	increase = 0;
	i = 0;
	if (pass->info[PATH][pass->end] == 1)
	{
		if (create_path(path, pass, 1, 1) == -1)
		{
			free(len);
			return (-1);
		}
		if (create_index(&(*path)->move_head, path, pass->end) == -1)
		{
			free(len);
			return (-1);
		}
		free(len);
		return (1);
	}
	i = 0;
	while (!current_true(pass))
	{
		i = 0;
		breadth_first_init(pass, &i);
		if (pass->info[PATH][pass->end] == 1)
		{
			pass->info[PATH][pass->end] = 0;
			lock_path_init(pass, pass->info[CURRENT][i]);
			calc_len(pass, &len);
			if (path_select(path, pass, &len, &increase) == -1)
			{
				free(len);
				return (-1);
			}
			// nbr++;
			// if (nbr > 20)
			// 	exit(0);
			//ft_printf("START OF SEARCH ---\n");
		
			if (increase > 10)
				break ;
		}
	}
	// trying out new algo to see if this method gives a better result
	// finish all paths before choosing which path to go with
	clean_everything(pass);
	i = 0;
	while (pass->links[0][i] >= 0)
		initialize_path(pass, i++);
	i = 0;
	while (!current_true(pass))
	{
		i = 0;
		breadth_first_init2(pass, &i, &pass->info[PATH][pass->end]);
		if (pass->info[PATH][pass->end] == 1 && current_true(pass))
		{
			i = choose_shortest_path(pass);
			//ft_printf("what is choosed %s\n", pass->rooms[i]);
			pass->info[PATH][pass->end] = 0;
			//print_output(pass);
			lock_path_init(pass, i);
			
			ft_printf("HERE\n");
			//print_output(pass);
			calc_len(pass, &len);
			path_select(path, pass, &len, &increase);
			// nbr++;
			// if (nbr > 20)
			// 	exit(0);
			//ft_printf("START OF SEARCH ---\n");
			//print_output(pass);
			if (increase > 20)
				break ;
		}
		// else
		// {
		// 	ft_printf("didn't enter\n");
		// }
		//ft_printf("WHILE BREADTH FIRST\n");
	}
	free(len);
	return (1);
}
