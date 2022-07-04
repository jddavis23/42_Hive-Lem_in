/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:11:31 by molesen           #+#    #+#             */
/*   Updated: 2022/07/04 13:28:31 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

int	main(void)
{
	/*int	ants;

	if (parsing_phase(&ants) == ERROR)
		return (error());*/
	t_room	*pass;
	char	*input;

	input = NULL;
	pass = NULL;
	if (create(pass, input) == -1)
		return (0);
	return (0);
}
