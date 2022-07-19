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
			//free(pass->final_head);
			del_path(&pass->final_head);
			pass->final_head = cpy_pth(pass->head);
			ft_printf("final: %d, path: %d\n", final_length, (*path)->nbr);
		}
		else if (final_length == (*path)->nbr)
		{
			if (count_moves(pass->final_head) > count_moves(pass->head))
			{
				ft_printf("pass->final_head: %d, head: %d\n", count_moves(pass->final_head), count_moves(pass->head));
	
				del_path(&pass->final_head);
				pass->final_head = cpy_pth(pass->head);
			}
		}
	}
	else
	{
		// int	final_length;
		// t_path *final;
		// int i;
		// ft_printf("path: %d\n", (*path)->nbr);
		pass->final_head = cpy_pth(pass->head);
		// final_length = loop_to_end(pass->final_head);
		// ft_printf("final: %d, path: %d\n", final_length, (*path)->nbr);
	//	final = pass->final_head;
	// i = 0;
	// ft_printf("\n{green}finalS:{uncolor} \n");
	// while (final)
	// {
	// 	final->move = final->move_head;
	// 	ft_printf("final\nnbr: %d	Len: %d	nbr of struct: %d\n", final->nbr, final->len, i);
	// 	while (final->move)
	// 	{
	// 		ft_printf("room: %s\n", pass->rooms[final->move->index]);
	
	// 		final->move = final->move->next;
	// 	}
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
		create_index(&(*path)->move, *path, i);
		pass->used[i] = TRUE;
		len = len_array(pass->links[i]);
		j = 0;
		while (j < len)
		{
			if (pass->links[i][j] == 0)
			{
				ft_printf("FOUND START!\n");
				pass->head->found = TRUE;
				initialize_path_finder(path, pass);
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

void	initialize_path_finder(t_path **path, t_room *pass)
{
	int	i;

	i = 0;
	while (i < pass->len)
	{
		if (pass->links[pass->end][i] == 0)
		{
			create_path(path, pass);
			pass->head->found = TRUE;
			ft_printf("FOUND START!\n");
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
	ft_printf("finish struct!\n");
	if (pass->head && pass->head->found == TRUE)
	{
	// 	int	temp_length;
	// 	t_path *temp;
	// 	int i;
	// 	temp_length = loop_to_end(pass->head);
	// 	temp = pass->head;
	// 	i = 0;
	// 	ft_printf("\n{cyan}tempS:{uncolor} \n");
	// 	while (temp)
	// 	{
	// 		ft_printf("temp\nnbr: %d	Len: %d	nbr of struct: %d\n", temp->nbr, temp->len, i);
	// 		temp->move = temp->move_head;
	// 		while (temp->move)
	// 		{
	// 			ft_printf("room: %s\n", pass->rooms[temp->move->index]);
	// 			temp->move = temp->move->next;
	// 		}
	// 		++i;
	// 		temp = temp->next;
	// 	}
		compare_and_copy(path, pass);
		pass->head->found = FALSE;
	}
}
