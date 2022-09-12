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

/*	mallocs and create the ants movement through the rooms	*/

void	create_ants(t_ants **ants_move, int ant, t_index *index)
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

/*	logic when ant has reached the last room	*/

static void	end_room_reached(t_ants **head, t_ants **send, int *i)
{
	t_ants	*temp;
	t_ants	*prev;

	prev = (*head)->prev;
	temp = (*head)->next;
	if (*head)
		free(*head);
	*head = temp;
	if (prev)
		(prev)->next = *head;
	if (*head)
		(*head)->prev = prev;
	if (*i == 0)
	{
		*i = -1;
		*send = *head;
	}
}

/*	prints one row of moving ants each time function is called	*/

t_ants	*print_ants_move(t_ants *head, t_room *pass, int line)
{
	t_ants		*send;
	int			i;

	send = head;
	i = 0;
	if (pass->print_row == TRUE)
		ft_printf("{purple}row: %d{uncolor}\n", line);
	while (head)
	{
		if (!pass->print_count)
			ft_printf("L%d-%s", head->ant, pass->rooms[head->move->index]);
		if (head->move->index == pass->end)
			end_room_reached(&head, &send, &i);
		else
		{
			head->move = head->move->next;
			head = head->next;
		}
		if (!head && !pass->print_count)
			ft_printf("\n");
		else if (!pass->print_count)
			ft_printf(" ");
		++i;
	}
	return (send); //careful what returning, could have changed
}

void	print_count(int	print_count, int line)
{
	if (print_count)
	{
		ft_printf("---- FINAL ROW COUNT ----\n");
		ft_printf("{purple}row: %d{uncolor}\n", line);
	}
}

/*	starting logic of printing ants moving and takes care of edge case	*/

void	solve(t_room *pass, t_input **build)
{
	t_ants	*ants_move;
	t_ants	*head;
	
	head = NULL;
	ants_move = NULL;
	// if start is connected to the end move all ants at the same time
	if (!pass->print_count)
		ft_printf("%s\n", (*build)->input);
	if (pass->final_head->len == 1)
	{
		int current_ant = 0;
		while (current_ant < pass->ants)
		{
			create_ants(&ants_move, current_ant++, pass->final_head->move_head);
			if (!head)
				head = ants_move;
		}
		head = print_ants_move(head, pass, 1);
		print_count(pass->print_count, 1);
	}
	else
		solve_calc(pass, ants_move, head);
	if (pass->print_len || pass->print_paths)
		printf_struct(pass);
	error_path(pass, &(*build), FALSE); //need to make sure everything
}
