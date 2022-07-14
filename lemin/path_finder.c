/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 09:38:32 by molesen           #+#    #+#             */
/*   Updated: 2022/07/12 09:38:35 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

static void	copy_struct(t_path **path, t_room *pass, int i)
{
	t_path *new;
	t_path *src;
	t_path *head;

	src = *path;
	src->move = src->move_head;
	while (src->move)
	{
		if (src->move->index == i || src->move->next == NULL)
			break ;
		src->move = src->move->next;
	}
	new = NULL;
	head = NULL;
	copy_path(&new, &src, pass, &head);
	new->move->next = NULL;
	(*path)->next = head;
	*path = (*path)->next;
}

static void	find_path(t_path **path, t_room *pass, int i, int prev_index)
{
	int	j;
	int	len;

	j = 0;
	if (pass->distance[i] <= pass->distance[prev_index] && pass->distance[i] != 0)
	{
		if (prev_index == pass->end)
			create_path(path, pass);
		create_index(&(*path)->move, *path, i, prev_index);
		len = len_array(pass->links[i]);
		while (j < len)
		{
			if (pass->links[i][j] == 0)
			{
				ft_printf("FOUND START!\n");
				(*path)->found = TRUE;
				if ((*path)->len > pass->longest_path)
					pass->longest_path = (*path)->len;
				return ;
			}
			if (pass->distance[pass->links[i][j]] <= pass->distance[i] && pass->distance[pass->links[i][j]] != 0 && pass->links[i][j] != prev_index)
			{
				if ((*path)->found == TRUE)
				{
					copy_struct(path, pass, i);
					(*path)->found = FALSE;
					find_path(&(*path), pass, pass->links[i][j], i);
				}
				else
					find_path(&(*path), pass, pass->links[i][j], i);
			}
			++j;
		}
	}
}

int	path_finder(t_room *pass, int len)
{
	int	i;
	t_path	*path;

	path = NULL;
	pass->path_nbr = 1;
	pass->longest_path = 0;
	i = 0;
	while (i < len)
	{
		if (pass->links[pass->end][i] == 0)
		{
			create_path(&path, pass);
			ft_printf("FOUND START!\n");
			path->found = TRUE;
			if (path->len > pass->longest_path)
				pass->longest_path = path->len;
			break ;
		}
		find_path(&path, pass, pass->links[pass->end][i], pass->end);
		++i;
	}
	if (!path)
	{
		ft_printf("ERROR\n");
		exit(0);
	}
	path = pass->head;
	i = 0;
	ft_printf("\n{green}PATHS:{uncolor} \n");
	while (path)
	{
		path->move = path->move_head;
		ft_printf("path\nnbr: %d	Len: %d	nbr of struct: %d\n", path->nbr, path->len, i);
		while (path->move)
		{
			ft_printf("room: %s\n", pass->rooms[path->move->index]);
	
			path->move = path->move->next;
		}
		++i;
		path = path->next;
	}
	return (0);
}


/*

check leaks and make sure everything is freed

make the function for printing out the final ants movement.

*/