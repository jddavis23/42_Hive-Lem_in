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

static void	set_correct_current_index(t_room *pass, int *i, int new_indx)
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

static void	remove_branch(t_room *pass, int *i)
{
	pass->info[CURRENT][*i] = 0;
	pass->info[LOCKED][*i] = 0;
	pass->info[MOVE][*i] = 0;
}

static void	find_new_branches(t_room *pass, int indx, int *i)
{
	int	j;
	int	temp;

	j = 0;
	temp = *i;
	while (pass->links[indx][j] >= 0)
	{
		if (pass->info[PATH][pass->links[indx][j]] == 2 && \
			pass->info[PATH][pass->info[PREV][pass->links[indx][j]]] >= 2)
		{
			if (pass->links[indx][j] != pass->info[PREV][indx])
			{
				pass->info[LOCKED][*i] = TRUE;
				pass->info[JUMP][pass->links[indx][j]] = indx;
			}
			pass->info[PATH][pass->links[indx][j]] = 3;
			set_correct_current_index(pass, i, pass->links[indx][j]);
		}
		else if (pass->info[PATH][pass->links[indx][j]] == 0)
		{
			if (pass->links[indx][j] == 0)
			{
				remove_branch(pass, i);
			}
			else
			{
				pass->info[PATH][pass->links[indx][j]] = 1;
				pass->info[PREV][pass->links[indx][j]] = indx;
				pass->info[LEN][pass->links[indx][j]] = pass->info[LEN][indx] + 1;
				set_correct_current_index(pass, i, pass->links[indx][j]);
			}
		}
		else if (pass->info[PATH][pass->links[indx][j]] == 1 && pass->info[LEN][indx] < pass->info[LEN][pass->links[indx][j]] && \
			pass->info[PATH][pass->info[PREV][pass->links[indx][j]]] == 3)
		{
			pass->info[PREV][pass->links[indx][j]] = indx;
			pass->info[LEN][pass->links[indx][j]] = pass->info[LEN][indx] + 1;
			set_correct_current_index(pass, i, pass->links[indx][j]);
		}
		++j;
	}
	if (pass->info[PATH][pass->info[PREV][indx]] == 3 && pass->info[MOVE][temp] == FALSE)
	{
		temp = *i;
		set_correct_current_index(pass, i, pass->info[PREV][indx]);
		pass->info[MOVE][temp] = TRUE;
	}
	else if (pass->info[PATH][pass->info[PREV][indx]] == 2)
	{
		pass->info[MOVE][*i] = FALSE;
		pass->info[PATH][pass->info[PREV][indx]] = 3;
		set_correct_current_index(pass, i, pass->info[PREV][indx]);
	}
	else if (pass->info[MOVE][temp] == TRUE)
	{
		pass->info[MOVE][temp] = FALSE;
	}
}

/*	when moving through a locked_path it will check if it contains a 'jump' from a non-locked path to 	*/

static void	travel_locked_path(t_room *pass, int indx, int *i)
{
	if (pass->info[JUMP][indx] && pass->info[LOCKED][*i] == TRUE)
	{
		pass->info[LOCKED][*i] = FALSE;
		ft_printf("here\n");
		if (pass->info[PREV][indx] != 0)
		{
			pass->info[PATH][pass->info[PREV][indx]] = pass->info[PATH][indx];
			set_correct_current_index(pass, i, pass->info[PREV][indx]);
		}
	}
	else
	{
		ft_printf("%s [%d]\n", pass->rooms[indx], pass->info[PATH][indx]);
		
		find_new_branches(pass, indx, i);
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
		{
			if (pass->links[indx][j] == 0)
				remove_branch(pass, i);
			else
			{
				pass->info[PATH][pass->links[indx][j]] = pass->info[PATH][indx];
				pass->info[PREV][pass->links[indx][j]] = indx;
				pass->info[LEN][pass->links[indx][j]] = pass->info[LEN][indx] + 1;
				ft_printf("ASSIGN LEN %s [%d] -> %s [%d]\n", pass->rooms[indx], pass->info[LEN][indx], pass->rooms[pass->links[indx][j]], pass->info[LEN][pass->links[indx][j]]);
				set_correct_current_index(pass, i, pass->links[indx][j]);
			}
		}
		else if (pass->info[PATH][pass->links[indx][j]] == 2 && \
			pass->info[PATH][pass->info[PREV][pass->links[indx][j]]] >= 2)
		{
			pass->info[JUMP][pass->links[indx][j]] = indx;
			pass->info[LOCKED][*i] = TRUE;
			pass->info[PATH][pass->links[indx][j]] = 3;
			set_correct_current_index(pass, i, pass->links[indx][j]);
		}
		else if (pass->info[PATH][pass->links[indx][j]] == 1 && \
			pass->info[LEN][indx] + 1 < pass->info[LEN][pass->links[indx][j]] && \
			pass->links[indx][j] != pass->info[PREV][indx]
		)
		{
			pass->info[PREV][pass->links[indx][j]] = indx;
			pass->info[LEN][pass->links[indx][j]] = pass->info[LEN][indx] + 1;
			//set_correct_current_index(pass, i, pass->links[indx][j]);
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
