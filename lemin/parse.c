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

static int	below_max_int(char *str, int len)
{
	if (len > 10 || (len == 10 && ft_strncmp(str, "2147483647", len) > 0))
		return (FALSE);
	return (TRUE);
}

static int	only_digits(char *str, int *i)
{
	if (ft_strcmp("0", str) == 0 || ft_strcmp("\0", str) == 0)
		return (FALSE);
	if (below_max_int(str, ft_strlen(str)) == FALSE)
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
	int	i;

	i = 0;
	while (str[i] == '#')
		++i;
	if (i < 1)
		return (FALSE);
	return (i);
}

static int	is_digit_and_below_max_int(char *str, int *i)
{
	(*i)++;
	if (below_max_int(&str[*i], ft_strlen_stop(&str[*i], ' ')) == FALSE)
		return (FALSE);
	while (str[*i] != ' ' && str[*i] != '\0')
	{
		if (ft_isdigit(str[*i]) == 0)
			return (FALSE);
		(*i)++;
	}
	return (TRUE);
}

static int	is_coordinates(char *str)
{
	int	i;

	if (*str == 'L')
		return (FALSE);
	if (ft_word_count(str, ' ') != 3)
		return (FALSE);
	i = 0;
	while (str[i] != ' ')
		++i;
	if (is_digit_and_below_max_int(str, &i) == FALSE)
		return (FALSE);
	if (is_digit_and_below_max_int(str, &i) == FALSE)
		return (FALSE);
	return (TRUE);
}

static int is_connection(char *str)
{
	int	count;
	int	i;

	if (ft_word_count(str, '-') != 2)
		return (FALSE);
	count = 0;
	i = 0;
	if (str[i] == 'L')
		return (FALSE);
	while (str[i] != '\0')
	{
		if (str[i] == '-')
		{
			if (str[i + 1] == 'L' || str[i + 1] == '#')
				return (FALSE);
			++count;
		}
		if (count > 1)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

int	parsing_phase(int *ants, int *total)
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
		else if (comment >= TRUE && i > 0)
		{
			//## start and end has to be done at coordinates and can only happen once.
			// so if it has already been found it is an error
			ft_printf("call function to collect comment if it contains ##start or ##end\n");
		}
		else if (i == 1 && is_coordinates(line) == TRUE)
		{
			(*total)++;
			ft_printf("room count: %d\n", *total);
		}
		else if (i > 0 && is_connection(line) == TRUE && *total > 1)
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