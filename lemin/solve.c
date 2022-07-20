/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:59:22 by jdavis            #+#    #+#             */
/*   Updated: 2022/07/20 12:10:08 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*void	picking_struct(t_path *path, int not_here)
{
	int	i;

	i = 0;
}*/

static void	create_ants(t_ants **ants_move, int ant, t_index *index)
{
	t_ants	*new;

	new = (t_ants *)malloc(sizeof(t_ants));
	if (!new)
		return ;
	new->ant = ant;
	new->index = index;
	new->next = NULL;
	if (*ants_move)
	{
		ft_printf("HEREIEJRIEJRI2222222\n");
		
		(*ants_move)->next = new;
		*ants_move = (*ants_move)->next;
	}
	else
	{
		ft_printf("HEREIEJRIEJRI\n");
		*ants_move = new;
	}
}

static t_ants	*path_setter(t_ants **ants_move, t_room *pass, int path_count)
{
	t_path	*path;
	static t_ants	*head = NULL;
	static int	current_ant = 1;
	int		i;

	i = 0;
	path = pass->final_head;
	while (path && i < path_count && current_ant <= pass->ants)
	{
		create_ants(ants_move, current_ant, path->move_head);
		ft_printf("ants->ant: %d	ants->path: %p\n", (*ants_move)->ant, (*ants_move)->index);
		if (!head)
		 	head = *ants_move;
		current_ant++;
		path = path->next;
		++i;
	}
	return (head);
}

static int	diff_prev(t_room *pass, int len)
{
	t_path *path;
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

void	solve(t_room *pass)
{
	int	i;
	/*
	int	first_len;
	t_path *find;

	i = 1;
	find = pass->final_head;
	first_len = find->len;
	if (pass->ants <= first_len && (i < find->nbr || pass->ants > i))
	{
		find = find->next;
		while (find)
		{
			ft_printf("%i  %i   %i   %i\n", find->len, first_len, i, find->nbr);
			if (find->len > first_len || i >= pass->ants)
				break ;
			++i;
			find = find->next;
		}
		//only use that path
	}
	else if (pass->ants > first_len)
	{
		find = find->next;
		while (find)
		{
			ft_printf("%i  %i   %i   %i\n", find->len, pass->ants, i, find->nbr);
			if (find->len > pass->ants || i >= pass->ants)
				break ;
			++i;
			find = find->next;
		}
	}
	ft_printf("amount of paths chosen %i\n", i);
	*/
	int dif;
	int	ants;
	//int current_len;
	//int	next_len;
	//int	selected_paths;
	t_path	*path;
	t_ants	*ants_move;
	t_ants	*head;

	i = 1;
	path = pass->final_head;
	while (path && path->next)
	{
		dif = diff_prev(pass, path->len) + ((path->next->len - path->len) * i);
		ants = dif + i;
		ft_printf("dif prev: %d, next half: %d\n", diff_prev(pass, path->len), ((path->next->len - path->len) * i));
		ft_printf("i: %d, ants: %d, dif: %d\n", i, ants, dif);
		if (pass->ants <= ants)
			break ;
		path = path->next;
		++i;
	}
	//int	current_ant;
	ft_printf("paths: %i\n", i);
	//current_ant = 1;
	ants_move = NULL;//printf error malloc message
	head = path_setter(&ants_move, pass, i);
	ft_printf("head->>ant: %d\n", head->ant);
	while (head)
	{

		path_setter(&ants_move, pass, i);
		while (head)
		{
			ft_printf("ants: %d		index: %d\n", head->ant, head->index->index);
			head = head->next;
		}
		break ;
		//printing function
		// uses delete function if ant reached the end

		//logic function
		// create_ants
	}
}

/*

Logic of printing

We have amount of selected paths.


struct ants_movement
{
	int		ant;
	t_path	*path;// or t_index index? or *path->move
	ants_movement *next;
}

would need:
- delete function: that deletes current path if the current path has printed the 'end' room
	needs to point correctly to next room when ant is being taken out
- printing function: loops through struct and prints information to line ending all of printing with newline ex.
	- path->move will have been set to head before function call.
	- needs to end with having the path->move shifted to the next room OR if printed last room delete current ant from struct.
	prints statement should be put in a while loop to print all ants in struct
	ex
	while (ants_movement)
		ft_printf("L%d-%s", ants_movement->ant, pass->rooms[t_path->move->index])
		// delete current ants_movement if just printed the last room
		// OR
		// shift it to point to the next room
		if last printed end with '\n' else end with ' '
		ants_movement = ants->movement->next;//go to next ant
- create function: quickly builds and or adds ants to current struct
	always add struct to the end (aka new element pointed to NULL)
	insert information about ant and path to function call
- logic function: logic that returns which path to send a specific ant down
	continue to add ants to struct until all 'active' ants have been sent off or there are no more available paths
	
	while (i < amount of paths && current_ant <= total_ants)
		ants_movement->ant = current_ant
		assign ants_movement->path = path
		path = path->next
		current_ant++


keep looping until everything is printed(while struct of ants_movement is true):
	if there are ants remaining and free rooms remaining
		logic function
			uses create function
	printing function
		uses delete function if ant reached the end




NON SOLVER STUFF that need to be done

need to make sorting function if our path struct happened to be not sorted in order of length

*/
