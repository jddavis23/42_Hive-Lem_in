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

// static void	printf_struct(t_room *pass)
// {
// 	t_path *final;
// 	t_index *temp;
// 	int i;
// 	final = pass->final_head;
// 	i = 0;
// 	ft_printf("\n{green}after sort: finalS:{uncolor} \n");
// 	while (final)
// 	{
// 		temp = final->move_head;
// 		final->move = final->move_head;
// 		ft_printf("final\nnbr: %d	Len: %d	nbr of struct: %d\n", final->nbr, final->len, i);
// 		while (final->move)
// 		{
// 			ft_printf("room: %s\n", pass->rooms[final->move->index]);
// 			final->move = final->move->next;
// 		}
// 		final->move_head = temp;
// 		++i;
// 		final = final->next;
// 	}
// }

static int	unique_paths(t_room *pass)
{
	int	current;
	int	compare;
	int	i;
	int	j;

	current = 0;
	while (pass->links[pass->end][current] != -1)
	{
		if (pass->info[NEXT][pass->links[pass->end][current]] == pass->end)
		{
			compare = current + 1;
			while (pass->links[pass->end][compare] != -1)
			{
				if (pass->info[NEXT][pass->links[pass->end][compare]] == pass->end)
				{
					//ft_printf("          PATH [%i]     \n", current);
					i = pass->links[pass->end][current];
					while (i != 0)
					{
						//ft_printf("current room [%s]\n", pass->rooms[i]);
						j = pass->links[pass->end][compare];
						while (j != 0)
						{
							//ft_printf("compare [%s]\n", pass->rooms[j]);
							if (i == j)
								return (FALSE);
							j = pass->info[PREV][j];
						}
						i = pass->info[PREV][i];
					}
				}
				++compare;
			}
		}
		++current;
	}
	return (TRUE);
}

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
		//ft_printf("FAILED\n");
		exit (0);
	}
	if (!pass->final_head)
		return (error_path(pass, input, TRUE));
	final = pass->final_head;
	return (0);
}
