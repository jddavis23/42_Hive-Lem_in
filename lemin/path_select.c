# include "../includes/lemin.h"

void	initialize_path(t_room *pass, int i)
{
	pass->info[PATH][pass->links[0][i]] = 1;
	pass->info[CURRENT][i] = pass->links[0][i];
	pass->info[PREV][pass->links[0][i]] = 0;
	pass->info[LEN][pass->links[0][i]] = 1;
}


static int	 calc_min_row(t_room *pass, int **len)
{
	int	path_count;
	int last_len;
	int remain_ants;
	int dif;

	remain_ants = pass->ants;
	path_count = 1;
	if ((*len)[path_count] == 0)
		return ((pass->info[LEN][(*len)[path_count - 1]] - 1) + remain_ants);
	while ((*len)[path_count] > 0)
	{
		if (pass->info[LEN][(*len)[path_count]] - pass->info[LEN][(*len)[path_count - 1]] != 0)
		{
			dif = pass->info[LEN][(*len)[path_count]] - pass->info[LEN][(*len)[path_count - 1]];
			dif *= path_count;
			remain_ants -= dif;
		}
		last_len = pass->info[LEN][(*len)[path_count]];
		++path_count;
	}
	dif = remain_ants / path_count;
	if (remain_ants % path_count != 0)
		dif += 1;
	return ((last_len - 1) + dif);
}

void	path_select(t_path **path, t_room *pass, int **len, int *increase)
{
	int	i;
	int	temp_row;

	temp_row = calc_min_row(pass, len);
	if (!pass->final_head)
	{
		copy_to_path(pass, path, len);
		pass->min_row = temp_row;
	}
	else if (temp_row < pass->min_row)
	{
		del_path(&pass->final_head);
		*path = NULL;
		copy_to_path(pass, path, len);
		pass->min_row = temp_row;
	}
	else
		(*increase)++;
	reset_len(pass, len);
	i = -1;
	while (pass->links[0][++i] >= 0)
	{
		if (pass->info[PATH][pass->links[0][i]] == 0)
			initialize_path(pass, i);
	}
}
