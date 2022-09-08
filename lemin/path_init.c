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

# include "../includes/lemin.h"

static void	printf_struct(t_room *pass)
{
	t_path *final;
	t_index *temp;
	int i;
	final = pass->final_head;
	i = 0;
	ft_printf("\n{green}STRUCT: PATHS COLLECTED{uncolor} \n");
	while (final)
	{
		temp = final->move_head;
		final->move = final->move_head;
		ft_printf("PATH [%d] (Len: %d	nbr of struct: %d)\n", final->nbr, final->len, i);
		while (final->move)
		{
			ft_printf("room: %s\n", pass->rooms[final->move->index]);
			final->move = final->move->next;
		}
		final->move_head = temp;
		++i;
		final = final->next;
	}
}

static int	unique_paths(t_room *pass)
{
	t_path *final;
	t_path *compare;
	t_index *temp;
	int count;

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

int	initialize_path_finder(t_room *pass, char *input)
{
	t_path	*path;
	t_path	*final;

	path = NULL;
	final = NULL;
	pass->final_head = NULL;
	path_finder(&path, pass);
	if (unique_paths(pass) == FALSE)
	{
		ft_printf("FAILED\n");
		printf_struct(pass);
		exit (0);
	}
	if (!pass->final_head)
		return (error_path(pass, input, TRUE));
	final = pass->final_head;
	// printf_struct(pass);
	// exit(0);
	return (0);
}

/*

make ssure it selects the path 6 and make sure it also use it when printing

*/