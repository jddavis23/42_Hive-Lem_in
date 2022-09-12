/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadth_first_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:52:29 by molesen           #+#    #+#             */
/*   Updated: 2022/09/09 18:52:30 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*	reduces the slots we are looking at in CURRENT	*/

int	current_len(t_room *pass)
{
	int	i;

	i = pass->total - 1;
	while (i > 0)
	{
		if (pass->info[CURRENT][i--] != 0)
			break ;
	}
	return (i + 2);
}

/*	moves all of the paths in one round	*/

static void	move_paths(t_room *pass, int *i, int c_len)
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

/*	breadth first initializer with the logic of the first algorithm	*/

static void	breadth_first_init(t_room *pass, int *i, int first)
{
	int	c_len;

	c_len = current_len(pass);
	if (first == TRUE)
		move_paths(pass, i, c_len);
	else
	{
		if (!on_lock_path(pass, i, c_len))
			move_paths(pass, i, c_len);
	}
}

/*
**	makes sure all variables has been set to zero before running
**	the second algorithm
*/

static void	clean_everything(t_room *pass)
{
	int	i;

	i = 0;
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

/*	first algorithm initializer	*/

int	first_algorithm(t_path **path, t_room *pass, int **len, int first)
{
	int	increase;
	int	i;

	increase = 0;
	while (!current_true(pass))
	{
		i = 0;
		breadth_first_init(pass, &i, first);
		if (pass->info[PATH][pass->end] == 1)
		{
			pass->info[PATH][pass->end] = 0;
			lock_path_init(pass, pass->info[CURRENT][i]);
			calc_len(pass, len);
			if (path_select(path, pass, len, &increase) == ERROR)
				return (free_len(len));
			if (increase > 10)
				break ;
		}
	}
	clean_everything(pass);
	initialize_path(pass);
	return (1);
}
