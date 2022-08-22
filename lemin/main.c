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

// static int	calc_max(int nbr1, int nbr2)
// {
// 	if (nbr1 < nbr2)
// 		return (nbr1);
// 	return (nbr2);
// }

// int	len_array(int *links)
// {
// 	int	i;

// 	i = 0;
// 	while (links[i] != -1)
// 		++i;
// 	return (i);
// }

/*	function checking room is already in use	*/

static int	create_used(t_room *pass)
{
	int	i;

	i = 0;
	pass->info = (int **) malloc(5 * sizeof(int *));
	if (!pass->info)
		return (ERROR);
	pass->info[PATH] = (int *) malloc(pass->total * sizeof(int));
	pass->info[PREV] = (int *) malloc(pass->total * sizeof(int));
	pass->info[LEN] = (int *) malloc(pass->total * sizeof(int));
	pass->info[CURRENT] = (int *) malloc(pass->total * sizeof(int));
	pass->info[CONNECT] = (int *) malloc(pass->total * sizeof(int));
	if (!pass->info[PATH] || !pass->info[PREV] || !pass->info[LEN] || !pass->info[CURRENT] || !pass->info[CONNECT])
		return (ERROR);
	while (i < pass->total)
	{
		pass->info[PATH][i] = FALSE;
		pass->info[PREV][i] = FALSE;
		pass->info[LEN][i] = FALSE;
		pass->info[CONNECT][i] = FALSE;
		pass->info[CURRENT][i++] = FALSE;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_room	*pass;
	char	*input;
	//int		max_paths;

	if (argc == 1 || (argc == 2 && ft_strcmp(argv[1], "-r") == 0))
	{
		input = NULL;
		pass = (t_room *) malloc(sizeof(t_room));
		if (!pass)
			return (0);
		if (argc == 2)
			pass->row = TRUE;
		else
			pass->row = FALSE;
		if (create(pass, &input) == ERROR)
			return (0);
		if (create_used(pass) == ERROR)
			return (error_path(pass, input, TRUE));
		distance(pass);
		// pass->len = len_array(pass->links[pass->end]);
		// max_paths = calc_max(len_array(pass->links[0]), pass->len);
		// if (max_paths < 1)
		// 	return (ERROR);
		if (initialize_path_finder(pass, input) == ERROR)
			return (0);
		ft_printf("%s\n", input);
		solve(pass);
		error_path(pass, input, FALSE);
	}
	else if (argv)
		ft_printf("Usage: ./lem-in < maps/subject.map\n");
	return (0);
}

/*



Decide when to replace existing path struct

*/
