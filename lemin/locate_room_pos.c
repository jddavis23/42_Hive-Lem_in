/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_room_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:12:50 by jdavis            #+#    #+#             */
/*   Updated: 2022/09/16 13:26:38 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int	minus_newline(t_room *pass, int r, char *input, char *temp)
{
	int		j;
	char	*arr;

	j = addi_diff(input, &temp[-1]);
	arr = ft_strnew(j);
	if (!arr)
		return (-1);
	ft_strncpy(arr, input, j);
	if (find_connec_room(pass, r, &arr, 0) == 1)
		return (1);
	else
	{
		arr = NULL;
		if (loop_through_rooms(pass, r, input, temp) == ERROR)
			return (ERROR);
	}
	if (arr)
		free(arr);
	return (2);
}

static int	nlm_helper(t_room *pass, int *j, char *help)
{
	int	i;
	int	stop;

	stop = ft_strlen(pass->rooms[*j]);
	if (pass->rooms[*j] && help && help[-1] == '\n' && \
		help[stop] == '-')
	{
		i = 0;
		if (pass->rooms[i] && !ft_strcmp(pass->rooms[i], pass->rooms[*j]))
			++i;
		while (pass->rooms[i])
		{
			if (pass->rooms[i] && !ft_strcmp(pass->rooms[i], pass->rooms[*j]))
				++i;
			if (pass->rooms[i] && !ft_strncmp(&help[\
			stop + 1], pass->rooms[i], ft_strlen_stop(&help[stop + 1], '\n')))
				return (i);
			++i;
		}
	}
	if (pass->rooms[*j])
		++(*j);
	return (pass->total);
}

int	newline_minus(t_room *pass, int r, char *temp, char *input)
{
	int		j;
	int		i;
	int x = -1;

	if (find_connec_room(pass, r, &temp, 1) == 1)
		return (1);
	else if (x == 0)
	{
		j = 0;
		i = 0;
		while (pass->rooms[j])
		{
			j = room_finder(pass, r, j);
			if (j == -1)
				return (2);
			if (pass->rooms[j])
				temp = ft_strnstr(input, pass->rooms[j], \
				ft_strlen(pass->rooms[j]));
			i = nlm_helper(pass, &j, temp);
			if (pass->rooms[i])
				break ;
		}
		if (!pass->rooms[i] || !pass->rooms[j])
			return (free_connect(pass));
	}
	return (2);
}
