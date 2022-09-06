/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:31:42 by molesen           #+#    #+#             */
/*   Updated: 2022/09/06 15:31:44 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*	calculates the previous	*/

static int	diff_prev(t_room *pass, int len)
{
	t_path	*path;
	int		count;

	path = pass->final_head;
	count = 0;
	while(path)
	{
		if (path->len == len)
			break ;
		count += len - path->len;
		path = path->next;
	}
	return (count);
}

/*	calculates how many paths we should send ants down	*/

static void	path_calc(int remain_ants, t_path **path)
{
	while (*path && (*path)->prev)
	{
		if (remain_ants > (*path)->prev->max_ants)
			break ;
		*path = (*path)->prev;
	}
}

/*	sets paths of the ants	*/

static t_ants	*path_setter(t_ants **ants_move, t_room *pass, t_path **end, t_ants *head)
{
	t_path		*path;
	static int	current_ant = 0;

	path = pass->final_head;
	if (head && current_ant < pass->ants)
		path_calc(pass->ants - current_ant, end);
	while (path && path->nbr <= (*end)->nbr && current_ant < pass->ants)
	{
		current_ant++;
		create_ants(ants_move, current_ant, path->move_head);
		if (!head)
			head = *ants_move;
		path = path->next;
	}
	return (head);
}

/*	calculates max amount of ants to be send down a path before we take the next path in use	*/

static void	calc_amount_of_ants(t_room *pass, t_path **path)
{
	t_path	*prev;
	int		dif;

	prev = NULL;
	while (*path && (*path)->next)
	{
		dif = diff_prev(pass, (*path)->len) + (((*path)->next->len - (*path)->len) * (*path)->nbr);
		(*path)->max_ants = dif + (*path)->nbr;
		(*path)->prev = prev;
		
		if (pass->ants <= (*path)->max_ants)
			break ;
		prev = *path;
		*path = (*path)->next;
	}
	(*path)->prev = prev;
}

/*	calls the functions to calculate amount of ants per path and the printing function	*/

void	solve_calc(t_room *pass, t_ants *ants_move, t_ants *head)
{
	t_path	*path;
	int		line;

	path = pass->final_head;
	calc_amount_of_ants(pass, &path);
	head = path_setter(&ants_move, pass, &path, head);
	line = 1;
	while (head)
	{
		head = print_ants_move(head, pass, line++);
		if (!head)
		{
			ants_move = NULL;
			head = path_setter(&ants_move, pass, &path, head);
		}
		else
			path_setter(&ants_move, pass, &path, head);
	}
}