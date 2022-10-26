/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:11:48 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/25 11:56:43 by jdavis           ###   ########.fr       */
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

int	create_links(t_room *pass, t_input **build, int i)
{
	int	j;

	if (duplicated(pass->rooms) == ERROR)
		return (error_free(pass, build, 0, FALSE));
	j = 0;
	if (create_connect(pass, 0, 0) == -1)
		return (error_free(pass, build, j, FALSE));
	if (count_in(&(((*build)->input)[i]), pass) == -1)
		return (error_free(pass, build, j, FALSE));
	return (TRUE);
}
