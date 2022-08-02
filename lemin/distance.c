/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:12:51 by jdavis            #+#    #+#             */
/*   Updated: 2022/07/12 16:53:09 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void    recurs(t_room *pass, int **links, int dist, int indx)
{
    int    i;
    int    j;
	static int k = 0;

    j = 0;
    i = 0;
    while (links[indx][j] >= 0)
    {
        if (links[indx][j] == pass->end)
        {
            return ;
        }
        ++j;
    }
    if (j == 1 && indx != 0)
        return ;
    while (links[indx][i] >= 0)
    {
        //if (indx == 1)
        //    exit (0);
        if (links[indx][i] == indx)
            ++i;
        if (links[indx][i] == 0)
            ++i;
        if (links[indx][i] < 0)
            return ;
        while (links[indx][i] > 0 && dist >= pass->distance[links[indx][i]] && pass->distance[links[indx][i]] != 0) //double check
            ++i;
        if (links[indx][i] <= 0)
            return ;
        if (dist + 1 < pass->distance[links[indx][i]] && pass->distance[links[indx][i]] != 0)
            pass->distance[links[indx][i]] = dist + 1;
        else if (dist + 1 > pass->distance[links[indx][i]] && pass->distance[links[indx][i]] == 0)
            pass->distance[links[indx][i]] = dist + 1;
        if (links[indx][i] != 0)
        {
            recurs(pass, pass->links, pass->distance[links[indx][i]], links[indx][i]);
        }
        if (k)
		{
			j = 0;
			while (pass->links[indx][j] != -1)
				++j;
			if (j < 3)
				pass->distance[indx] = -1;
			else
				--k;
		}
		++i;
    }
}

/*void	recurse_check(t_room *pass, int **links, int dist, int indx, int prev)
{
	int	i;
	int	j;
	static int	found = FALSE;

	j = 0;
	i = 0;
	while (links[indx][j] >= 0)
	{
		if (links[indx][j] == pass->end)
		{
			//ft_printf("HERE\n");
			return ;
		}
		++j;
	}
	if (j == 1 && indx != 0)
	{
		//ft_printf("He1222\\n");
		return ;
	}
	while (links[indx][i] >= 0)
	{
		if (links[indx][i] == 0 || links[indx][i] == prev)
			++i;
		if (links[indx][i] < 0)
		{
			//ft_printf("gback back\n");
			return ;
		}
		//ft_printf("rooom current: %s, next: %s\n", pass->rooms[indx], pass->rooms[links[indx][i]]);
		// while (links[indx][i] >= 0 && pass->distance[links[indx][i]] != 0) //double check
		// 	++i;
		// if (links[indx][i] < 0)
		// {
		// 	ft_printf("go back\n");
		// 	return ;
		// }
		if (pass->distance[links[indx][i]] >= dist)
		{
			recurse_check(pass, pass->links, pass->distance[links[indx][i]], links[indx][i], indx);
		}
		else
			found = TRUE;
		if (pass->distance[indx] == pass->distance[links[indx][i]])
			found = FALSE;
		if (found == TRUE)
		{
			pass->distance[indx] = pass->distance[links[indx][i]];
			//ft_printf("Heredfefe\n");
			return ;
		}
		++i;
	}
}*/

void	distance(t_room *pass)
{
	int	i;

	i = 0;
	pass->distance = (int *) malloc(pass->total * sizeof(int));
	if (!pass->distance)
	{
		//free evrything
		exit (0);
	}
	while (i < pass->total)
		pass->distance[i++] = 0;
	recurs(pass, pass->links, 0, 0);
	pass->distance[pass->end] = pass->total;
	i = 0;
	ft_printf("\n");
	while (i < pass->total)
	{
		ft_printf("room %s  distance %i\n", pass->rooms[i], pass->distance[i]);
		++i;
	}
	ft_printf("\n");
	exit(0);
}
