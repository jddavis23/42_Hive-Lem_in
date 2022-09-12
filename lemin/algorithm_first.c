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
	int i;

	i = pass->total - 1;
	while (i > 0)
	{
		if (pass->info[CURRENT][i--] != 0)
			break; 
	}
	return (i + 2);
}

/*	breadth first initializer with the logic of the first algorithm	*/

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

/*	first algorithm initializer	*/

int	first_algorithm(t_path **path, t_room *pass, int **len)
{
	int	increase;
	int	i;

	increase = 0;
	while (!current_true(pass))
	{
		i = 0;
		breadth_first_init(pass, &i);
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
	return (1);
}
