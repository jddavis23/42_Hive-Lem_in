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
//TRY SOMETHIGN NEW
static int	on_lock_path(t_room *pass, int *i, int c_len)
{
	int	j;

	j = 0;
	while (j < c_len)
	{
		if (pass->info[PATH][pass->info[CURRENT][j]] >= 2)
		{
			while (*i < c_len)
			{
				if (pass->info[CURRENT][*i] != 0 && \
					pass->info[PATH][pass->info[CURRENT][*i]] >= 2)
					breadth_first(pass, pass->info[CURRENT][*i], *i);
				++(*i);
			}
			return (TRUE);
		}
		++j;
	}
	return (FALSE);
}


/*	breadth first initializer with the logic of the first algorithm	*/

static void	breadth_first_init(t_room *pass, int *i, int first)
{
	int	c_len;

	c_len = current_len(pass);
	if (first == TRUE)
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
	else
	{
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
			ft_printf("waiting to lock path\n");
			lock_path_init(pass, pass->info[CURRENT][i]);
			ft_printf("LOCKED lock path\n");
			calc_len(pass, len);
			if (path_select(path, pass, len, &increase) == ERROR)
				return (free_len(len));
			if (increase > 10)
				break ;
		}
	}
	return (1);
}
