/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:10:08 by molesen           #+#    #+#             */
/*   Updated: 2022/07/06 11:10:09 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

/*	checks if a given string with digit is below max int or not	*/

static int	below_max_int(char *str, int len)
{
	if (len > 10 || (len == 10 && ft_strncmp(str, "2147483647", len) > 0))
		return (FALSE);
	return (TRUE);
}

/*
**	checks if the string only contains digits or else return error message
**	used to check if the amount of ants are correctly specified
*/

int	only_digits(char *str, int *i)
{
	if (ft_strcmp("0", str) == 0 || ft_strcmp("\0", str) == 0)
		return (error(NO_ANTS));
	if (below_max_int(str, ft_strlen(str)) == FALSE)
		return (error(TOO_MANY_ANTS));
	while (*str != '\0')
	{
		if (ft_isdigit(*str) == 0)
			return (error(NON_DIGIT_ANTS));
		str++;
	}
	(*i)++;
	return (TRUE);
}

/*	checks coordinates only consist of digits and space as seperator	*/

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

/*	function that checks if coordinates are correctly formatted	*/

int	is_coordinates(char *str)
{
	int	i;

	if (*str == 'L' || *str == ' ')
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

/*	checks if connections are correctly formatted	*/

int	is_connection(char *str)
{
	int	count;
	int	i;

	if (ft_word_count(str, '-') < 2)
		return (FALSE);
	count = 0;
	i = 0;
	if (str[i] == 'L' || *str == ' ')
		return (FALSE);
	while (str[i] != '\0')
	{
		if (str[i] == '-')
			++count;
		else if (str[i] == ' ')
			return (FALSE);
		++i;
	}
	if (count < 1)
		return (FALSE);
	return (TRUE);
}
