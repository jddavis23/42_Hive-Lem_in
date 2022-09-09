/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadth_first.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:40:09 by molesen           #+#    #+#             */
/*   Updated: 2022/09/01 13:40:10 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

/*	updates current indx	*/

void	set_correct_current_index(t_room *pass, int *i, int new_indx)
{
	int	j;

	j = 0;
	pass->info[CURRENT][*i] = new_indx;
	while (j < pass->total)
	{
		if (pass->info[CURRENT][j] == 0)
		{
			*i = j;
			break ;
		}
		++j;
	}
}

/*	update non-locked path values	*/

void	update_non_locked_path(t_room *pass, int indx, int j, int *i)
{
	if (pass->links[indx][j] == 0)
		remove_branch(pass, i);
	else
	{
		pass->info[PATH][pass->links[indx][j]] = 1;
		pass->info[PREV][pass->links[indx][j]] = indx;
		pass->info[LEN][pass->links[indx][j]] = pass->info[LEN][indx] + 1;
		set_correct_current_index(pass, i, pass->links[indx][j]);
	}
}

/*	updates remaining of path	*/

static void	update_len(t_room *pass, int indx)
{
	int	i;

	i = 0;
	while (pass->links[indx][i] >= 0)
	{
		if (pass->info[PREV][pass->links[indx][i]] == indx)
		{
			pass->info[LEN][pass->links[indx][i]] = pass->info[LEN][indx] + 1;
			update_len(pass, pass->links[indx][i]);
		}
		++i;
	}
}

/*
**	when moving through a non-locked path it will check for valid rooms to move into
**	valid rooms contain the value 0 or 2 in the pass->info[PATH]
*/

static void	travel_non_locked_path(t_room *pass, int indx, int *i)
{
	int	j;

	j = 0;
	while (pass->links[indx][j] >= 0)
	{
		if (pass->info[PATH][pass->links[indx][j]] == 0)
			update_non_locked_path(pass, indx, j, i);
		else if (pass->info[PATH][pass->links[indx][j]] == 2 && \
			pass->info[PATH][pass->info[PREV][pass->links[indx][j]]] >= 2)
			update_locked_path(pass, indx, j, i);
		else if (pass->info[PATH][pass->links[indx][j]] == 1 && \
			pass->info[LEN][indx] + 1 <= pass->info[LEN][pass->links[indx][j]] && \
			pass->links[indx][j] != pass->info[PREV][indx]
		)
		{
			pass->info[PREV][pass->links[indx][j]] = indx;
			pass->info[LEN][pass->links[indx][j]] = pass->info[LEN][indx] + 1;
			update_len(pass, pass->links[indx][j]);
		}
		++j;
	}
}

/*
**	breadth first algorithm
**	contains logic of moving through locked and non-locked paths
*/

void	breadth_first(t_room *pass, int indx, int i)
{
	int	j;

	j = 0;
	if (pass->info[PATH][indx] == 1)
	{
		while (pass->links[indx][j] >= 0)
		{
			if (pass->links[indx][j] == pass->end)
			{
				pass->info[PATH][pass->end] = 1;
				return ;
			}
			++j;
		}
		travel_non_locked_path(pass, indx, &i);
	}
	else if (pass->info[PATH][indx] == 3)
		travel_locked_path(pass, indx, &i);
	if (pass->info[CURRENT][i] == indx)
		remove_branch(pass, &i);
}
