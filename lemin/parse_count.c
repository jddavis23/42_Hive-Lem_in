/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:20:20 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/25 12:27:12 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include <stdio.h>

// static int	found_or_not(t_room *pass, int r, char *temp, char *input)
// {
// 	int	str_len;

// 	if (temp && input[0] != '#')
// 	{
// 		str_len = ft_strlen(pass->rooms[r]);
// 		if (((temp[-1] == '\n' && temp[str_len] == '-') || \
// 			(temp[-1] == '-' && temp[str_len] == '\n')))
// 		{
// 			if (is_dash(&temp[str_len]) >= 1 && (temp[-1] == '\n' && \
// 				temp[str_len] == '-'))
// 				return (newline_minus(pass, r, temp, input));
// 			else if (dash_in_section(input, temp) >= 1 && \
// 				(temp[-1] == '-' && temp[str_len] == '\n'))
// 				return (minus_newline(pass, r, input, temp));
// 		}
// 	}
// 	return (0);
// }

static int	count_in_helper(t_room *pass, char *input)
{
	if (!ft_strncmp(&input[0], "##start\n", 8) || \
		!ft_strncmp(&input[0], "##end\n", 6))
		return (free_connect(pass));
	return (1);
}

static int	initialise_links(t_room *pass)
{
	int	i;
	int	j;

	i = 0;
	while (i < pass->total)
	{
		pass->links[i] = (int *) malloc((pass->con_arr[i]->count - 1) * sizeof(int));
		if (!pass->links[i])
			return (-1);//return (error_free(pass, NULL, 0, FALSE));//double check freeing
		j = 0;
		while (j < (pass->con_arr[i]->count - 1))
		{
			pass->links[i][j] = pass->con_arr[i]->head->current_room;
			pass->con_arr[i]->head = pass->con_arr[i]->head->next;
			++j;
		}
		++i;
	}
	return (0);
}

int	count_in(char *input, t_room *pass)
{
	int		i;
	int		j;
	int		stop;
	int		look;
	int		end;

	i = 0;
	while (input[i] != '\0')
	{
		stop = ft_strlen_stop(&input[i], '\n');
		j = 0;
		j += dash_in_section(&input[i + j], &input[i + stop]);
		end = 0;
		while (input[i] != '#' && input[i + j] != '\n')
		{
			look = 0;
			while (look < pass->total)
			{
				if (!ft_strncmp(&input[i], pass->rooms[look], j))
				{
					if (newline_minus(pass, look, &input[i], &input[i]) == 1)
					{
						end = 2;
						break ;
					}
				}
				look++;
			}
			if (end == 2)
				break ;
			j += dash_in_section(&input[i + j], &input[i + stop]);
			if (input[i + j] == '\n') //this isnt workin gto spot an error
			 	return (-1);
		}
		if (count_in_helper(pass, &input[i]) == -1)
		{
		 	return (-1);
		}
		while (input[i] != '\n')
			++i;
		++i;
	}
	if (initialise_links(pass))
		return (-1);
	i = 0;
	while (i < pass->total)
	{
		j = 0;
		while (j < pass->con_arr[i]->count - 1)
			ft_printf("%s   ", pass->rooms[pass->links[i][j++]]);
		ft_printf("\n");
		++i;
	}
	exit (0);
	// i = 0;
	// while (i < pass->total)
	// {
	// 	while (pass->con_arr[i]->head->current_room != -1)
	// 	{
	// 		ft_printf("%s   ", pass->rooms[pass->con_arr[i]->head->current_room]);
	// 		pass->con_arr[i]->head = pass->con_arr[i]->head->next;
	// 	}
	// 	ft_printf("\n");
	// 	if (i == 1)
	// 		exit (0);
	// 	++i;

	// }
	return (0);
}
