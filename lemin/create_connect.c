/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_connect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:31:48 by jdavis            #+#    #+#             */
/*   Updated: 2022/09/14 12:10:20 by jdavis           ###   ########.fr       */
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
	if (j == r)
		++j;
	while (pass->rooms[j])
	{
		if (j == r)
			++j;
		if (choice == 0 && pass->rooms[j] && !ft_strcmp(*arr, pass->rooms[j]))
		{
			create_connect(pass, j);
			free(*arr);
			return (1);
		}
		else if (choice == 1 && pass->rooms[j] && \
			!ft_strcmp_stop(&(*arr)[str_len], pass->rooms[j]))
		{
			create_connect(pass, j);
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
	t_connect *tp;

	while (pass->head_con)
	{
		tp = pass->head_con->next;
		free(pass->head_con);
		pass->head_con = tp;
	}
	return (ERROR);
}

static int	extend_connec(t_room *pass, int j)
{
	t_connect	*temp;

	pass->tmp_con->current_room = j;
	pass->tmp_con->next = (t_connect *) malloc (sizeof(t_connect));
	if (!pass->tmp_con->next)
	{
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
