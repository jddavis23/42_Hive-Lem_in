/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:02:28 by jdavis            #+#    #+#             */
/*   Updated: 2022/09/15 11:23:24 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int	mnl_found_room(t_room *pass, int *i, char *input, char *temp)
{
	char	*arr;

	if (pass->rooms[*i] && !ft_strncmp(input, pass->rooms[*i], \
		ft_strlen(pass->rooms[*i])))
	{
		arr = ft_strnew(addi_diff(input, &temp[-1]));
		if (!arr)
		{
			*i = ERROR;
			return (ERROR);
		}
		ft_strncpy(arr, input, addi_diff(input, &temp[-1]));
		if (ft_strcmp(arr, pass->rooms[*i]))
		{
			free(arr);
			arr = NULL;
			return (TRUE);
		}
		free(arr);
		arr = NULL;
	}
	return (FALSE);
}

/*	checks if room we are connected to is valid	*/

static int	mnl_helper_loop(t_room *pass, int *j, char *input, char *temp)
{
	int	i;
	int	ret;

	i = 0;
	if (pass->rooms[i] && !ft_strcmp(pass->rooms[i], pass->rooms[*j]))
		++i;
	while (pass->rooms[i])
	{
		if (pass->rooms[i] && !ft_strcmp(pass->rooms[i], pass->rooms[*j]))
			++i;
		ret = mnl_found_room(pass, &i, input, temp);
		if (i == ERROR || ret == TRUE)
			break ;
		++i;
	}
	return (i);
}

static int	mnl_helper(t_room *pass, int *j, char *input, char *temp)
{
	static int	flag = 0;
	int			i;

	i = -1;
	if (pass->rooms[*j] && temp && temp[-1] == '-' && \
		temp[ft_strlen(pass->rooms[*j])] == '\n')
	{
		++flag;
		i = mnl_helper_loop(pass, j, input, temp);
	}
	if (pass->rooms[*j])
		++(*j);
	if (!flag)
		return (-1);
	return (i);
}

int	loop_through_rooms(t_room *pass, int r, char *input, char *temp)
{
	char	*hold;
	int		i;
	int		j;
	int		value;

	hold = temp;
	i = -1;
	j = 0;
	while (pass->rooms[j])
	{
		j = room_finder(pass, r, j);
		if (j == -1)
			return (2);
		temp = NULL;
		if (pass->rooms[j])
			temp = ft_strstr(input, pass->rooms[j]);
		value = mnl_helper(pass, &j, input, temp);
		if (value >= 0)
			i = value;
	}
	if ((i != -1 && !pass->rooms[i]) || (i == -1 && hold[-1] == '-'))
		return (free_connect(pass));
	return (1);
}

int	room_finder(t_room *pass, int r, int j)
{
	while (pass->rooms[j])
	{
		if (j != r && ft_strstr(pass->rooms[j], pass->rooms[r]))
			break ;
		else if (j != r && ft_strstr(pass->rooms[r], pass->rooms[j]))
			return (-1);
		++j;
	}
	return (j);
}
