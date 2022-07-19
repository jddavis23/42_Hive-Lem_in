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

static char	**free2d(char **dest)
{
	int	i;

	i = 0;
	while (&dest[i])
	{
		ft_strdel(&dest[i]);
		i++;
	}
	free(dest);
	return (NULL);
}

static void	free2d_int(t_room *pass, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(pass->links[i]);
		++i;
	}
	free(pass->links);
	pass->links = NULL;
}

int	error_free(t_room *pass, char *input, int j)
{
	if (pass->rooms)
	{
		pass->rooms = free2d(pass->rooms);
	}
	if (pass->links)
	{
		free2d_int(pass, j);
	}
	if (pass->distance)
		free(pass->distance);
	if (pass->used)
		free(pass->used);
	if (pass)
		free(pass);
	if (input)
		free(input);
	return (ERROR);
}

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
	return (ERROR);
}
