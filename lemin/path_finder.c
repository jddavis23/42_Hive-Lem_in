/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_initialize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:31:10 by molesen           #+#    #+#             */
/*   Updated: 2022/07/19 10:31:12 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

static int	count_moves(t_path *path)
{
	int	i;

	i = 0;
	while (path)
	{
		i += path->len;
		path = path->next;
	}
	return (i);
}

static int	loop_to_end(t_path *file)
{
	while (file->next)
	{
		file = file->next;
	}
	return (file->nbr);
}

static void	compare_and_copy(t_path **path, t_room *pass)
{
	int	final_length;

	if (pass->final_head)
	{
		final_length = loop_to_end(pass->final_head);
		if (final_length < (*path)->nbr)
		{
			del_path(&pass->final_head);
			pass->final_head = cpy_pth(pass->head);
			//ft_printf("finish struct!\n");
		}
		else if (final_length == (*path)->nbr)
		{
			if (count_moves(pass->final_head) > count_moves(pass->head))
			{
				del_path(&pass->final_head);
				pass->final_head = cpy_pth(pass->head);
				//ft_printf("finish struct!\n");
			}
		}
		// t_path *final;
		// t_index *temp;
		// int i;
		// final = pass->final_head;
		// i = 0;
		// ft_printf("\n{green}after sort: finalS:{uncolor} \n");
		// while (final)
		// {
		// 	temp = final->move_head;
		// 	final->move = final->move_head;
		// 	ft_printf("final\nnbr: %d	Len: %d	nbr of struct: %d\n", final->nbr, final->len, i);
		// 	while (final->move)
		// 	{
		// 		ft_printf("room: %s\n", pass->rooms[final->move->index]);
		// 		final->move = final->move->next;
		// 	}
		// 	final->move_head = temp;
		// 	++i;
		// 	final = final->next;
		// }
	}
	else
	{
		//ft_printf("finish struct!\n");
		pass->final_head = cpy_pth(pass->head);
		// t_path *final;
		// t_index *temp;
		// int i;
		// final = pass->final_head;
		// i = 0;
		// ft_printf("\n{green}after sort: finalS:{uncolor} \n");
		// while (final)
		// {
		// 	temp = final->move_head;
		// 	final->move = final->move_head;
		// 	ft_printf("final\nnbr: %d	Len: %d	nbr of struct: %d\n", final->nbr, final->len, i);
		// 	while (final->move)
		// 	{
		// 		ft_printf("room: %s\n", pass->rooms[final->move->index]);
		// 		final->move = final->move->next;
		// 	}
		// 	final->move_head = temp;
		// 	++i;
		// 	final = final->next;
		// }
	}
}

static void	find_path(t_path **path, t_room *pass, int i, int prev_index)
{
	int	len;
	int	j;

	if (pass->distance[i] <= pass->distance[prev_index] && pass->distance[i] != 0)
	{
		create_index(&(*path)->move_head, *path, i);
		pass->used[i] = TRUE;
		len = len_array(pass->links[i]);
		j = 0;
		while (j < len)
		{
			if (pass->links[i][j] == 0)
			{

				//ft_printf("head: %p, move_head: %p, index: %d\n", pass->head, pass->head->move_head, pass->head->move_head->index);
				//ft_printf("FOUND START!\n");
				pass->head->found = TRUE;
				path_finder(path, pass);
				// ft_printf("head: %p, move_head: %p, index: %d\n", pass->head, pass->head->move_head, pass->head->move_head->index);
				
				// ft_printf("head of pointer: %p, move_head: %p	 index: %d\n", pass->head, pass->head->move_head, pass->head->move_head->index);
				// t_path *final;
				// t_index *temp;
				// int i;
				// final = pass->head;
				// i = 0;
				// ft_printf("\n{green}after STTART FOUND: finalS:{uncolor} \n");
				// while (final)
				// {
				// 	temp = final->move_head;
				// 	final->move = final->move_head;
				// 	ft_printf("final\nnbr: %d	Len: %d	nbr of struct: %d\n", final->nbr, final->len, i);
				// 	while (final->move)
				// 	{
				// 		ft_printf("room: %s\n", pass->rooms[final->move->index]);
				// 		final->move = final->move->next;
				// 	}
				// 	final->move_head = temp;
				// 	++i;
				// 	final = final->next;
				// }
			}
			if (pass->distance[pass->links[i][j]] <= pass->distance[i] && pass->distance[pass->links[i][j]] != 0 && pass->links[i][j] != prev_index && pass->used[pass->links[i][j]] == FALSE)
			{
				find_path(&(*path), pass, pass->links[i][j], i);
				pass->used[pass->links[i][j]] = FALSE;
				del_first_index(*path);
			}
			j++;
		}
		pass->used[i] = FALSE;
	}
}

void	path_finder(t_path **path, t_room *pass)
{
	int	i;
	static int count = 0;

	i = 0;
	while (i < pass->len)
	{
		// temp solution to the constant looping problem
		if (count > 15 || pass->final_head)
		{
			return ;
		}
		if (pass->links[pass->end][i] == 0)
		{
			create_path(path, pass);
			pass->head->found = TRUE;
			//ft_printf("FOUND START!\n");
			break ;
		}
		if (pass->used[pass->links[pass->end][i]] == FALSE && pass->distance[i] <= pass->distance[pass->end])
		{
			create_path(path, pass);
			find_path(&(*path), pass, pass->links[pass->end][i], pass->end);
			del_last_path(path, pass);
		}
		++i;
	}
	if (pass->head && pass->head->found == TRUE)
	{
		compare_and_copy(path, pass);
		pass->head->found = FALSE;
		count++;
	}
}
