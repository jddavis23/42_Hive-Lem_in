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
		pass->max_paths = calc_max(len_array(pass->links[0]), pass->len);
		if (pass->max_paths < 1)
			return (ERROR);
		if (initialize_path_finder(pass, input) == ERROR)
			return (0);
		solve(pass);
	}
	else if (argv)
		ft_printf("Usage: ./lem-in < maps/subject.map\n");
	return (0);
}

/*

Maps that should be considered an error but it accepts

	./lem-in < maps/error/connec_too_many.map
	./lem-in < maps/error/connec_too_many2.map
	./lem-in < maps/error/connec_too_many3.map
	./lem-in < maps/error/connec_too_many4.map

	./lem-in < maps/error/space_at_end.map

	doesn't display error if room name doesn't exist
	./lem-in < maps/error_parsing/no_room.map

	frees too much
	./lem-in < maps/error_parsing/dublicate.map
*/


/*

	TO DO:

	if amount of ants < len of paths
		pick path with fewest turns

	do we want to collect the shortest path also?

	try out with example we tried on paper



	make the function for printing out the final ants movement.

*/
