/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:00:01 by jdavis            #+#    #+#             */
/*   Updated: 2022/07/15 12:01:57 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*int	compare_paths(t_index *first, t_index *second)
{
	t_index *head_first;
	t_index *head_second;
	int		sim;

	head_second = second;
	head_first = first;
	sim = -1;
	while (first)
	{
		while (second)
		{
			if (first->index == second->index)
			{
				sim = first->index;
				break ;
			}
			second = second->next;
		}
		if (sim != -1)
			break ;
		first = first->next;
	}
	if (sim == -1)
	{
		//return a value to indicate keep both
	}


}

int	keep_and_erase(int p_nbr, t_path *path, t_path *head)
{
	t_path *temp;
	int		sim;

	temp = path;
	while (head && (head->len != path->len || head->nbr != p_nbr))
		head = head->next;
	//condition to exit if head is not true
	sim = compare_paths(path->move, head->move);
	return (sim);
}

void	delete_sim(t_room *pass, int t_len, int	delete)
{
	t_path *head;
	t_path *prev_head;
	t_path	*temp;
	t_index	*home;

	head = pass->head;
	prev_head = NULL;
	while (pass->head)
	{
		home = pass->head->move;
		while (pass->head->move)
		{
			if (pass-head->move->index == delete && pass->head->len > t_len)
			{
				temp = pass->head->next;
				free(pass->head); //and everything inside
				if (!prev_head)
					pass->head = temp;
				else
					prev_head->next = temp;
			}	
			pass->head->move = pass->head->move->next;
		}
		pass->head->move = home;
		prev_head = pass->head;
		pass->head = pass->head->next;
	}
	pass->head = head;
}

void	absolute_path(t_room * pass)
{
	t_index	*tmp_indx;
	t_path 	*tmp_path;
	int		j;
	int		ret;

	j = 1;
	ret = -1;
	tmp_path = pass->head;
	while ( j <= length of longest path)
	{
		while (tmp_path->path)
		{
			if (j == tmp_path->len)
				ret = keep_and_erase(tmp_path->nbr, tmp_path, pass->head);
			if (ret != -1)
			{
				delete_sim(pass, j, ret);
				ret = -1;
			}
			tmp_path = tmp_path->next;
		}
		tmp_path = pass->head;
		++J;
	}
}*/

