/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_save_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:35:52 by jdavis            #+#    #+#             */
/*   Updated: 2022/09/14 11:37:06 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*	logic of growing the build->input	*/

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
	temp = ft_strcpy(temp, build->input);
	ft_strcat(&temp[build->current - 1], line);
	ft_strcat(&temp[build->current + len - 1], "\n");
	free(build->input);
	build->input = temp;
	build->capacity = build->capacity * factor;
	build->current = build->current + len;
	return (0);
}

/*	saving logic when it is the first time saving anything to build	*/

static int	save_no_prev_build(t_room *pass, t_input **build, char **line, \
	int len)
{
	*build = (t_input *) malloc(sizeof(t_input));
	if (!(*build))
	{
		free(*line);
		return (error_free(pass, build, 0, 0));
	}
	(*build)->input = (char *) malloc((len + 2) * sizeof(char));
	if (!(*build)->input)
	{
		free (*line);
		return (error_free(pass, build, 0, 0));
	}
	ft_bzero((*build)->input, len + 2);
	ft_strcat(ft_strcpy((*build)->input, *line), "\n");
	(*build)->capacity = len;
	(*build)->current = len;
	return (1);
}

/*	saving logic when already having saved something to build	*/

static int	save_have_prev_build(t_room *pass, t_input **build, char **line, \
	int len)
{
	if ((*build)->current + len >= (*build)->capacity)
	{
		if (grow(*build, *line, len) == -1)
		{
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
	return (1);
}

/*	saves line to input	*/

int	file_save_line(t_room *pass, t_input **build, char **line)
{
	int	len;

	len = ft_strlen(*line) + 1;
	if (!(*build))
	{
		if (save_no_prev_build(pass, build, line, len) == ERROR)
			return (ERROR);
	}
	else
	{
		if (save_have_prev_build(pass, build, line, len) == ERROR)
			return (ERROR);
	}
	free(*line);
	return (1);
}
