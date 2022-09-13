/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:11:48 by jdavis            #+#    #+#             */
/*   Updated: 2022/09/13 18:15:28 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int	duplicated(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (!ft_strcmp(str[i], str[j]))
				return (-1);
			++j;
		}
		++i;
	}
	return (0);
}

static void	connec_to_links(t_room *pass, int j)
{
	int	k;
	int	count;
	t_connect *temp;

	k = 0;
	count = pass->tmp_con->count;
	pass->tmp_con = NULL;
	while (k < count)
	{
		pass->links[j][k] = -1;
		if (pass->head_con->current_room != -1)
		{
			pass->links[j][k] = pass->head_con->current_room;
		}
		temp = pass->head_con->next;
		free(pass->head_con);
		pass->head_con = temp;
		k++;
	}
}

int	create_links(t_room *pass, t_input **build, int i)
{
	int	j;
	//char **input = NULL; //just for error function

	//exit (0);
	if (duplicated(pass->rooms) == ERROR)
		return (error_free(pass, build, 0, FALSE));
	j = 0;
	while (pass->rooms[j])
	{
		if (create_connect(pass, 0) == -1)
			return (error_free(pass, build, j, FALSE)); //CHANGE INPUT TO FREE BUILD AND COTENTS
		if (count_in(j, &(((*build)->input)[i]), pass) == -1)
			return (error_free(pass, build, j, FALSE));
		pass->links[j] = (int *) malloc((pass->tmp_con->count) * sizeof(int));
		if (!pass->links[j])
			return (error_free(pass, build, j, FALSE));
		connec_to_links(pass, j);
		++j;
	}
	return (TRUE);
}