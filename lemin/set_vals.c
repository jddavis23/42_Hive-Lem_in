/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_vals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:14:26 by jdavis            #+#    #+#             */
/*   Updated: 2022/09/16 12:56:16 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	set_to_null(t_room *pass)
{
	int	i;

	i = 0;
	while (i < pass->total)
	{
		pass->rooms[i] = NULL;
		pass->links[i] = NULL;
		++i;
	}
	pass->rooms[i] = NULL;
}

void	set_val(t_room *pass, t_input **build, int *hold)
{
	*hold = ERROR;
	pass->line_check = NULL;
	pass->rooms = NULL;
	pass->links = NULL;
	pass->tmp_con = NULL;
	pass->head_con = NULL;
	pass->info = NULL;
	pass->total = file_save(pass, build, 1, 0);
	pass->end = pass->total - 1;
	pass->con_arr = NULL;
}
