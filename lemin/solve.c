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

static t_ants	*path_setter(t_ants **ants_move, t_room *pass, t_path **end, t_ants *head)
{
	t_path	*path;
	static int	current_ant = 0;

	path = pass->final_head;
	if (head && current_ant < pass->ants)
	{
		//ft_printf("ants: %d, current_ant: %d\n", pass->ants, current_ant);
		// if (current_ant >= pass->ants)
		// 	exit(0);
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

t_ants	*print_ants_move(t_ants *head,t_room *pass)
{
	t_ants	*send;
	t_ants	*temp;
	t_ants	*prev;
	int		i;
	static int	line = 1;

	send = head;
	i = 0;
	if (pass->row == TRUE)
		ft_printf("{purple}row: %d{uncolor}\n", line);
	++line;
	while (head)
	{
		ft_printf("L%d-%s", head->ant, pass->rooms[head->move->index]);
		if (head->move->index == pass->end)
		{
			prev = head->prev;
			temp = head->next;
			if (head)
				free(head);
			head = temp;
			if (prev)
				prev->next = head;
			if (head)
			{
				head->prev = prev;
			}
			if (i == 0)
			{
				i = -1;
				send = head;
			}
		}
		else
		{
			head->move = head->move->next;
			head = head->next;
		}
		if (!head)
			ft_printf("\n");
		else
			ft_printf(" ");
		++i;
	}
	return (send); //careful what returning, could have changed
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
	head = NULL;
	head = path_setter(&ants_move, pass, &path, head);
	t_ants *temp;
	temp = head;
	int k;
	k = 0;
	while (head)
	{
		head = print_ants_move(head, pass);
		if (!head)
		{
			ants_move = NULL;
			head = path_setter(&ants_move, pass, &path, head);
		}
		else
			path_setter(&ants_move, pass, &path, head);
	}
}

/*

NON SOLVER STUFF that need to be done

- need to make sorting function if our path struct happened to be not sorted in order of length

Jeffs help is needed to discuss the logic here
- do we want to collect the shortest path also? have amount of ants determine what kind of combo of paths we priorities

- adding bonusses

	-h : help  message
	-l : leaks check
	-m/lines : prints out amount of move pr line/amount of lines
	-p : prints amount of paths selected before printing the final movement of the ants
	-t : bonus that displays the time it took to run the program

*/
