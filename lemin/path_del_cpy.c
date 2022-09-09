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

/*	deletes the first index - used in error.c	*/

void	del_first_index(t_path *file)
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
