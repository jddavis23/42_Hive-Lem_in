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
	pass->info[PATH][pass->links[pass->end][i]] = 1;
	pass->info[CURRENT][i] = pass->links[pass->end][i];
	pass->info[PREV][pass->links[pass->end][i]] = pass->end;
	pass->info[LEN][pass->links[pass->end][i]] = pass->info[LEN][pass->end] + 1;
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

static void	breadth_first(t_room *pass, int indx, int i)
{
	int	j;
	int	k;

	j = 0;
	while (pass->links[indx][j] >= 0)
	{
		if (pass->info[PATH][pass->links[indx][j]] == 0)
		{
			if (pass->links[indx][j] == 0 || pass->links[indx][j] == pass->end)
			{
				pass->info[CURRENT][i] = 0;
				break;
			}
			pass->info[PATH][pass->links[indx][j]] = pass->info[PATH][indx];
			pass->info[PREV][pass->links[indx][j]] = indx;
			pass->info[LEN][pass->links[indx][j]] = pass->info[LEN][indx] + 1;
			pass->info[CURRENT][i] = pass->links[indx][j];
			k = 0;
			while (k < pass->total)
			{
				if (pass->info[CURRENT][k] == 0)
				{
					i = k;
					break ;
				}
				++k;
			}
		}
		++j;
	}
	if (pass->info[CURRENT][i] == indx)
		pass->info[CURRENT][i] = 0;
}
static void	print_output(t_room *pass)
{
	int	i;
	int	nbr;
	int	prev;

	i = 0;
	while (pass->links[0][i] >= 0)
	{
		nbr = pass->info[PATH][pass->links[0][i]];
		if (nbr != 0)
		{
			ft_printf("{green}PATH [%d] LEN[%d]{uncolor}\n", nbr, pass->info[LEN][pass->links[0][i]]);
			prev = pass->info[PREV][pass->links[0][i]];
			ft_printf("%s\n", pass->rooms[pass->links[0][i]]);
			while (prev > 0)
			{
				ft_printf("%s\n", pass->rooms[prev]);
				prev = pass->info[PREV][prev];
			}
		}
		++i;
	}
	i = 0;
	ft_printf("\n\n------------\nrooms path nbr:\n");
	while (i < pass->total)
	{
		ft_printf("[%s]: [%d] \n",pass->rooms[i], pass->info[PATH][i]);
		++i;
	}
}

void	path_finder(t_path **path, t_room *pass, int i)
{
	//int	i;

	i = 0;
	pass->info[LEN][pass->end] = 1;
	while (pass->links[pass->end][i] >= 0)
		initialize_path(pass, i++);
	while (!current_true(pass))
	{
		i = 0;
		while (i < pass->total)
		{
			if (pass->info[CURRENT][i] != 0)
				breadth_first(pass, pass->info[CURRENT][i], i);
			++i;
		}
		ft_printf("\nNEW\n");
		print_output(pass);
	}
	if (path)
		++i;
}
