/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:11:31 by molesen           #+#    #+#             */
/*   Updated: 2022/07/19 12:42:13 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

static int	calc_max(int nbr1, int nbr2)
{
	if (nbr1 < nbr2)
		return (nbr1);
	return (nbr2);
}

int	len_array(int *links)
{
	int	i;

	i = 0;
	while (links[i] != -1)
		++i;
	return (i);
}

int	main(int argc, char **argv)
{
	t_room	*pass;
	char	*input;
	int		max_paths;

	if (argc == 1)
	{
		input = NULL;
		pass = (t_room *) malloc(sizeof(t_room));
		if (!pass)
			return (0);
		
		if (create(pass, &input) == ERROR)
			return (0);
		distance(pass);
		
		pass->len = len_array(pass->links[pass->end]);
		max_paths = calc_max(len_array(pass->links[0]), pass->len);
		if (max_paths < 1)
			return (ERROR);
		if (initialize_path_finder(pass, input) == ERROR)
			return (0);
		solve(pass);
		error_path(pass, input, FALSE);
	}
	else if (argv)
		ft_printf("Usage: ./lem-in < maps/subject.map\n");
	return (0);
}

/*

	Maps that should be considered an error but it accepts

		./lem-in < maps/error/space_at_end.map

	TO DO:

	if amount of ants < len of paths
		pick path with fewest turns

	do we want to collect the shortest path also?

	try out with example we tried on paper




	delete in parse_count >> # include <string.h>

*/
