#include "../includes/lemin.h"

static void	path_not_in_use(t_room *pass, int prev)
{
	while (prev != 0 || pass->info[NEXT][prev] != prev)
	{
		pass->info[PATH][prev] = 0;
		pass->info[LEN][prev] = 0;
		pass->info[PREV][prev] = 0;
		pass->info[NEXT][prev] = 0;
		prev = pass->info[PREV][prev];
		if (pass->info[PATH][prev] < 2)
			return ;
	}
}

/*
**	updates the length so the count goes up from end to start of already
**	found paths
*/

static void	len_back_front(t_room *pass)
{
	int	i;
	int	j;
	int	prev;

	i = 1;
	j = 0;
	while (pass->links[pass->end][j] != -1)
	{
		if (pass->info[NEXT][pass->links[pass->end][j]] == pass->end)
		{
			prev = pass->links[pass->end][j];
			while (prev != 0)
			{
				if (pass->info[PATH][prev] < 2)
				{
					path_not_in_use(pass, pass->links[pass->end][j]);
					return ;
				}
				pass->info[LEN][prev] = i++;
				prev = pass->info[PREV][prev];
			}
			i = 1;
		}
		++j;
	}
}

/*
**	sets the values to zero - also called from main when function is
**	first called
*/

void	info_set_to_zero(t_room *pass, int i)
{
	pass->info[PATH][i] = FALSE;
	pass->info[PREV][i] = FALSE;
	pass->info[LEN][i] = FALSE;
	pass->info[NEXT][i] = FALSE;
	pass->info[JUMP][i] = FALSE;
	pass->info[LOCKED][i] = FALSE;
	pass->info[MOVE][i] = FALSE;
	pass->info[CURRENT][i] = FALSE;
}

/*	clears non found paths and set values to 0	*/

static void	clear_non_found_paths(t_room *pass)
{
	int	i;

	i = 0;
	while (i < pass->total)
	{
		if (pass->info[PATH][i] != 2)
			info_set_to_zero(pass, i);
		else if (pass->info[PATH][i] == 2)
		{
			pass->info[JUMP][i] = 0;
			pass->info[LOCKED][i] = 0;
			pass->info[MOVE][i] = 0;
			pass->info[CURRENT][i] = FALSE;
		}
		++i;
	}
}

/*
**	cals nescessary functions to set PREV and NEXT pointing the correct directions
**	follows prev from end to start to set new paths to correct value of 2
*/

void	lock_path_init(t_room *pass, int indx)
{
	int	i;
	int	prev;
	int	error;

	len_back_front(pass);
	error = FALSE;
	lock_path(pass, indx, &error);
	if (error == TRUE)
		return ;
	i = 0;
	while (pass->links[pass->end][i] >= 0)
	{
		if (pass->info[NEXT][pass->links[pass->end][i]] == pass->end)
		{
			prev = pass->links[pass->end][i];
			while (prev != 0)
			{
				pass->info[PATH][prev] = 2;
				prev = pass->info[PREV][prev];
			}
		}
		++i;
	}
	clear_non_found_paths(pass);
}
