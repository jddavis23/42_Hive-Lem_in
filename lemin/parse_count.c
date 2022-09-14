/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:20:20 by jdavis            #+#    #+#             */
/*   Updated: 2022/09/14 17:50:10 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int	found_or_not(t_room *pass, int r, char *temp, char *input)
{
	int	str_len;

	if (temp && input[0] != '#')
	{
		str_len = ft_strlen(pass->rooms[r]);
		if (((temp[-1] == '\n' && temp[str_len] == '-') || \
			(temp[-1] == '-' && temp[str_len] == '\n')))
		{
			if (is_dash(&temp[str_len]) >= 1 && (temp[-1] == '\n' && \
				temp[str_len] == '-'))
				return (newline_minus(pass, r, temp, input));
			else if (dash_in_section(input, temp) >= 1 && \
				(temp[-1] == '-' && temp[str_len] == '\n'))
				return (minus_newline(pass, r, input, temp));
		}
	}
	return (0);
}

static int	count_in_helper(t_room *pass, char *input, int r, char *temp)
{
	int	stop;

	if (temp && input[0] != '#')
	{
		stop = ft_strlen_stop(&temp[1], '\n');
		while (ft_strnstr(&temp[1], pass->rooms[r], stop))
		{
			temp = ft_strnstr(&temp[1], pass->rooms[r], stop);
			if (temp[-1] == '-' && temp[ft_strlen(pass->rooms[r])] == '\n')
			{
				if (minus_newline(pass, r, &input[0], temp) == -1)
					return (-1);
			}
		}
	}
	else
	{
		if (!ft_strncmp(&input[0], "##start\n", 8) || \
			!ft_strncmp(&input[0], "##end\n", 6))
			return (free_connect(pass));
	}
	return (1);
}

int	count_in(int r, char *input, t_room *pass)
{
	int		i;
	char	*temp;
	int		j;

	i = 0;
	j = 0;
	pass->con_prev = pass->tmp_con->count;
	while (input[i] != '\0')
	{
		temp = ft_strnstr(&input[i], pass->rooms[r], \
			ft_strlen_stop(&input[i], '\n'));
		if (found_or_not(pass, r, temp, &input[i]) == -1)
			return (-1);
		if (count_in_helper(pass, &input[i], r, temp) == -1)
			return (-1);
		if (wrong_line(pass, r, &j, &input[i]) == ERROR)
			return (-1);
		while (input[i] != '\n')
			++i;
		++i;
	}
	return (0);
}
