/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:00:01 by jdavis            #+#    #+#             */
/*   Updated: 2022/07/14 15:51:08 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	absolute_path(t_room * pass)
{
	t_index	*tmp_indx;
	t_path 	*tmp_path;
	int		j;

	j = 1;
	while ( j <= length of longest path)
	{
		while (pass->path)
		{
			if (pass->path->len == j)
			{
				if (!pass->path->next || path->next->len > j)
					//keep the path we're currently on
					//break loop
				tmp_indx = path->move;
				tmp_path = path;
				tmp_path = tmp_path->next;
				while (tmp_path->len == j)
				{
					if (tmp_path->move->index == tmp_index->index)
					{

					}
				}
			}
		}
		++J;
	}
}
