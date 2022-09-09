
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
		if (pass->info[PATH][indx] == 2)
			return (TRUE);
		if (pass->info[JUMP][indx] && pass->info[PATH][pass->info[JUMP][indx]] == 1 \
		 && pass->info[LEN][pass->info[JUMP][indx]] + pass->info[LEN][indx] < i )// && pass->info[JUMP][indx] != start)
		{
			return (FALSE);
		}
	}
	return (TRUE);
}

void	lock_path(t_room *pass, int indx, int *error)
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
			//ft_printf("Room1: %s[%d]	PATH[%d]	PREV: [%d]	NEXT: [%d]	LEN: [%d]\n", pass->rooms[indx], indx, pass->info[PATH][indx], pass->info[PREV][indx], pass->info[NEXT][indx], pass->info[LEN][indx]);
		
			pass->info[NEXT][indx] = for_now;
			//ft_printf("Room1: %s[%d]	PATH[%d]	PREV: [%d]	NEXT: [%d]	LEN: [%d]\n", pass->rooms[indx], indx, pass->info[PATH][indx], pass->info[PREV][indx], pass->info[NEXT][indx], pass->info[LEN][indx]);
		}
		else if (pass->info[PATH][indx] == 3 && value == 3 && \
			pass->info[JUMP][indx] && !hold)
		{
			//ft_printf("Room2: %s[%d]	PATH[%d]	PREV: [%d]	NEXT: [%d]	LEN: [%d]	JUMP: [%d]\n", pass->rooms[indx], indx, pass->info[PATH][indx], pass->info[PREV][indx], pass->info[NEXT][indx], pass->info[LEN][indx], pass->info[JUMP][indx]);

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
			//ft_printf("Room3: %s[%d]	[%d]	[%d]	[%d]\n", pass->rooms[indx], indx, pass->info[PREV][indx], pass->info[NEXT][indx], pass->info[LEN][indx]);

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
			//ft_printf("Room4: %s[%d]	[%d]	[%d]	[%d]\n", pass->rooms[indx], indx, pass->info[PREV][indx], pass->info[NEXT][indx], pass->info[LEN][indx]);

		}
		//ft_printf("Room2: %s[%d]	PATH[%d]	PREV: [%d]	NEXT: [%d]	LEN: [%d]	JUMP: [%d]\n", pass->rooms[indx], indx, pass->info[PATH][indx], pass->info[PREV][indx], pass->info[NEXT][indx], pass->info[LEN][indx], pass->info[JUMP][indx]);

		if (pass->info[PREV][indx] != 0 && pass->info[NEXT][indx] == pass->info[PREV][indx])
		{
			*error = TRUE;
			return ;
		}
		//else
		//{
		//	ft_printf("Room: %s[%d]	[%d]	[%d]	[%d]\n", pass->rooms[indx], indx, pass->info[PREV][indx], pass->info[NEXT][indx]);
		
		//	return ;
		//}
		//if (indx == 564 && ++nbr > 10)
		//	exit(0);
		//ft_printf("Room!: %s[%d]	PATH[%d]	PREV: [%d]	NEXT: [%d]	LEN: [%d]\n", pass->rooms[indx], indx, pass->info[PATH][indx], pass->info[PREV][indx], pass->info[NEXT][indx], pass->info[LEN][indx]);
	}
}
