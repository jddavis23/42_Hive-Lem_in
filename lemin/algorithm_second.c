/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadth_second_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:52:36 by molesen           #+#    #+#             */
/*   Updated: 2022/09/09 18:52:37 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

/*	checks if CURRENT has any paths that are moving on the locked path	*/

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
				if (pass->info[CURRENT][*i] != 0 && pass->info[PATH][pass->info[CURRENT][*i]] >= 2)
					breadth_first(pass, pass->info[CURRENT][*i], *i);
				++(*i);
			}
			return (TRUE);
		}
		++j;
	}
	return (FALSE);
}

/*	breadth first initializer with the base logic of the second algorithm	*/

static void	breadth_second_init(t_room *pass, int *i, int *end)
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
				{
					pass->info[CURRENT][*i] = 0;
					*end = 1;
				}
			}
			++(*i);
		}
	}
}

/*
**	runs breadth first through the whole thing and then selects with this
**	function the shortest of all of the paths
*/

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

/*	second algorithm initializer	*/

int	second_algorithm(t_path **path, t_room *pass, int **len, int i)
{
	int	increase;

	increase = 0;
	while (!current_true(pass))
	{
		i = 0;
		breadth_second_init(pass, &i, &pass->info[PATH][pass->end]);
		if (pass->info[PATH][pass->end] == 1 && current_true(pass))
		{
			i = choose_shortest_path(pass);
			pass->info[PATH][pass->end] = 0;
			lock_path_init(pass, i);
			calc_len(pass, len);
			if (path_select(path, pass, len, &increase) == ERROR)
				return (free_len(len));
			if (increase > 20)
				break ;
		}
	}
	free(*len);
	return (1);
}
