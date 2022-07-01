/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:11:51 by molesen           #+#    #+#             */
/*   Updated: 2022/07/01 16:11:53 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

static int	only_digits(char *str, int *i, int *ants)
{
	*ants = ft_atoi(str);
	while (*str != '\0')
	{
		if (ft_isdigit(*str) == 0)
			return (FALSE);
		str++;
	}
	(*i)++;
	return (TRUE);
}

static int	valid_comment(char *str)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == '#')
			++count;
		++str;
	}
	if (count > 2)
		return (FALSE);
	return (TRUE);
}

static int	valid_coordinates(char *str)
{
	if (str)
		return (TRUE);
	return (TRUE);
}

static int valid_connection(char *str)
{
	if (str)
		return (TRUE);
	return (TRUE);
}

int	parsing_phase(int *ants)
{
	int		ret;
	char	*line;
	int		i;

	ret = 1;
	line = NULL;
	i = 0;
	while (ret == 1)
	{
		ret = get_next_line(0, &line);
		if (ret == ERROR)
			return (0);
		if (!line)
			break ;
		if (i == 0 && only_digits(line, &i, ants) == FALSE)
			return (ERROR);
		else if (i == 1 && valid_coordinates(line) == TRUE)
			ft_printf("call function to collect name of rooms\n");
		else if (i >= 1 && valid_connection(line) == TRUE)
		{
			++i;
			ft_printf("call function to collect connections\n");
		}
		else if (valid_comment(line) == TRUE && i > 0)
			ft_printf("call function to collect comment if it contains ##start or ##end\n");
		else
		{
			free(line);
			return (ERROR);
		}
		ft_printf("%s\n", line);
		free(line);
	}
	return (0);
}
