
# include "../includes/lemin.h"

static int	len_check(t_room *pass, int indx)
{
	int	i;
	int	start;

	i = pass->info[LEN][pass->info[JUMP][indx]];
	i += pass->info[LEN][indx];
	start = indx;
	while (pass->info[NEXT][indx] != pass->end && pass->info[PATH][indx])
	{
		indx = pass->info[NEXT][indx];
		if (pass->info[JUMP][indx] && pass->info[PATH][pass->info[JUMP][indx]] == 1 \
		 && pass->info[LEN][pass->info[JUMP][indx]] + pass->info[LEN][indx] < i )// && pass->info[JUMP][indx] != start)
		{
			return (FALSE);
		} 
	}
	return (TRUE);
}

// static void	jump_check(t_rooom *pass, int indx)
// {
// 	int	i;

// 	i = 0;
// 	while (pass->links[indx][i] != -1)
// 	{
// 		if (pass->info[JUMP][pass->links[indx][i]] == indx)
// 			return (TRUE);
// 		++i;
// 	}
// 	return (FALSE);
// }

static void	lock_path_helper(t_room *pass, int indx, int *next, int for_now)
{

}

static void	lock_path(t_room *pass, int indx)
{
	int	hold;
	int	for_now;
	int	value;
	int	next;

	next = 0;
	hold = 0;
	pass->info[NEXT][indx] = pass->end; 
	while (indx != 0)
	{
		for_now = indx;
		value = pass->info[PATH][indx];
		if (pass->info[PATH][indx] == 1)
			pass->info[PATH][indx] = 4;
		if (!next)
			indx = pass->info[PREV][indx];
		else
			indx = next;
		next = 0;
		if ((pass->info[PATH][indx] == 3 && value == 1) || \
			(pass->info[PATH][indx] == 1 && value == 3) || \
			pass->info[PATH][indx] == 1)
		{
			hold = 0;
			if (value == 1 && pass->info[PATH][indx] != 1)
			{
				next = pass->info[NEXT][indx];
			}
			pass->info[NEXT][indx] = for_now;
		}
		else if (pass->info[PATH][indx] == 3 && value == 3 && \
			pass->info[JUMP][indx] && !hold)
		{
			if ((len_check(pass, indx) && !hold))
			{
				pass->info[PREV][indx] = pass->info[JUMP][indx];
				pass->info[JUMP][indx] = 0;
				hold = 1;
			}
			else
			{
				next = pass->info[NEXT][indx];
				pass->info[PREV][indx] = 0;
			}
		}
		else if (pass->info[PATH][indx] == 3 && value == 3 && \
			pass->info[JUMP][indx] && hold)
		{
			next = pass->info[NEXT][indx];
			pass->info[NEXT][indx] = for_now;
			hold = 0;
		}
		else if (pass->info[PATH][indx] == 3 && value == 3 && \
			!pass->info[JUMP][indx])
		{
			next = pass->info[NEXT][indx];
			if (!hold)
			{
				pass->info[PREV][indx] = 0;
				pass->info[NEXT][indx] = 0;
			}
			else
			{
				pass->info[NEXT][indx] = for_now;
			}
			hold = 0;
		}
		else
			return ;
	}
}
