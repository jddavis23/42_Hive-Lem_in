/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:59:22 by jdavis            #+#    #+#             */
/*   Updated: 2022/07/20 12:10:08 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*void	picking_struct(t_path *path, int not_here)
{
	int	i;

	i = 0;
}*/

static int	diff_prev(t_room *pass, int len)
{
	t_path *path;
	int		count;

	path = pass->final_head;
	count = 0;
	while(path)
	{
		if (path->len == len)
			break ;
		count += len - path->len;
		path = path->next;
	}
	return (count);
}

void	solve(t_room *pass)
{
	int	i;
	/*
	int	first_len;
	t_path *find;

	i = 1;
	find = pass->final_head;
	first_len = find->len;
	if (pass->ants <= first_len && (i < find->nbr || pass->ants > i))
	{
		find = find->next;
		while (find)
		{
			ft_printf("%i  %i   %i   %i\n", find->len, first_len, i, find->nbr);
			if (find->len > first_len || i >= pass->ants)
				break ;
			++i;
			find = find->next;
		}
		//only use that path
	}
	else if (pass->ants > first_len)
	{
		find = find->next;
		while (find)
		{
			ft_printf("%i  %i   %i   %i\n", find->len, pass->ants, i, find->nbr);
			if (find->len > pass->ants || i >= pass->ants)
				break ;
			++i;
			find = find->next;
		}
	}
	ft_printf("amount of paths chosen %i\n", i);
	*/
	int dif;
	int	ants;
	//int current_len;
	//int	next_len;
	//int	selected_paths;
	t_path	*path;

	i = 1;
	path = pass->final_head;
	while (path && path->next)
	{
		dif = diff_prev(pass, path->len) + ((path->next->len - path->len) * i);
		ants = dif + i;
		ft_printf("dif prev: %d, next half: %d\n", diff_prev(pass, path->len), ((path->next->len - path->len) * i));
		ft_printf("i: %d, ants: %d, dif: %d\n", i, ants, dif);
		if (pass->ants <= ants)
			break ;
		path = path->next;
		++i;
	}
	ft_printf("paths: %i\n", i);
}

