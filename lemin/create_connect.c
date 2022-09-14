/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_connect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:31:48 by jdavis            #+#    #+#             */
/*   Updated: 2022/09/13 17:48:00 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int	extend_connec(t_room *pass, int j)
{
	pass->tmp_con->current_room = j;
	pass->tmp_con->next = (t_connect *) malloc (sizeof(t_connect));
	if (!pass->tmp_con->next)
	{
		t_connect *temp;
		while (pass->head_con)
		{
			temp = pass->head_con->next;
			free(pass->head_con);
			pass->head_con = temp;
		}
		return (-1);
	}
	pass->tmp_con->next->next = NULL;
	pass->tmp_con->next->count = pass->tmp_con->count + 1;
	pass->tmp_con = pass->tmp_con->next;
	pass->tmp_con->current_room = -1;
	return (0);
}

int	create_connect(t_room *pass, int j)
{
	if (!pass->tmp_con)
	{
		pass->tmp_con = (t_connect *) malloc(sizeof(t_connect));
		if (!pass->tmp_con)
		{
			//clean
			return (-1);
		}
		pass->tmp_con->count = 1;
		pass->head_con = pass->tmp_con;
		pass->tmp_con->next = NULL;
	}
	else
	{
		if (extend_connec(pass, j) == -1)
			return (-1);
	}
	return (1);
}