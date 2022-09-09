# include "../includes/lemin.h"


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
	ft_printf("HERE\n");
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
	ft_printf("HERE\n");
	i = 0;
	while (i < pass->total)
	{
		if (pass->info[PATH][i] != 2)
		{
			pass->info[PATH][i] = 0;
			pass->info[PREV][i] = 0;
			pass->info[NEXT][i] = 0;
			pass->info[LEN][i] = 0;
			pass->info[JUMP][i] = 0;
			pass->info[LOCKED][i] = 0;
			pass->info[MOVE][i] = 0;
		}
		else if (pass->info[PATH][i] == 2)
		{
			pass->info[JUMP][i] = 0;
			pass->info[LOCKED][i] = 0;
			pass->info[MOVE][i] = 0;
		}
		pass->info[CURRENT][i] = FALSE;
		++i;
	}
}
