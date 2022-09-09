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

// static int	first_start_or_end(char *str, int i, int *command)
// {
// 	if (*command == TRUE)
// 		return (ERROR);
// 	if (ft_strcmp(str, "##start") == 0)
// 	{
// 		if (i > 1)
// 			return (ERROR);
// 		else
// 			*command = TRUE;
// 	}
// 	else if (ft_strcmp(str, "##end") == 0)
// 	{
// 		if (i > 1)
// 			return (ERROR);
// 		else
// 			*command = TRUE;
// 	}
// 	return (TRUE);
// }

/*
**	checks if valid line
**	valid line and their order: number of ants, coordinates, connections
**	comments/commands can occur anywhere (also before ants?????)
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

static int	grow(t_input *build, char *line, int len)
{
	char	*temp;
	int		factor;

	temp = NULL;
	if ((build->current + len) < (build->capacity * 2))
		factor = 2;
	else
		factor = len;
	temp = (char *) malloc((build->capacity * factor) * sizeof(char));
	if (!temp)
		return (-1);
	ft_bzero(temp, build->capacity * factor);
	//ft_printf("capacity(new) %i     capacity(old) %i   current(int) %i    currrent(string) %i\n", build->capacity * factor, build->capacity, build->current, ft_strlen(build->input));
	temp = ft_strcpy(temp, build->input);
	ft_strcat(&temp[build->current - 1], line);
	ft_strcat(&temp[build->current + len - 1], "\n");
	free(build->input);
	build->input = temp;
	build->capacity = build->capacity * factor;
	build->current = build->current + len;
	return (0);
}

/*	saves line to input	*/

static int	save_line(t_room *pass, t_input **build, char **line)
{
	int	len;

	len = ft_strlen(*line) + 1;
	if (!(*build))
	{
		*build = (t_input *) malloc(sizeof(t_input));
		if (!(*build))
		{
			//clean up
			free(*line);
			return (error_free(pass, build, 0, 0));
		}
		(*build)->input = (char *) malloc((len + 2) * sizeof(char));
		if (!(*build)->input)
		{
			//clean up
			free (*line);
			return (error_free(pass, build, 0, 0));
		}
		ft_bzero((*build)->input, len + 2);
		ft_strcat(ft_strcpy((*build)->input, *line), "\n");
		(*build)->capacity = len;
		(*build)->current = len;
	}
	else
	{
		if ((*build)->current + len >= (*build)->capacity)
		{
			if (grow(*build, *line, len) == -1)
			{
				//clean up
				free(*line);
				return (error_free(pass, build, 0, 0));
			}
		}
		else
		{
			ft_strcat(&(*build)->input[((*build)->current - 1)], *line);
			ft_strcat(&(*build)->input[((*build)->current + len - 1)], "\n");
			(*build)->current = (*build)->current + len;
		}
	}
	free(*line);
	return (1);
}

/*	reads file and stores in string and checks if invalid file	*/

int	file_save(t_room *pass, t_input **build)
{
	int		ret;
	int		i;
	int		command;
	char	*line;
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
			return (ERROR);
		if (!line)
			break ;
		if (is_comment(line) >= TRUE)
		{
			// if (first_start_or_end(line, i, &command) == ERROR)
			// {
			// 	free(line);
			// 	return (error(COMMAND));
			// }
		}
		else if (i == 0)// && only_digits(line, &i) == TRUE)
		{
			if (only_digits(line, &i) == TRUE)
				pass->ants = ft_atoi(line);
			else
				exit (0);//have to free pass and line?
		}
		else if (check_if_valid(line, &i, &total, &command) == ERROR)
		{
			return (ERROR);
		}
		if (save_line(pass, build, &line) == -1)
			return (-1);
	}
	return (total);
}