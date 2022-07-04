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

static int	below_max_int(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 10 || (len == 10 && ft_strcmp(str, "2147483647") > 0))
		return (FALSE);
	return (TRUE);
}

static int	only_digits(char *str, int *i)
{
	if (ft_strcmp("0", str) == 0 || ft_strcmp("\0", str) == 0)
		return (FALSE);
	if (below_max_int(str) == FALSE)
		return (FALSE);
	while (*str != '\0')
	{
		if (ft_isdigit(*str) == 0)
			return (FALSE);
		str++;
	}
	(*i)++;
	return (TRUE);
}

static int	is_comment(char *str)
{
	int	count;

	count = 0;
	while (*str == '#')
	{
		++count;
		++str;
	}
	if (count < 1)
		return (FALSE);
	return (count);
}

static int	is_coordinates(char *str)
{
	if (*str == 'L')
		return (FALSE);
	if (ft_word_count(str, ' ') != 3)
		return (FALSE);
		//below_max_int(char *str)
	// while (*str != '\0')
	// {
	// 	++count;
	// 	++str;
	// }
	// return (TRUE);
	// // count words has to be three
	// // two last words has to only consist of digits and has to be below max int
	// // duplicate rooms can first be checked when collecting phase aka jeff has easier time implementing this
	// if (str)
	// 	return (TRUE);
	return (TRUE);
}

static int is_connection(char *str)
{
	//words has to be two split by '-'
	//has to be digits not above max int
	if (str)
		return (TRUE);
	return (TRUE);
}

int	parsing_phase(int *ants)
{
	int		ret;
	int		i;
	int		comment;
	char	*line;

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
		comment = is_comment(line);
		if (i == 0 && only_digits(line, &i) == TRUE)
			*ants = ft_atoi(line);
		else if (comment == TRUE && i > 0)
		{
			//## start and end has to be done at coordinates and can only happen once.
			// so if it has already been found it is an error
			ft_printf("call function to collect comment if it contains ##start or ##end\n");
		}
		else if (i == 1 && is_coordinates(line) == TRUE)
			ft_printf("call function to collect name of rooms\n");
		else if (i >= 1 && is_connection(line) == TRUE)
		{
			++i;
			ft_printf("call function to collect connections\n");
		}
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

// how to check if path is valid?