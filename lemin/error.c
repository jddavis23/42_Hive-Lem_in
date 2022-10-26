/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:11:17 by molesen           #+#    #+#             */
/*   Updated: 2022/10/26 12:19:39 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*	Freeing t_connect array of linked lists	*/
static t_connect	**free2d_t_connect(t_connect **connect, int total)
{
	int			i;
	t_connect	*temp;

	i = 0;
	while (connect[i] && i < total)
	{
		while (connect[i]->head)
		{
			temp = connect[i]->head;
			connect[i]->head = connect[i]->head->next;
			free(temp);
		}
		++i;
	}
	free(connect);
	return (NULL);
}

/*	frees everything that needs to be freed	*/
int	error_free(t_room *pass, t_input **build, int j, int first)
{
	if (first == FALSE)
		ft_printf("{red}Error:{uncolor} during parsing phase\n");
	if (pass)
	{
		if (pass->rooms)
			pass->rooms = ft_free_rooms(pass, pass->rooms);
		if (pass->links)
			pass->links = free2d_int(pass->links, j, pass->end);
		if (pass->info)
			free2d_int(pass->info, 8, 7);
		if (pass->line_check)
			free(pass->line_check);
		if (pass->con_arr)
		 	pass->con_arr = free2d_t_connect(pass->con_arr, pass->total);
		free(pass);
	}
	if (*build)
	{
		if ((*build)->input)
			free ((*build)->input);
		free(*build);
	}
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
			ft_printf("Location incorrect or duplicate ##start/##end command\n");
		else if (err == COORDINATES)
			ft_printf("Incorrect coordinates\n");
		else if (err == CONNECTION)
			ft_printf("Incorrect connection\n");
		else
			ft_printf("\n");
	}
	return (ERROR);
}

/*	deletes the first index - used in error.c	*/

static void	del_first_index(t_path *file)
{
	t_index	*temp;

	if (file->move_head)
	{
		file->move = file->move_head;
		temp = file->move;
		if (file->move->next)
		{
			file->move = file->move->next;
			free(temp);
			file->move_head = file->move;
			file->len--;
		}
		else
		{
			free(temp);
			file->move = NULL;
			file->move_head = NULL;
		}
	}
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

int	error_path(t_room *pass, t_input **build, int first)
{
	if (first == TRUE)
		ft_printf("{red}Error:{uncolor} no paths found\n");
	if (pass->final_head)
		del_path(&pass->final_head);
	return (error_free(pass, build, pass->total, TRUE));
}
