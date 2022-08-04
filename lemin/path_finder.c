/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_initialize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:31:10 by molesen           #+#    #+#             */
/*   Updated: 2022/07/19 10:31:12 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

/*	PRINT FUNCTIONS	*/

// static void	print_output(t_room *pass)
// {
// 	int	i;
// 	int	nbr;
// 	int	prev;

// 	i = 0;
// 	while (pass->links[0][i] >= 0)
// 	{
// 		nbr = pass->info[PATH][pass->links[0][i]];
// 		if (nbr != 0)
// 		{
// 			ft_printf("{green}PATH [%d] LEN[%d]{uncolor}\n", nbr, pass->info[LEN][pass->links[0][i]]);
// 			prev = pass->info[PREV][pass->links[0][i]];
// 			ft_printf("%s\n", pass->rooms[pass->links[0][i]]);
// 			while (prev > 0)
// 			{
// 				ft_printf("%s\n", pass->rooms[prev]);
// 				prev = pass->info[PREV][prev];
// 			}
// 		}
// 		++i;
// 	}
// 	i = 0;
// 	ft_printf("\n\n------------\nrooms path nbr:\n");
// 	while (i < pass->total)
// 	{
// 		ft_printf("%s: %d \n",pass->rooms[i], pass->info[PATH][i]);
// 		++i;
// 	}
// }

// static void	print_struct(t_room *pass)
// {
// 	t_conflict *temp;
// 	temp = pass->conf_head;
// 	while (temp)
// 	{
// 		temp->move = temp->move_head;
// 		ft_printf("\npath nbr[%d]: ", temp->nbr);
// 		while (temp->move)
// 		{
// 			ft_printf("room %s[%d] ", pass->rooms[temp->move->index], temp->move->index);
// 			temp->move = temp->move->next;
// 		}
// 		temp->move = temp->move_head;
// 		ft_printf("\n");
// 		temp = temp->next;
// 	}
// }

// /*	UPDATE VALUES	*/

// static void	update_values(t_room *pass, int i, int indx, int nbr)
// {
// 	pass->info[PATH][pass->links[indx][i]] = nbr;
// 	pass->info[PREV][pass->links[indx][i]] = indx;
// 	pass->info[LEN][pass->links[indx][i]] = pass->info[LEN][indx] + 1;
// 	pass->info[CURRENT][nbr - 1] = pass->links[indx][i];
// }

// /*	UPDATE CONNECTIONS	*/

// static int check_connect(t_room *pass, int indx, int nbr)
// {
// 	int i;
// 	int non;

// 	i = 0;
// 	if (!pass->info[CONNECT][indx])
// 		non = TRUE;
// 	else
// 		non = FALSE;
// 	while (pass->distance[pass->links[indx][i]] >= 0 && pass->links[indx][i] != -1)
// 	{
// 		if (non == TRUE)
// 			pass->info[CONNECT][indx]++;
// 		if (pass->links[indx][i] == 0)
// 		{
// 			pass->info[CURRENT][nbr - 1] = 0;
// 			pass->info[CONNECT][indx] = 0;
// 			return (FALSE);
// 		}
// 		i++;
// 	}
// 	return (TRUE);
// }

// // /*	NEED TO CHANGE MOVE INDEX	*/

// // static void	move_index(t_room *pass, int prev, int indx, int nbr)
// // {
// // 	int i;

// // 	if (check_connect(pass, indx, nbr) == FALSE)
// // 		return ;
// // 	i = 0;
// // 	if (pass->info[CONNECT][indx] == 2)
// // 	{
// // 		while (pass->distance[pass->links[indx][i]] > 0 && pass->links[indx][i] != -1)
// // 		{
// // 			if (pass->info[PATH][pass->links[indx][i]] == 0 && pass->links[indx][i] != prev && \
// // 				pass->info[PREV][pass->links[indx][i]] == 0)
// // 			{
// // 				update_values(pass, i, indx, nbr);
// // 				move_index(pass, indx, pass->links[indx][i], nbr);
// // 				return ;
// // 			}
// // 			++i;
// // 		}
// // 	}

// // }

// static int	all_paths_found(t_room *pass)
// {
// 	int	i;

// 	i = 0;
// 	while (i < pass->total)
// 	{
// 		if (pass->info[CURRENT][i] != 0)
// 		{
// 			return (FALSE);
// 		}
// 		++i;
// 	}
// 	return (TRUE);
// }

// // static void	delete_begin(t_conflict **temp)
// // {
// // 	t_i_conf	*pnt;
// // 	t_i_conf	*move;

// // 	pnt = (*temp)->move_head;
// // 	while (pnt && pnt->index != (*temp)->move->index)
// // 	{
// // 		move = pnt;
// // 		pnt = pnt->next;
// // 		free(move);
// // 	}
// // 	(*temp)->move_head = pnt;
// // }

