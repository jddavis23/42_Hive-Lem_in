/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:11:17 by molesen           #+#    #+#             */
/*   Updated: 2022/07/01 16:11:20 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

int	error(int err)
{
	//make sure everything is freed that needs to be freed
	if (err == -1)
		ft_printf("{red}Error{uncolor}\n");
	else
	{
		ft_printf("{red}Error:{uncolor} ");
		if (err == NO_ANTS)
			ft_printf("No ants detected. Must be 1 or more ants\n");
		else if (err == TOO_MANY_ANTS)
			ft_printf("Too many ants. Must be below max int\n");
		else if (err == NON_DIGIT_ANTS)
			ft_printf("Non digit detected. Only positive number allowed\n");
		else if (err == COMMAND)
			ft_printf("Location incorrect or duplicate ##start or ##end command\n");
		else if (err == COORDINATES)
			ft_printf("Incorrect coordinates\n");
		else if (err == CONNECTION)
			ft_printf("Incorrect connection\n");
		else
			ft_printf("\n");
	}
	//ft_putstr_fd("Error\n", 2);
	return (ERROR);
}
