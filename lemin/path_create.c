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
		new = ft_indexnew(i);
		if (!new)
		{
			return (-1);
		}
		new->next = (*path)->move;
		(*path)->move_head = new;
		(*path)->move = new;
	}
	return (0);
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

int	create_path(t_path **path, t_room *pass, int nbr, int len)
{
	t_path *new;

	//new = *path;
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
	int	prev;
	int	nbr;
	int	m;

	m = 0;
	nbr = 1;
	// was this just a print statement? delete?
	/*while ((*len)[m] != -1)
	{
		ft_printf("%d ", (*len)[m]);
		m++;
	}*/
	i = 0;
	while ((*len)[i] > 0)
	{
		prev = pass->info[PREV][(*len)[i]];
		if (create_path(path, pass, nbr++, pass->info[LEN][(*len)[i]]) == -1)
			return (-1); //dont know what has been allocated here
		if (create_index(&(*path)->move_head, path, pass->end) == -1)
			return (-1);
		if (create_index(&(*path)->move_head, path, (*len)[i]) == -1)
			return (-1);
		while (prev > 0)
		{
			create_index(&(*path)->move_head, path, prev);
			prev = pass->info[PREV][prev];
		}
		++i;
	}
	return (1);
}