// static t_i_conf	*ft_newindex(int index)
// {
// 	t_i_conf *new;

// 	new = (t_i_conf *)malloc(sizeof(t_i_conf));
// 	if (!new)
// 		return (NULL);
// 	new->index = index;
// 	new->i = 0;
// 	new->next = NULL;
// 	return (new);
// }

// static void	create_conflict(t_room *pass, int nbr)
// {
// 	t_conflict	*node;
// 	t_conflict	*temp;

// 	node = (t_conflict *)malloc(sizeof(t_conflict));
// 	if (!node)
// 		return ;
// 	node->nbr = nbr + 1;
// 	node->move = ft_newindex(pass->info[CURRENT][nbr]);
// 	node->move_head = node->move;
// 	node->next = NULL;
// 	if (!pass->conf_head)
// 	{
// 		pass->conf_head = node;
// 	}
// 	else
// 	{
// 		temp = pass->conf_head;
// 		while (temp->next)
// 		{
// 			temp = temp->next;
// 		}
// 		temp->next = node;
// 	}
// }

// static void	add_conflict(t_room *pass, int index, int nbr)
// {
// 	t_conflict	*temp;
// 	t_i_conf	*new;

// 	temp = pass->conf_head;
// 	while (temp && temp->nbr != nbr)
// 	{
// 		temp = temp->next;
// 	}
// 	new = NULL;
// 	if (temp && !temp->move)
// 	{
// 		temp->move = ft_newindex(index);
// 		temp->move_head = temp->move;
// 	}
// 	else if (temp)
// 	{
// 		new = ft_newindex(index);
// 		new->next = temp->move_head;
// 		temp->move_head = new;
// 	}
// }

// static void	delete_path(t_room *pass, int nbr)
// {
// 	int	i;

// 	i = 0;
// 	while (i < pass->total)
// 	{
// 		if (pass->info[PATH][i] == nbr)
// 		{
// 			pass->info[CURRENT][nbr - 1] = 0;
// 			pass->info[PREV][i] = 0;
// 			pass->info[PATH][i] = 0;
// 			pass->info[LEN][i] = 0;
// 		}
// 		++i;
// 	}
// }

// static void	removes_path_cur_pos(t_room *pass, int indx, int nbr)
// {
// 	int	i;

// 	i = 0;
// 	int change;
// 	int prev;
// 	change = indx;
// 	pass->info[CURRENT][pass->info[PATH][indx] - 1] = indx;
// 	prev = pass->info[PREV][indx];
// 	while (pass->links[change][i] != -1)
// 	{
// 		if (pass->info[PATH][pass->links[change][i]] == nbr && pass->links[change][i] != prev)
// 		{
// 			prev = pass->info[PREV][pass->links[change][i]];
// 			pass->info[PATH][pass->links[change][i]] = 0;
// 			pass->info[LEN][pass->links[change][i]] = 0;
// 			pass->info[PREV][pass->links[change][i]] = 0;
// 			change = pass->links[change][i];
// 			i = 0;
// 		}
// 		else
// 			++i;
// 	}
// }


void	path_finder(t_path **path, t_room *pass, int i)
{
	//int i;
	// int	total;
	
	// i = 0;
	// pass->info[PREV][pass->end] = -1;
	// pass->info[LEN][pass->end] = 1;
	// pass->conf_head = NULL;
	// // INITIALIZE BREATH FIRST AND VARIABLES
	// while (pass->distance[pass->links[pass->end][i]] > 0)
	// {
	// 	if (pass->info[PATH][pass->links[pass->end][i]] == 0 && pass->info[PREV][pass->links[pass->end][i]] == 0)
	// 	{
	// 		//update_values(pass, i, pass->end, i + 1);
	// 		//move_index(pass, pass->end, pass->links[pass->end][i], i + 1);
	// 		//create_conflict(pass, i);
	// 	}
	// 	++i;
	// }
	// total = i;
	// print_struct(pass);
	// print_output(pass);
	// while (all_paths_found(pass) == FALSE)
	// {
	// 	i = 0;
	// 	// BREATH FIRST TAKE ON STEP
	// 	while (i < total)
	// 	{
	// 		if (pass->info[CURRENT][i] != 0 && pass->info[CONNECT][pass->info[CURRENT][i]] != 2)
	// 		{

	// 		}
	// 		++i;
	// 	}
	// }
	// ft_printf("finished\n");
	// //print_struct(pass);
	// print_output(pass);
	if (!(*path) || pass || i)
	// 	++i;
	
	ft_printf("end found\n");
	//exit(0);
}
