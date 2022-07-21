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

static void	create_ants(t_ants **ants_move, int ant, t_index *index)
{
	t_ants	*new;

	new = (t_ants *)malloc(sizeof(t_ants));
	if (!new)
		return ;
	new->ant = ant;
	new->move = index;
	new->next = NULL;
	if (*ants_move)
	{
		new->prev = *ants_move;
		(*ants_move)->next = new;
		*ants_move = (*ants_move)->next;
	}
	else
	{
		new->prev = NULL;
		*ants_move = new;
	}
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

static void	path_calc(int remain_ants, t_path **path)
{
	//ft_printf("path->prev: %p\n", (*path)->prev);
	while (*path && (*path)->prev)
	{
		//ft_printf("Here end: %p, remain_ants: %d, max_ants: %d\n", *path, remain_ants, (*path)->max_ants);
		//if (remain_ants <= (*path)->max_ants)
		//	break ;
		if (remain_ants > (*path)->prev->max_ants)
			break ;
		*path = (*path)->prev;
	}
}

static t_ants	*path_setter(t_ants **ants_move, t_room *pass, t_path **end, int add)
{
	t_path	*path;
	static t_ants	*head = NULL;
	static int	current_ant = 0;

	path = pass->final_head;
	if (add == FALSE)
	{
		ft_printf("ants: %d, current_ant: %d\n", pass->ants, current_ant);
		if (current_ant >= pass->ants)
			exit(0);
		path_calc(pass->ants - current_ant, end);
	}
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

void	solve(t_room *pass)
{
	int dif;
	t_path	*path;
	t_ants	*ants_move;
	t_ants	*head;
	t_path	*prev;

	path = pass->final_head;
	prev = NULL;
	while (path && path->next)
	{
		dif = diff_prev(pass, path->len) + ((path->next->len - path->len) * path->nbr);
		path->max_ants = dif + path->nbr;
		path->prev = prev;
		
		if (pass->ants <= path->max_ants)
			break ;
		prev = path;
		path = path->next;
	}
	path->prev = prev;
	ants_move = NULL;
	head = path_setter(&ants_move, pass, &path, TRUE);
	
	t_ants *temp;
	temp = head;
	int k;
	k = 0;
	while (temp)
	{
		//head = print_ants_move(head, pass);
		while (temp)
		{
			ft_printf("ants: %d		index: %d\n",temp->ant,temp->move->index);
			temp = temp->next;
		}
		temp = head;
		++k;
		if (k > 10)
			break ;
		path_setter(&ants_move, pass, &path, FALSE);
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

- need to make sorting function if our path struct happened to be not sorted in order of length

- need to make sure when we copy to final_head that it also sets path->move to path->move_head;

- check if we need to free more as we go eks links, used and distance as we go

*/
