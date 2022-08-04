/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:00:01 by jdavis            #+#    #+#             */
/*   Updated: 2022/07/15 13:33:20 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static t_index	*cpy_indx(t_path *file, t_path *new)
{
	t_index *n_index;
	t_index *n_index_head;
	//t_index *temp;

	n_index_head = (t_index *) malloc(sizeof(t_index));
	n_index = n_index_head;
	file->move = file->move_head;
	while (file->move)
	{
		n_index->index = file->move->index;
		//temp = file->move;
		file->move = file->move->next;
		//free(temp);
		if (file->move)
		{
			n_index->next = (t_index *) malloc(sizeof(t_index));
			n_index = n_index->next;
		}
	}
	n_index->next = NULL;
	n_index = n_index_head;
	// should this below be switched to n_index_head?? that way it will always start with the head
	new->move = n_index;
	return (n_index_head);
}

t_path	*cpy_pth(t_path *file)
{
	t_path *n_path;
	t_path *n_path_head;
	//t_path *temp;

	n_path_head = (t_path *) malloc(sizeof(t_path));
	n_path = n_path_head;
	while (file)
	{
		n_path->nbr = file->nbr;
		n_path->len = file->len;
		//n_path->found = file->found;
		n_path->move_head = cpy_indx(file, n_path);
		//temp = file;
		file = file->next;
		//free(temp);
		if (file)
		{
			n_path->next = (t_path *) malloc(sizeof(t_path));
			n_path = n_path->next;
		}
		else
			n_path->next = NULL;
	}
	n_path = n_path_head;
	return (n_path);
}

void del_first_index(t_path *file)
{
	t_index	*temp;

	if (file->move_head)
	{
		file->move = file->move_head;
		temp = file->move;
		if (file->move->next)
		{
			file->move = file->move->next;
			free(temp);
			file->move_head = file->move;
			file->len--;
		}
		else
		{
			free(temp);
			file->move = NULL;
			file->move_head = NULL;
		}
	}
}

// void	free_and_del_path(t_path **path, t_room *pass)
// {
// 	(*path)->move = (*path)->move_head;
// 	while ((*path)->move)
// 		del_first_index(*path);
// 	free(*path);
// 	*path = NULL;
// 	//pass->path_nbr--;
// }

// void del_last_path(t_path **path, t_room *pass)
// {
// 	t_path	*head;
// 	t_path	*prev;

// 	head = pass->head;
// 	if (!head->next)
// 	{
// 		(*path)->move = head->move_head;
// 		free_and_del_path(path, pass);
// 		pass->head = NULL;
// 	}
// 	else
// 	{
// 		while (head)
// 		{
// 			prev = head;
// 			if (!head->next->next)
// 				break ;
// 			head = head->next;
// 		}
// 		*path = head->next;
// 		(*path)->move = (*path)->move_head;
// 		free_and_del_path(path, pass);
// 		prev->next = NULL;
// 		*path = prev;
// 	}
// }
