
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
		//pass->info[PATH][indx] = 2;
		if (!next)
			indx = pass->info[PREV][indx];
		else
			indx = next;
		next = 0;
		if ((pass->info[PATH][indx] == 3 && value == 1) || (pass->info[PATH][indx] == 1 && value == 3) || pass->info[PATH][indx] == 1)
		{
			hold = 0;
			if (value == 1 && pass->info[PATH][indx] != 1)
			{
				next = pass->info[NEXT][indx];
				//if (pass->info[JUMP][indx])
				//{
					//ft_printf("%% [%s]\n", pass->rooms[indx]);
				//	hold = 1;
				//}
			}
			pass->info[NEXT][indx] = for_now;
		}
		else if (pass->info[PATH][indx] == 3 && value == 3 && pass->info[JUMP][indx] && !hold)
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
				//pass->info[NEXT][indx] = 0;

			}
			/*else
			{
				next = pass->info[NEXT][indx];
				pass->info[NEXT][indx] = for_now;
				hold = 0;
			}*/
		}
		else if (pass->info[PATH][indx] == 3 && value == 3 && pass->info[JUMP][indx] && hold)
		{
			next = pass->info[NEXT][indx];
			pass->info[NEXT][indx] = for_now;
			//pass->info[PREV][indx] = pass->info[JUMP][indx];
			hold = 0;
		}
		else if (pass->info[PATH][indx] == 3 && value == 3 && !pass->info[JUMP][indx])
		{
			next = pass->info[NEXT][indx];
			if (!hold)
			{
				pass->info[PREV][indx] = 0;
				pass->info[NEXT][indx] = 0;
				//pass->info[PATH][indx] = 0;
			}
			else
			{
				pass->info[NEXT][indx] = for_now;
			}
			hold = 0;
		}
	}
}

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
				pass->info[LEN][prev] = i++;
				prev = pass->info[PREV][prev];
			}
			i = 1;
		}
		++j;
	}
}

void	delete_non_found_paths(t_room *pass, int indx)
{
	int	i;
	int	prev;

	len_back_front(pass);
	lock_path(pass, indx);
	i = 0;
	int count;
	while (pass->links[pass->end][i] >= 0)
	{
		//count = 1;
		if (pass->info[NEXT][pass->links[pass->end][i]] == pass->end)//(pass->info[PATH][pass->links[pass->end][i]] == 1)
		{
			prev = pass->links[pass->end][i];
			while (prev != 0)
			{
				pass->info[PATH][prev] = 2;
				//pass->info[LEN][prev] = count++;
				prev = pass->info[PREV][prev];
			}
		}
		++i;
	}
	i = 0;
	int next = 0;
	while (pass->links[0][i] >= 0)
	{
		count = 1;
		if (pass->info[PATH][pass->links[0][i]] == 2)//(pass->info[PATH][pass->links[pass->end][i]] == 1)
		{
			next = pass->links[0][i];
			while (next != 0)
			{
				pass->info[LEN][next] = count++;
				next = pass->info[NEXT][next];
			}
		}
		++i;
	}
	i = 0;
	while (i < pass->total)
	{
		if (pass->info[PATH][i] != 2)
		{
			pass->info[PATH][i] = 0;
			pass->info[PREV][i] = 0;
			pass->info[NEXT][i] = 0;
			pass->info[LEN][i] = 0;//should be able to delete
			pass->info[JUMP][i] = 0;
			pass->info[LOCKED][i] = 0;
			pass->info[MOVE][i] = 0;
		}
		else if (pass->info[PATH][i] == 2)
		{
			//pass->info[LEN][i] = 0;//should be able to delete
			pass->info[JUMP][i] = 0;
			pass->info[LOCKED][i] = 0;
			pass->info[MOVE][i] = 0;
		}
		/*if (pass->info[NEXT][i] && pass->info[PATH][i] == 3)
			pass->info[PATH][i] = 2;*/
		/*else if (pass->info[PATH][i] == 3)
		{
			pass->info[PATH][i] = 2;
			pass->info[JUMP][i] = 0;
			pass->info[LOCKED][i] = 0;
			pass->info[MOVE][i] = 0;
		}*/
		pass->info[CURRENT][i] = FALSE;
		++i;
	}
	//exit (0);
}
