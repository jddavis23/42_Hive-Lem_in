/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_select.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:25:31 by molesen           #+#    #+#             */
/*   Updated: 2022/09/09 19:25:33 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

void	initialize_path(t_room *pass)
{
	int	i;

	i = 0;
	while (pass->links[0][i] >= 0)
	{
		if (pass->info[PATH][pass->links[0][i]] == 0)
		{
			pass->info[PATH][pass->links[0][i]] = 1;
			pass->info[CURRENT][i] = pass->links[0][i];
			pass->info[PREV][pass->links[0][i]] = 0;
			pass->info[LEN][pass->links[0][i]] = 1;
		}
		++i;
	}
}


static int	calc_min_row(t_room *pass, int **len, int path_count, int remain_ants)
{
	//int	path_count;
	int last_len;
	//int remain_ants;
	int dif;

	//remain_ants = pass->ants;
	//path_count = 1;
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

static void	reset_locked_len(t_room *pass)
{
	int	i;
	int	count;
	int	next;

	i = 0;
	while (pass->links[0][i] >= 0)
	{
		count = 1;
		if (pass->info[PATH][pass->links[0][i]] == 2)
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

int	path_select(t_path **path, t_room *pass, int **len, int *increase)
{
	int	temp_row;

	temp_row = calc_min_row(pass, len, 1, pass->ants);
	if (!pass->final_head)
	{
		if (copy_to_path(pass, path, len) == ERROR)
			return (ERROR);
		pass->min_row = temp_row;
	}
	else if (temp_row < pass->min_row)
	{
		del_path(&pass->final_head);
		*path = NULL;
		if (copy_to_path(pass, path, len) == ERROR)
			return (ERROR);
		pass->min_row = temp_row;
	}
	else
		(*increase)++;
	reset_len(pass, len);
	reset_locked_len(pass);
	initialize_path(pass);
	return (1);
}
