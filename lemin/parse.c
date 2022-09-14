/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:20:42 by jdavis            #+#    #+#             */
/*   Updated: 2022/09/14 17:50:32 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int	start_and_end(t_room *pass,	int hold, t_input **build, int *i)
{
	if (hold == 5)
		hold = 0;
	else
		hold = pass->total - 1;
	if (pass->rooms[hold])
		return (error_free(pass, build, 0, FALSE));
	pass->rooms[hold] = \
		ft_strnew(ft_strlen_stop(&(((*build)->input)[*i]), ' '));
	if (!pass->rooms[hold])
		return (error_free(pass, build, 0, FALSE));
	ft_strncat(pass->rooms[hold], &(((*build)->input)[*i]), \
		ft_strlen_stop(&(((*build)->input)[*i]), ' '));
	while (((*build)->input)[*i] != '\n')
		++(*i);
	return (TRUE);
}

static int	helper_function(t_room *pass, t_input **build, int *hold, int *i)
{
	if (*hold == 5 || *hold == 6)
	{
		if (start_and_end(pass, *hold, build, i) == ERROR)
			return (ERROR);
	}
	*hold = by_line(&(((*build)->input)[*i]));
	if (*hold < 2 || *hold == 5 || *hold == 6)
	{
		if (*hold == -2)
			return (-2);
		while (((*build)->input)[*i] != '\n')
			++(*i);
	}
	return (1);
}

static int	rooms_c_helper(t_room *pass, t_input **build, int *j, int *i)
{
	int	stop;

	stop = ft_strlen_stop(&(((*build)->input)[*i]), ' ');
	if ((*j) == pass->end)
		return (error_free(pass, build, 0, FALSE));
	pass->rooms[(*j)] = ft_strnew(stop);
	if (!pass->rooms[(*j)])
		return (error_free(pass, build, 0, FALSE));
	ft_strncat(pass->rooms[(*j)++], &(((*build)->input)[*i]), stop);
	while (((*build)->input)[*i] != '\n')
		++(*i);
	return (0);
}

static int	create_helper(t_room *pass, t_input **build, int hold)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	j = 1;
	while (((*build)->input)[i] != '\0')
	{
		ret = helper_function(pass, build, &hold, &i);
		if (ret == ERROR)
			return (ERROR);
		if (ret == -2)
			return (error_free(pass, build, j, FALSE));
		if (hold == 3)
		{
			if (rooms_c_helper(pass, build, &j, &i) == -1)
				return (-1);
		}
		else if (hold == 2)
			return (create_links(pass, build, i));
		++i;
	}
	return (1);
}

int	create(t_room *pass, t_input **build)
{
	int	hold;

	set_val(pass, build, &hold);
	if (pass->total == ERROR)
		return (error_free(pass, build, 0, TRUE));
	if (pass->total > 0)
	{
		pass->rooms = (char **) malloc((pass->total + 1) * sizeof(char *));
		pass->links = (int **) malloc(pass->total * sizeof(int *));
		if (!pass->rooms || !pass->links)
			return (error_free(pass, build, 0, FALSE));
		set_to_null(pass);
		if (create_helper(pass, build, hold) == ERROR)
			return (ERROR);
	}
	return (1);
}
