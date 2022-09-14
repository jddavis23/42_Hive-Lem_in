/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrong_line_plus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:16:14 by jdavis            #+#    #+#             */
/*   Updated: 2022/09/14 17:57:08 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int	is_dash(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\n')
	{
		if (str[i] == '-')
			++count;
		++i;
	}
	return (count);
}

int	dash_in_section(char *full, char *inside)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (&full[i] != inside)
	{
		if (full[i] == '-')
			++count;
		++i;
	}
	return (count);
}

int	addi_diff(char *start, char *finish)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (&start[i] != finish)
	{
		++i;
		++count;
	}
	return (count);
}

int	wrong_line(t_room *pass, int r, int *j, char *input)
{
	int	i;

	if (r == 0 && *j == 0)
	{
		pass->line_check = (int *) malloc (pass->line * sizeof(int));
		if (!pass->line_check)
			return (free_connect(pass));
		i = 0;
		while (i < pass->line)
			pass->line_check[i++] = '\0';
	}
	if (pass->con_prev != pass->tmp_con->count)
		pass->line_check[*j] = 1;
	if (r == pass->end)
	{
		if (pass->line_check[*j] == 0 && input[0] != '#')
			return (free_connect(pass));
	}
	if (input[0] != '#')
		++(*j);
	pass->con_prev = pass->tmp_con->count;
	return (0);
}
