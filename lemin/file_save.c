/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_save.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:10:17 by molesen           #+#    #+#             */
/*   Updated: 2022/07/06 11:10:19 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

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
**	counts the amount of times the command start and end has been found
**	start and end only can occur once
**	the line after has to be a room name and its coordinates
*/

static int	first_start_or_end(char *str, int i, int *command)
{
	if (*command == TRUE)
		return (ERROR);
	if (ft_strcmp(str, "##start") == 0)
	{
		if (i > 1)
			return (ERROR);
		else
			*command = TRUE;
	}
	else if (ft_strcmp(str, "##end") == 0)
	{
		if (i > 1)
			return (ERROR);
		else
			*command = TRUE;
	}
	return (TRUE);
}

/*
**	checks if valid line
**	valid line and their order: number of ants, coordinates, connections
**	comments/commands can occur anywhere (also before ants?????)
*/

static int	check_if_valid(char *str, int *i, int *total, int *command)
{
	if (is_comment(str) >= TRUE)
	{
		if (first_start_or_end(str, *i, command) == ERROR)
			return (error(COMMAND));
		return (TRUE);
	}
	else if (*i == 1 && is_coordinates(str) == TRUE)
		(*total)++;
	else if (*i > 0 && is_connection(str) == TRUE && *total > 1)
		(*i)++;
	else
	{
		free(str);
		if (*i == 1)
			return (error(COORDINATES));
		else if (*i > 1)
			return (error(CONNECTION));
		else
			return (ERROR);
	}
	if (*command == TRUE)
		*command = FALSE;
	return (TRUE);
}

/*	reads file and stores in string and checks if invalid file	*/

int	parsing_phase(t_room *pass, char **input)
{
	int		ret;
	int		i;
	int		command;
	char	*line;
	char	*temp;
	char	*just;  //will think of better way
	int		total;

	ret = 1;
	line = NULL;
	i = 0;
	command = FALSE;
	total = 0;
	while (ret == 1)
	{
		ret = get_next_line(0, &line);
		if (ret == ERROR)
			return (0);
		if (!line)
			break ;
		//check_if_valid(line, &i, total, &command);
		if (i == 0 && only_digits(line, &i) == TRUE)
			pass->ants = ft_atoi(line);
		else if (check_if_valid(line, &i, &total, &command) == ERROR)
			return (ERROR);
		if (!(*input))
			*input = ft_strjoin(line, "\n");
		else
		{
			temp = ft_strjoin(line, "\n");
			just = ft_strjoin(*input, temp);
			free(*input);
			free(temp);
			*input = just;
		}
		free(line);
	}
	return (total);
}

// how to check if path is valid?