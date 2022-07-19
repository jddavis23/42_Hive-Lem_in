/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:59:22 by jdavis            #+#    #+#             */
/*   Updated: 2022/07/19 13:24:14 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*void	picking_struct(t_path *path, int not_here)
{
	int	i;

	i = 0;
}*/

void	solve(t_room *pass)
{
	int	i;
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
			if (find->len > first_len || i >= find->nbr)
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
			if (find->len > pass->ants || i > find->nbr)
				break ;
			++i;
			find = find->next;
		}
	}
	ft_printf("amount of paths chosen %i\n", i);
}

