/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   by_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:07:15 by jdavis            #+#    #+#             */
/*   Updated: 2022/09/13 18:07:53 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int	check_start(void)
{
	static int	start = FALSE;

	if (start == FALSE)
	{
		start = TRUE;
		return (5);
	}
	return (-2);
}

static int	check_end(void)
{
	static int	end = FALSE;

	if (end == FALSE)
	{
		end = TRUE;
		return (6);
	}
	return (-2);
}

static int	comment_start_end(char *str)
{
	if (!ft_strncmp(str, "##start", 7))
		return (check_start());
	else if (!ft_strncmp(str, "##end", 5))
		return (check_end());
	else if (str[0] == '#')
		return (-1);
	return (0);
}

int	by_line(char *input)
{
	int	flag;
	int	count;
	int	i;
	int j;

	i = 0;
	count = 0;
	flag = 1;
	j = comment_start_end(&input[i]);
	if (j != 0)
		return (j);
	if (!ft_strlchr(input, ' ', ft_strlen_stop(input, '\n'))\
		 && ft_strlchr(input, '-', ft_strlen_stop(input, '\n')))
		return (2);
	while (input[i] != '\n' && input[i] != '\0')
	{
		if (flag && input[i] != ' ')
		{
			flag = 0;
			++count;
		}
		if (input[i++] == ' ')
			flag = 1;
	}
	return (count);
}