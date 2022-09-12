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

#include "../includes/lemin.h"

/*	creates a new index element	*/

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

/*	creates index element and adds it onto path->move's linked list	*/

int	create_index(t_index **move, t_path **path, int i)
{
	t_index	*new;

	new = NULL;
	if (!(*move))
	{
		*move = ft_indexnew(i);
		if (!(*move))
		{
			return (-1);
		}
		(*path)->move_head = *move;
		(*path)->move = *move;
	}
	else
	{
		(*path)->move->next = ft_indexnew(i);
		if (!((*path)->move->next))
			return (-1);
		(*path)->move = (*path)->move->next;
	}
	return (0);
}

/*	creates a new path	*/

static t_path	*ft_pathnew(void)
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

/*	creates path element and adds it onto the linked list of paths	*/

int	create_path(t_path **path, t_room *pass, int nbr, int len)
{
	t_path	*new;

	new = ft_pathnew();
	if (!new)
		return (-1);
	new->nbr = nbr;
	new->len = len;
	new->move_head = NULL;
	if (*path)
	{
		new->prev = *path;
		(*path)->next = new;
		*path = (*path)->next;
	}
	else
	{
		new->prev = NULL;
		*path = new;
		pass->final_head = *path;
	}
	return (1);
}

/*	copies the paths from the array to the struct	*/

int	copy_to_path(t_room *pass, t_path **path, int **len)
{
	int	i;
	int	next;
	int	nbr;

	nbr = 1;
	i = 0;
	while ((*len)[i] > 0)
	{
		next = pass->info[NEXT][(*len)[i]];
		if (create_path(path, pass, nbr++, pass->info[LEN][(*len)[i]]) == -1)
			return (-1);
		if (create_index(&(*path)->move_head, path, (*len)[i]) == -1)
			return (-1);
		while (next > 0)
		{
			create_index(&(*path)->move_head, path, next);
			next = pass->info[NEXT][next];
		}
		++i;
	}
	return (1);
}
