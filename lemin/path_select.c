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
			if (remain_ants - dif < 0)
				break ;
			else
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

// static void	printf_struct(t_room *pass)
// {
// 	t_path *final;
// 	t_index *temp;
// 	int i;
// 	final = pass->final_head;
// 	i = 0;
// 	ft_printf("\n{green}after sort: finalS:{uncolor} \n");
// 	while (final)
// 	{
// 		temp = final->move_head;
// 		final->move = final->move_head;
// 		ft_printf("\nnbr: %d	Len: %d	nbr of struct: %d\n", final->nbr, final->len, i);
// 		// while (final->move)
// 		// {
// 		// 	ft_printf("room: %s\n", pass->rooms[final->move->index]);
// 		// 	final->move = final->move->next;
// 		// }
// 		final->move_head = temp;
// 		++i;
// 		final = final->next;
// 	}
// }

// static void	printf_struct(t_room *pass)
// {
// 	t_path *final;
// 	t_index *temp;
// 	int i;
// 	final = pass->final_head;
// 	i = 0;
// 	ft_printf("\n{green}STRUCT: PATHS COLLECTED{uncolor} \n");
// 	while (final)
// 	{
// 		temp = final->move_head;
// 		final->move = final->move_head;
// 		ft_printf("PATH [%d] (Len: %d	nbr of struct: %d)\n", final->nbr, final->len, i);
// 		// if (!ft_strcmp(pass->rooms[final->move->index], "Tgz6"))
// 		// {
// 			// ft_printf("	Rooms: ");
// 			// while (final->move)
// 			// {
// 			// 	ft_printf("%s ", pass->rooms[final->move->index]);
// 			// 	final->move = final->move->next;
// 			// 	if (final->move)
// 			// 		ft_printf("-> ");
// 			// 	else
// 			// 		ft_printf("\n\n");
// 			// }
// 		//}
// 		final->move_head = temp;
// 		++i;
// 		final = final->next;
// 	}
// }

static void	reset_locked_len(t_room *pass)
{
	int	i;
	int	count;
	int	next;

	i = 0;
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
}

void	path_select(t_path **path, t_room *pass, int **len, int *increase)
{
	int	i;
	int	temp_row;
	//static int nbr = 0;

	temp_row = calc_min_row(pass, len);
	//ft_printf("temp: %d prevrow: %d\n", temp_row, pass->min_row);
	if (!pass->final_head)
	{
		copy_to_path(pass, path, len);
		pass->min_row = temp_row;
	}
	else if (temp_row < pass->min_row)// || (temp_row <= pass->min_row && ))
	{
		del_path(&pass->final_head);
		*path = NULL;
		copy_to_path(pass, path, len);
		pass->min_row = temp_row;
		// nbr++;
		// ft_printf("\n----------------------\n");
		// // //printf_struct(pass);
		// printf_struct(pass);
		// if (nbr > 12)
		// {
		// 	printf_struct(pass);
		// 	exit(0);
		// 	*increase = 21;
		// }
		// ft_printf("nbr _ %d\n", nbr);
		// ft_printf("NBR %d-----------------\n", nbr);
			
		// printf_struct(pass);
		// nbr++;
		// ft_printf("temp row: %d	pass->min_row: %d\n", temp_row, pass->min_row);
			
		// if (nbr > 8)
		// {
		// 	//ft_printf("temp row: %d	pass->min_row: %d\n", temp_row, pass->min_row);
		// 	exit(0);
		// 	*increase = 50;
		// }
	}
	else
	{
		(*increase)++;
	}
	reset_len(pass, len);
	reset_locked_len(pass);
	i = -1;
	while (pass->links[0][++i] >= 0)
	{
		if (pass->info[PATH][pass->links[0][i]] == 0)
		{
			//ft_printf("Room: %s\n", pass->rooms[pass->links[0][i]]);
			initialize_path(pass, i);
		}
	}
}
