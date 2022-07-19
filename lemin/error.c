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

static int	**free2d_int(int **links, int j, int end)
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
		// int k = 0;
		// ft_printf("pass->links[%d]: %p\n", i, links[i]);
		// while (links[i][k] != -1)
		// {
		// 	ft_printf("1pass->links[%d][%d]: %p\n", i, k, links[i][k]);
		// 	++k;
		// }
		// ft_printf("1pass->links[%d][%d]: %p\n", i, k, links[i][k]);
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

int	error_free(t_room *pass, char *input, int j, int first)
{
	if (first == FALSE)
	{
		ft_printf("{red}Error:{uncolor} during parsing phase\n");
	}
	// ft_printf("pass->rooms: %p\n", pass->rooms);
	// int i;
	// int k;
	// i = 0;
	// while (i < pass->total)
	// {
	// 	k = 0;
	// 	ft_printf("pass->rooms[%d]: %p\n", i, pass->rooms[i]);
	// 	while (pass->rooms[i][k] != '\0')
	// 	{
	// 		ft_printf("pass->rooms[%d][%d]: %p\n", i, k, pass->rooms[i][k]);
	// 		++k;
	// 	}
	// 	ft_printf("pass->rooms[%d][%d]: %p\n", i, k, pass->rooms[i][k]);
	// 	++i;
	// }
	if (pass->rooms)
		pass->rooms = ft_free2d(pass->rooms);
	if (pass->links)
		pass->links = free2d_int(pass->links, j, pass->end);
	if (pass->distance)
		free(pass->distance);
	if (pass->used)
		free(pass->used);
	if (pass)
		free(pass);
	if (input)
		free(input);
	ft_printf("HERE\n");
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

int	error_path(t_room *pass, char *input, int first)
{
	if (first == TRUE)
		ft_printf("{red}Error:{uncolor} no paths found\n");
	if (pass->final_head)
	{
		del_path(&pass->final_head);
	}
	if (pass->head)
	{
		del_path(&pass->head);
	}
	return (error_free(pass, input, pass->total, TRUE));
}