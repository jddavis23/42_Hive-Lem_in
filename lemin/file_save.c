/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_save.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:10:17 by molesen           #+#    #+#             */
/*   Updated: 2022/09/14 11:35:08 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*	checks if the read line is a comment	*/

static int	is_comment(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '#')
		++i;
	if (i < 1)
		return (FALSE);
	return (i);
}

/*
**	checks if valid line
**	valid line and their order: number of ants, coordinates, connections
**	comments/commands can occur anywhere
*/

static int	check_if_valid(char *str, int *i, int *total, int *command)
{
	if (*i == 1 && is_coordinates(str) == TRUE)
		(*total)++;
	else if (*i > 0 && is_connection(str) == TRUE && *total > 1)
		(*i)++;
	else
	{
		free(str);
		str = NULL;
		if (*i == 1)
			return (error(COORDINATES));
		else if (*i > 1)
			return (error(CONNECTION));
		else
		{
			return (ERROR);
		}
	}
	if (*command == TRUE)
		*command = FALSE;
	return (TRUE);
}

static int	check_comment_or_ant(t_room *pass, char *line, int *i)
{
	if (is_comment(line) >= TRUE)
		return (TRUE);
	else if (*i == 0)
	{
		if (only_digits(line, i) == TRUE)
		{
			pass->ants = ft_atoi(line);
			return (TRUE);
		}
		else
		{
			free(line);
			return (ERROR);
		}
	}
	return (FALSE);
}

static int	returning(t_room *pass, int i, int total)
{
	pass->line = i - 1;
	if (i < 2)
		return (error(CONNECTION));
	return (total);
}

/*	reads file and stores in string and checks if invalid file	*/

int	file_save(t_room *pass, t_input **build, int ret, int total)
{
	char	*line;
	int		i;
	int		command;
	int		found;

	line = NULL;
	i = 0;
	command = FALSE;
	while (ret == 1)
	{
		ret = get_next_line(0, &line);
		if (ret == ERROR)
			return (ERROR);
		if (!line)
			break ;
		found = check_comment_or_ant(pass, line, &i);
		if (found == ERROR)
			return (ERROR);
		else if (found == FALSE && \
			check_if_valid(line, &i, &total, &command) == ERROR)
			return (ERROR);
		if (file_save_line(pass, build, &line) == ERROR)
			return (ERROR);
	}
	return (returning(pass, i, total));
}
