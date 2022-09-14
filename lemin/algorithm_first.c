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

int	first_algorithm(t_path **path, t_room *pass, int **len, void (*f)(t_room *, int *))
{
	int	error;
	int	increase;
	int	i;

	increase = 0;
	error = FALSE;
	while (!current_true(pass))
	{
		i = 0;
		f(pass, &i);
		if (pass->info[PATH][pass->end] == 1)
		{
			pass->info[PATH][pass->end] = 0;
			lock_path_init(pass, pass->info[CURRENT][i], &error);
			if (error == TRUE)
				break ;
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
