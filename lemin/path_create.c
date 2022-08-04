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

void	create_index(t_index **move, t_path **path, int i)
{
	t_index	*new;

	new = NULL;
	if (!(*move))
	{
		*move = ft_indexnew(i);
		(*path)->move_head = *move;
		(*path)->move = *move;
	}
	else
	{
		new = ft_indexnew(i);
		(*path)->move->next = new;
		(*path)->move = (*path)->move->next;
	}
}

/*	creates a new path	*/

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

/*	creates path element and adds it onto the linked list of paths	*/

void	create_path(t_path **path, t_room *pass, int nbr, int len)
{
	t_path *new;

	new = *path;
	new = ft_pathnew();
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
}
