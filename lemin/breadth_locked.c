#include "../includes/lemin.h"

/*	update the locked path values	*/

void	update_locked_path(t_room *pass, int indx, int j, int *i)
{
	if (pass->links[indx][j] != pass->info[PREV][indx])
	{
		pass->info[LOCKED][*i] = TRUE;
		pass->info[JUMP][pass->links[indx][j]] = indx;
	}
	pass->info[PATH][pass->links[indx][j]] = 3;
	set_correct_current_index(pass, i, pass->links[indx][j]);
}

/*
**	special case that makes us able to enter a path with the value of 3
**	which means it has already been visited by another path
*/

static void	already_locked_path(t_room *pass, int indx, int temp, int *i)
{
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

/*	logic of routes we can go down	*/

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
			update_locked_path(pass, indx, j, i);
		else if (pass->info[PATH][pass->links[indx][j]] == 0)
			update_non_locked_path(pass, indx, j, i);
		else if (pass->info[PATH][pass->links[indx][j]] == 1 && pass->info[LEN][indx] + 1 <= pass->info[LEN][pass->links[indx][j]] && \
			pass->info[PATH][pass->info[PREV][pass->links[indx][j]]] == 3)
		{
			pass->info[PREV][pass->links[indx][j]] = indx;
			pass->info[LEN][pass->links[indx][j]] = pass->info[LEN][indx] + 1;
			//set_correct_current_index(pass, i, pass->links[indx][j]);
		}
		++j;
	}
	already_locked_path(pass, indx, temp, i);
}

/*	when moving through a locked_path it will check if it contains a 'jump' from a non-locked path to 	*/

void	travel_locked_path(t_room *pass, int indx, int *i)
{
	if (pass->info[JUMP][indx] && pass->info[LOCKED][*i] == TRUE)
	{
		pass->info[LOCKED][*i] = FALSE;
		if (pass->info[PREV][indx] != 0)
		{
			pass->info[PATH][pass->info[PREV][indx]] = pass->info[PATH][indx];
			set_correct_current_index(pass, i, pass->info[PREV][indx]);
		}
	}
	else
		find_new_branches(pass, indx, i);
}
