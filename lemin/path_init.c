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

// ------ should we delete this one??? ------------ //////////
static int	unique_paths(t_room *pass)
{
	t_path	*final;
	t_path	*compare;
	t_index	*temp;
	int		count;

	final = pass->final_head;
	while (final)
	{
		final->move = final->move_head;
		temp = final->move;
		while (temp->index != pass->end)
		{
			//ft_printf("          PATH [%d]     \n", final->nbr);
			compare = pass->final_head;
			count = 0;
			while (compare)
			{
				compare->move = compare->move_head;
				//ft_printf("current room [%s]\n", pass->rooms[temp->index]);
				while (compare->move->index != pass->end)
				{
					if (compare->move->index == temp->index)
					{
						++count;
						//ft_printf("count: %d, room: %d room: %d\n", count, compare->move->index, temp->index);
						if (count > 1)
						{
							ft_printf("Error: Room %s occurs more than once\n", pass->rooms[compare->move->index]);
							return (FALSE);
						}
					}
					compare->move = compare->move->next;
				}
				compare = compare->next;
			}
			temp = temp->next;
		}
		final = final->next;
	}
	return (TRUE);
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
	if (unique_paths(pass) == FALSE)
	{
		ft_printf("FAILED\n"); //delete before submission??
		printf_struct(pass);
		exit (0);
	}
	if (!pass->final_head)
		return (error_path(pass, build, TRUE));
	final = pass->final_head;
	return (0);
}
