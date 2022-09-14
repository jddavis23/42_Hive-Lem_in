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

#include "../includes/lemin.h"

/*	special case where start is connected to the end	*/

static int	end_only(t_path **path, t_room *pass, int **len)
{
	if (create_path(path, pass, 1, 1) == ERROR)
		return (free_len(len));
	if (create_index(&(*path)->move_head, path, pass->end) == ERROR)
		return (free_len(len));
	free(*len);
	return (1);
}

/*	breadth first initializer with the logic of the first algorithm	*/

static void	move_only_non_locked(t_room *pass, int *i)
{
	int	c_len;

	c_len = current_len(pass);
	while (*i < c_len)
	{
		if (pass->info[CURRENT][*i] != 0)
		{
			if (pass->info[PATH][pass->info[CURRENT][*i]] < 2)
			{
				breadth_first(pass, pass->info[CURRENT][*i], *i);
				if (pass->info[PATH][pass->end] == 1)
					return ;
			}
			else
				pass->info[CURRENT][*i] = 0;
		}
		++(*i);
	}
}

/*	logic of moving all of the paths at the same time	*/

static void	move_paths_all(t_room *pass, int *i)
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

/*	logic of moving only the locked paths if there are any	*/

static void	move_locked_alone(t_room *pass, int *i)
{
	int	c_len;

	c_len = current_len(pass);
	if (!on_lock_path(pass, i, c_len))
	{
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
	if (pass->info[PATH][pass->end] == 1 && end_only(path, pass, &len) == ERROR)
		return (ERROR);
	else if (!pass->info[PATH][pass->end])
	{
		if (first_algorithm(path, pass, &len, &move_paths_all) == ERROR)
			return (ERROR);
		if (first_algorithm(path, pass, &len, &move_locked_alone) == ERROR)
			return (ERROR);
		if (first_algorithm(path, pass, &len, &move_only_non_locked) == ERROR)
			return (ERROR);
		if (second_algorithm(path, pass, &len, 0) == ERROR)
			return (ERROR);
	}
	return (1);
}
