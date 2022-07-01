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

int	error(void)
{
	//make sure everything is freed that needs to be freed
	
	ft_putstr_fd("Error\n", 2);
	return (0);
}
