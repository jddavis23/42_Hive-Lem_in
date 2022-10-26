/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_connect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:31:48 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/26 12:12:31 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int	ft_strcmp_stop(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\n' && (str1[i] != '\0' || str2[i] != '\0'))
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

int	find_connec_room(t_room *pass, int r, char **arr, int choice)
{
	int	j;
	int	str_len;

	str_len = ft_strlen(pass->rooms[r]) + 1;
	j = 0;
	while (pass->rooms[j])
	{
		if (choice == 0 && j != r && pass->rooms[j] && \
			!ft_strcmp(*arr, pass->rooms[j]))
		{
			create_connect(pass, r, j);
			free(*arr);
			return (1);
		}
		else if (choice == 1 && j != r && pass->rooms[j] && \
			!ft_strcmp_stop(&(*arr)[str_len], pass->rooms[j]))
		{
			create_connect(pass, r, j);
			return (1);
		}
		++j;
	}
	if (choice == 0)
		free(*arr);
	return (-1);
}

int	free_connect(t_room *pass)
{
	t_connect	*tp;

	while (pass->head_con)
	{
		tp = pass->head_con->next;
		free(pass->head_con);
		pass->head_con = tp;
	}
	return (ERROR);
}

static int	extend_connec(t_room *pass, int i, int j)
{
	pass->con_arr[i]->current_room = j;
	pass->con_arr[i]->next = (t_connect *) malloc (sizeof(t_connect));
	if (!pass->con_arr[i]->next)
		return (free_connect(pass));
	pass->con_arr[i]->next->next = NULL;
	pass->con_arr[i]->next->count = pass->con_arr[i]->count + 1;
	pass->con_arr[i]->next->head = pass->con_arr[i]->head;
	pass->con_arr[i] = pass->con_arr[i]->next;
	pass->con_arr[i]->current_room = -1;
	pass->con_arr[j]->current_room = i;
	pass->con_arr[j]->next = (t_connect *) malloc (sizeof(t_connect));
	if (!pass->con_arr[j]->next)
		return (free_connect(pass));
	pass->con_arr[j]->next->next = NULL;
	pass->con_arr[j]->next->count = pass->con_arr[j]->count + 1;
	pass->con_arr[j]->next->head = pass->con_arr[j]->head;
	pass->con_arr[j] = pass->con_arr[j]->next;
	pass->con_arr[j]->current_room = -1;
	return (0);
}

int	create_connect(t_room *pass, int i, int j)
{
	int	x;

	if (!pass->con_arr)
	{
		pass->con_arr = (t_connect **) malloc(pass->total * sizeof(t_connect *));
		if (!pass->con_arr)
			return (-1);
		x = 0;
		while (x < pass->total)
		{
			pass->con_arr[x] = (t_connect *) malloc(sizeof(t_connect));
			if (!pass->con_arr[x])
				return (-1);
			pass->con_arr[x]->count = 1;
			pass->con_arr[x]->head = pass->con_arr[x];
			pass->con_arr[x]->next = NULL;
			pass->con_arr[x]->current_room = -1;
			x++;
		}
	}
	else
	{
		if (extend_connec(pass, i, j) == -1)
			return (-1);
	}
	return (1);
}
