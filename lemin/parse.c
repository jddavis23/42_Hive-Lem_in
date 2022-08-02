/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:20:42 by jdavis            #+#    #+#             */
/*   Updated: 2022/07/11 13:20:44 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

int	by_line(char *input)
{
	int	flag;
	int	count;
	int	i;

	i = 0;
	count = 0;
	flag = 1;
	if (!ft_strncmp(&input[i], "##start", 7))
		return (5);
	else if (!ft_strncmp(&input[i], "##end", 5))
		return (6);
	else if (input[i] == '#')
		return (-1);
	if (!ft_strlchr(input, ' ', ft_strlen_stop(input, '\n')) && ft_strlchr(input, '-', ft_strlen_stop(input, '\n')))
		return (2);
	while (input[i] != '\n' && input[i] != '\0')
	{
		if (flag && input[i] != ' ')
		{
			 flag = 0;
			 ++count;
		}
		if (input[i] == ' ')
			flag = 1;
		++i;
	}
	return (count);
}

int	duplicated(char **str)
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

static void	set_to_null(t_room *pass)
{
	int	i;

	i = 0;
	while (i < pass->total)
	{
		pass->rooms[i] = NULL;
		pass->links[i] = NULL;
		++i;
	}
	pass->rooms[i] = NULL;
}

int	create(t_room *pass, char **input)	
{
	int	i;
	int	j;
	int	k;
	int	hold;
	int p, m;
	int	count;

	i = 0;
	j = 1;
	k = 0;
	p = 0;
	m = 0;
	hold = ERROR;
	pass->rooms = NULL;
	pass->links = NULL;
	pass->distance = NULL;
	//pass->used = NULL;
	pass->total = file_save(pass, input);
	pass->end = pass->total - 1;
	if (pass->total == ERROR)
		return (error_free(pass, *input, 0, TRUE));
	if (pass->total > 0)
	{
		pass->rooms = (char **) malloc((pass->total + 1) * sizeof(char *));
		pass->links = (int **) malloc(pass->total * sizeof(int *));
		if (!pass->rooms || !pass->links)
		{
			ft_printf("here\n");
			return (error_free(pass, *input, 0, FALSE));
		}
		set_to_null(pass);
		while ((*input)[i] != '\0')
		{
			if (hold == 5 || hold == 6)
			{
				if (hold == 5)
					hold = 0;//pass->rooms[0] = ft_strnew(ft_strlen_stop(&input[i], ' '));
				else
					hold = pass->total - 1;//pass->rooms[count - 1] = ft_strnew(ft_strlen_stop(&input[i], ' '));
				if (pass->rooms[hold])
				{
					ft_printf("here6\n");
					return (error_free(pass, *input, 0, FALSE));
				}
				pass->rooms[hold] = ft_strnew(ft_strlen_stop(&((*input)[i]), ' '));
				if (!pass->rooms[hold])
				{
					ft_printf("here2\n");
					return (error_free(pass, *input, 0, FALSE));
				}
				ft_strncat(pass->rooms[hold], &((*input)[i]), ft_strlen_stop(&((*input)[i]), ' '));
				//ft_printf("%s-%i\n", pass->rooms[hold], hold);
				while ((*input)[i] != '\n')
					++i;
			}
			hold = by_line(&((*input)[i]));
			if (hold < 2 || hold == 5 || hold == 6)
			{
				while ((*input)[i] != '\n')
					++i;
			}
			if (hold == 3)
			{
				pass->rooms[j] = ft_strnew(ft_strlen_stop(&((*input)[i]), ' '));
				if (!pass->rooms[j])
				{
					ft_printf("here3\n");
					return (error_free(pass, *input, 0, FALSE));
				}
				//pass->rooms[j + 1] = NULL;
				ft_strncat(pass->rooms[j++], &((*input)[i]), ft_strlen_stop(&((*input)[i]), ' '));
				//ft_printf("%s-%i\n", pass->rooms[j - 1], j - 1);
				while ((*input)[i] != '\n')
					++i;
			}
			else if (hold == 2)// && ft_strlchr(&input[i], '-', ft_strlen_stop(&input[i], '\n')))
			{
				if (duplicated(pass->rooms) == ERROR)
				{
					ft_printf("here5\n");
					return (error_free(pass, *input, 0, FALSE));
				}
				j = 0;
				while (pass->rooms[j])
				{
					count = count_in(pass->rooms[j], &((*input)[i]), pass->rooms);
					if (count == -1)
						exit (0);
					pass->links[j] = (int *) malloc((count + 1) * sizeof(int));
					if (!pass->links[j])
					{
						ft_printf("here4\n");
						return (error_free(pass, *input, j, FALSE));
					}
					k = 0;
					while (k < count + 1)
						pass->links[j][k++] = -1;
					match_in(pass->rooms[j], &((*input)[i]), pass, j);
					//match_in(pass->rooms[j], &((*input)[i]), pass->rooms, j, pass);
					
					++j;
				}
				int nn;
				nn = 0;
				while (pass->rooms[nn])
				{
					k = 0;
					ft_printf("Room %s: ", pass->rooms[nn]);
					while (pass->links[nn][k] >= 0)
					{
						ft_printf(" %s", pass->rooms[pass->links[nn][k++]]);
					}
					ft_printf("\n");
					++nn;
				}
				// while (pass->rooms[p])
				// {
				// 	m = 0;
				// 	if (p == 0)
				// 	{
				// 		ft_printf("room %s count [%i]\n\n", pass->rooms[p], count);
				// 		while (pass->links[p][m] >= 0)
				// 		{
				// 			ft_printf("\nroom %s{\n", pass->rooms[pass->links[p][m]]);
						
				// 			//ft_printf("\n%d { ", pass->links[m][]);
				// 			int q = 0;
				// 			while (pass->links[pass->links[p][m]][q] != -1)
				// 			{
				// 				ft_printf("%d ", pass->links[pass->links[p][m]][q]);
				// 				q++;
				// 			}
				// 			m++;
				// 			ft_printf("}");
				// 		}
				// 		ft_printf("\n");
				// 	}
				// 	++p;
				// }
				
				return (0);
			}
			++i;
		}
	}
	
	return (1);
}
