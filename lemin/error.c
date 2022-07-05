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
	if (err == NO_ANTS)
		ft_putstr_fd("Error: No ants detected. Must be 1 or more ants\n", 2);
	else if (err == TOO_MANY_ANTS)
		ft_putstr_fd("Error: Too many ants. Must be below max int\n", 2);
	else if (err == NON_DIGIT_ANTS)
		ft_putstr_fd("Error: Non digit detected. Only positive number allowed\n", 2);
	else if (err == COMMAND)
		ft_putstr_fd("Error: Location incorrect or duplicate ##start or ##end command\n", 2);
	else if (err == COORDINATES)
		ft_putstr_fd("Error: Incorrect coordinates\n", 2);
	else if (err == CONNECTION)
		ft_putstr_fd("Error: Incorrect connection\n", 2);
	else
		ft_putstr_fd("Error\n", 2);
	//ft_putstr_fd("Error\n", 2);
	return (ERROR);
}
