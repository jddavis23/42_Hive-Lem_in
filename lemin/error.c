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

/*	frees all the elements in 2d int array	*/

int	**free2d_int(int **links, int j, int end)
{
	int	i;

	i = 0;
	if (links[i])
	{
		free(links[i]);
		links[i] = NULL;
	}
	++i;
	while (i < j)
	{
		free(links[i]);
		links[i] = NULL;
		++i;
	}
	if (links[end])
	{
		free(links[end]);
		links[end] = NULL;
	}
	free(links);
	return (NULL);
}

/*	frees everything that needs to be freed	*/

int	error_free(t_room *pass, char *input, int j, int first)
{
	if (first == FALSE)
		ft_printf("{red}Error:{uncolor} during parsing phase\n");
	if (pass->rooms)
		pass->rooms = ft_free2d(pass->rooms);
	if (pass->links)
		pass->links = free2d_int(pass->links, j, pass->end);
	if (pass->distance)
		free(pass->distance);
	// if (pass->used)
	// 	free(pass->used);
	if (pass)
		free(pass);
	if (input)
		free(input);
	return (ERROR);
}

/*	specific invalid map error messages	*/

int	error(int err)
{
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

/*	frees and deletes a path struct	*/

void	del_path(t_path **path)
{
	t_path	*temp;

	while (*path)
	{
		temp = (*path)->next;
		(*path)->move = (*path)->move_head;
		while ((*path)->move)
			del_first_index(*path);
		(*path)->move_head = NULL;
		free(*path);
		*path = temp;
	}
}


/*
**	function called in two scenarious
**	upon error in path finding phase or upon finished program
*/

int	error_path(t_room *pass, char *input, int first)
{
	if (first == TRUE)
		ft_printf("{red}Error:{uncolor} no paths found\n");
	if (pass->final_head)
		del_path(&pass->final_head);
	if (pass->head)
		del_path(&pass->head);
	return (error_free(pass, input, pass->total, TRUE));
}
