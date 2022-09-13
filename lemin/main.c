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

#include "../includes/lemin.h"

/*	function checking room is already in use	*/

static int	create_used(t_room *pass)
{
	int	i;

	i = 0;
	pass->info = (int **) malloc(8 * sizeof(int *));
	if (!pass->info)
		return (ERROR);
	pass->info[PATH] = (int *) malloc(pass->total * sizeof(int));
	pass->info[PREV] = (int *) malloc(pass->total * sizeof(int));
	pass->info[LEN] = (int *) malloc(pass->total * sizeof(int));
	pass->info[CURRENT] = (int *) malloc(pass->total * sizeof(int));
	pass->info[NEXT] = (int *) malloc(pass->total * sizeof(int));
	pass->info[JUMP] = (int *) malloc(pass->total * sizeof(int));
	pass->info[LOCKED] = (int *) malloc(pass->total * sizeof(int));
	pass->info[MOVE] = (int *) malloc(pass->total * sizeof(int));
	if (!pass->info[PATH] || !pass->info[PREV] || !pass->info[LEN] || \
		!pass->info[CURRENT] || !pass->info[NEXT] || !pass->info[JUMP] || \
		!pass->info[LOCKED] || !pass->info[MOVE])
		return (ERROR);
	while (i < pass->total)
		info_set_to_zero(pass, i++);
	return (0);
}

/*	prints help information about how to use the flags to the terminal	*/

static void	print_help(void)
{
	ft_printf("Usage: ./lem-in [flags] < maps/subject.map\n\n	flags:\n");
	ft_printf("		-h :	display help\n");
	ft_printf("		-r :	prints row number\n");
	ft_printf("		-p :	prints found paths - all information\n");
	ft_printf("		-l :	prints found paths - basic information ex len\n");
	ft_printf("		-c :	prints total row count without ants movement\n\n");
}

/*	updates the flags in the struct to either TRUE or FALSE	*/

static void	update_flags(int argc, char *str, t_room *pass)
{
	pass->print_row = FALSE;
	pass->print_paths = FALSE;
	pass->print_len = FALSE;
	pass->print_count = FALSE;
	if (argc == 2)
	{
		if (!ft_strcmp(str, "-r"))
			pass->print_row = TRUE;
		else if (!ft_strcmp(str, "-p"))
			pass->print_paths = TRUE;
		else if (!ft_strcmp(str, "-l"))
			pass->print_len = TRUE;
		else if (!ft_strcmp(str, "-c"))
			pass->print_count = TRUE;
	}
}

int	main(int argc, char **argv)
{
	t_room	*pass;
	t_input	*build;

	if (argc == 1 || (argc == 2 && (!ft_strcmp(argv[1], "-r") || \
		!ft_strcmp(argv[1], "-p") || !ft_strcmp(argv[1], "-l") || \
		!ft_strcmp(argv[1], "-c"))))
	{
		build = NULL;
		pass = (t_room *) malloc(sizeof(t_room));
		if (!pass)
			return (0);
		ft_printf("Entered create\n");
		if (create(pass, &build) == ERROR)
		{
			ft_printf("ERROR\n");
			return (0);
		}
		ft_printf("Exited create\n");
		update_flags(argc, argv[1], pass);
		if (create_used(pass) == ERROR)
			return (error_path(pass, &build, TRUE));
		if (initialize_path_finder(pass, &build) == ERROR)
			return (0);
		solve(pass, &build);
	}
	else if (argc == 2 && !ft_strcmp(argv[1], "-h"))
		print_help();
	else if (argv)
		ft_printf("Usage: ./lem-in < maps/subject.map\n");
	return (0);
}
