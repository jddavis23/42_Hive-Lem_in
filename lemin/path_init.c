/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 09:38:32 by molesen           #+#    #+#             */
/*   Updated: 2022/07/15 13:30:59 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*	free_line and returns ERROR	*/

int	free_len(int **len)
{
	free(*len);
	return (ERROR);
}

/*	checks if there are anymore alive paths	*/

int	current_true(t_room *pass)
{
	int	i;

	i = 0;
	while (i < pass->total)
	{
		if (pass->info[CURRENT][i] != 0)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

/*	prints rooms if flag -p is activated	*/

static void	print_rooms(t_path *final, t_room *pass)
{
	final->move = final->move_head;
	ft_printf("	Rooms: ");
	while (final->move)
	{
		ft_printf("%s ", pass->rooms[final->move->index]);
		final->move = final->move->next;
		if (final->move)
			ft_printf("-> ");
		else
			ft_printf("\n\n");
	}
}

/*	prints the whole struct of the paths with the flags -p and -l	*/

void	printf_struct(t_room *pass)
{
	t_path	*final;
	t_index	*temp;
	int		i;

	final = pass->final_head;
	i = 0;
	ft_printf("\n{green}STRUCT: PATHS COLLECTED{uncolor} \n");
	while (final)
	{
		temp = final->move_head;
		ft_printf("PATH [%d] (Len: %d - nbr of struct: %d)\n", final->nbr, \
		final->len, i);
		if (pass->print_paths == TRUE)
			print_rooms(final, pass);
		++i;
		final = final->next;
	}
}

/*	initializes the functions that takes care of finding the paths	*/

int	initialize_path_finder(t_room *pass, t_input **build)
{
	t_path	*path;
	t_path	*final;

	path = NULL;
	final = NULL;
	pass->final_head = NULL;
	if (path_finder(&path, pass) == -1)
		return (error_path(pass, build, FALSE));
	if (!pass->final_head)
		return (error_path(pass, build, TRUE));
	final = pass->final_head;
	return (0);
}
