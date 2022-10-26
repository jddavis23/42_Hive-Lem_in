/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:20:20 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/26 12:29:26 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*	Checking each line to check there is any referencing commands	*/
static int	count_in_helper(t_room *pass, char *input)
{
	if (!ft_strncmp(&input[0], "##start\n", 8) || \
		!ft_strncmp(&input[0], "##end\n", 6))
		return (free_connect(pass));
	return (1);
}

/*	Storing links in the linked list array into  double array for
	easy referencing during BFS	*/
static int	initialise_links(t_room *pass)
{
	int			i;
	int			j;
	int			count;
	t_connect	*temp;

	i = 0;
	while (i < pass->total)
	{
		count = pass->con_arr[i]->count;
		pass->con_arr[i] = pass->con_arr[i]->head;
		pass->links[i] = (int *) malloc(count * sizeof(int));
		if (!pass->links[i])
			return (error_free(pass, NULL, i, FALSE));
		j = 0;
		while (j < count)
		{
			pass->links[i][j++] = pass->con_arr[i]->current_room;
			temp = pass->con_arr[i];
			pass->con_arr[i] = pass->con_arr[i]->next;
			free(temp);
		}
		++i;
	}
	free(pass->con_arr);
	pass->con_arr = NULL;
	return (0);
}

/*	Searching for what room is at the start of the line*/
static int	search_connec(t_room *pass, int j, char *str)
{
	int	look;

	look = 0;
	while (look < pass->total)
	{
		if (!ft_strncmp(str, pass->rooms[look], j))
		{
			if (newline_minus(pass, look, str, str) == 1)
				return (2);
		}
		look++;
	}
	return (0);
}

/*	Finding and storing connections on each line to an array of linked
	for fast memory alllocation, then storing into a double array of ints*/
int	count_in(char *input, t_room *pass)
{
	int		i;
	int		j;
	int		stop;

	i = 0;
	while (input[i] != '\0')
	{
		stop = ft_strlen_stop(&input[i], '\n');
		j = 0;
		j += dash_in_section(&input[i + j], &input[i + stop]);
		while (input[i] != '#' && input[i + j] != '\n')
		{
			if (search_connec(pass, j, &input[i]) == 2)
				break ;
			j += dash_in_section(&input[i + j], &input[i + stop]);
			if (input[i + j] == '\n')
			 	return (-1);
		}
		if (count_in_helper(pass, &input[i]) == -1)
		 	return (-1);
		while (input[i] != '\n')
			++i;
		++i;
	}
	if (initialise_links(pass))
		return (-1);
	return (0);
}
