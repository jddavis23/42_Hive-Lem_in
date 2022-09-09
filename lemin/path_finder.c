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

int	free_len(int **len)
{
	free(*len);
	return (ERROR);
}

static int	start_connect_end(t_path **path, t_room *pass, int **len)
{
	if (create_path(path, pass, 1, 1) == ERROR)
		return (free_len(len));
	if (create_index(&(*path)->move_head, path, pass->end) == ERROR)
		return (free_len(len));
	free(*len);
	return (1);
}

/*	checks if there are anymore alive paths	*/

int	current_true(t_room *pass)
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
		ft_printf("[%s][%d]: [%d] 	[%s]	[%s]	[%s]	[%d]\n",pass->rooms[i], i, pass->info[PATH][i], pass->rooms[pass->info[PREV][i]], pass->rooms[pass->info[NEXT][i]], pass->rooms[pass->info[JUMP][i]], pass->info[LEN][i]);
		++i;
	}
}

/*	makes sure all variables has been set to zero before running the second algorithm	*/

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
	int	*len;
	int	increase;

	len = NULL;
	if (create_len(pass->links[0], &len) == ERROR)
	{
		del_path(&pass->final_head);
		return (ERROR);
	}
	initialize_path(pass);
	increase = 0;
	if (pass->info[PATH][pass->end] == 1)
	{
		if (start_connect_end(path, pass, &len) == ERROR)
			return (ERROR);
		return (1);
	}
	if (first_algorithm(path, pass, &len) == ERROR)
		return (ERROR);
	clean_everything(pass);
	initialize_path(pass);
	if (second_algorithm(path, pass, &len, 0) == ERROR)
		return (ERROR);
	return (1);
}
