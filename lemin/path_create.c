/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:46:56 by molesen           #+#    #+#             */
/*   Updated: 2022/07/14 16:53:26 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

static t_index	*ft_indexnew(int index)
{
	t_index	*new;

	new = (t_index *)malloc(sizeof(t_index));
	if (!new)
		return (NULL);
	new->index = index;
	new->next = NULL;
	return (new);
}

void	create_index(t_index **move, t_path *path, int i)
{
	t_index	*new;

	new = NULL;
	if (!(*move))
	{
		*move = ft_indexnew(i);
		path->move_head = *move;
		path->move = *move;
	}
	else
	{
		new = ft_indexnew(i);
		new->next = path->move_head;
		path->move_head = new;
	}
	path->len++;
}

static t_path	*ft_pathnew()
{
	t_path	*new;

	new = (t_path *)malloc(sizeof(t_path));
	if (!new)
		return (NULL);
	new->len = 0;
	new->move = NULL;
	new->next = NULL;
	return (new);
}

void	create_path(t_path **path, t_room *pass)
{
	t_path *new;

	new = *path;
	new = ft_pathnew();
	new->nbr = pass->path_nbr;
	new->found = FALSE;
	pass->path_nbr++;
	if (*path)
	{
		(*path)->next = new;
		*path = (*path)->next;
	}
	else
	{
		*path = new;
		pass->head = *path;
	}
	create_index(&(*path)->move, *path, pass->end);
}
