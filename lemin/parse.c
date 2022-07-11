/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:11:51 by molesen           #+#    #+#             */
/*   Updated: 2022/07/11 11:48:59 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

const char	*ft_strlchr(const char *str, int c, int len)
{
	int	i;

	i = 0;
	if (str)
	{
		while (i < len)
		{
			if (str[i] == c)
			   return (&str[i]);
			++i;
		}
	}
	return (NULL);
}

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

int	funki(char *full, char *inside)
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

/*int	find_indx(t_room *pass, char *input, int count)
{
	int	i;
	int	hold;
	i = 0;
	if (ft_strlen_stop(input, '-') < ft_strlen_stop(input, '\n'))
		hold = ft_strlen_stop(input, '-');
	else
		hold = ft_strlen_stop(input, '\n');
	while (ft_strncmp(pass->rooms[i], input, hold) && i < count)
		++i;
	if (ft_strncmp(pass->rooms[i], input, hold))
			return (-1);
	return (i);
}*/

/*void	realloc_arr(t_room *pass, int k, int insert)
{
	int	j;
	int *temp;
	temp = NULL;
	j = 0;
	while (pass->links[k][j] >= 0)
		++j;
	temp = (int *) malloc((j + 2) * sizeof(int));
	if (!temp)
		//free exit
	j = 0;
	while (pass->links[k][j] >= 0)
	{
		temp[j] = pass->links[k][j];
		++j;
	}
	free(pass->links[k]);
	pass->links[k] = temp;
	pass->links[k][j] = insert;
	pass->links[k][j + 1] = -2;
}*/

void	initial_mal(t_room *pass, int k)
{
	if (!pass->links[k])
	{
		pass->links[k] = (int *) malloc(1 * sizeof(int));
		if (!pass->links[k])
			//free and exit
		pass->links[k][0] = -2; //only on first iteration
	}
}

int	addi_diff(char *start, char * finish) //undefined behaviour if finish is not infront of start
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

int	minus_newline(char **rooms, char *str, char *input, char *temp)
{
	int	j;
	int	count;
	char arr[ addi_diff(input, &temp[-1]) + 1];

	count = 0;
	j = 0;
	ft_bzero(arr, addi_diff(input, &temp[-1]) + 1);
	ft_strncpy(arr, input, addi_diff(input, &temp[-1]));
	//ft_printf("ARR %s\n", arr);
	if (!ft_strcmp(rooms[j], str))
		++j;
	while (rooms[j])
	{
		if (rooms[j] && !ft_strcmp(rooms[j], str))
			++j;
		if (rooms[j] && !ft_strcmp(arr, rooms[j]))
		{
			//ft_printf("FOUND %s  INPPUT %s\n", rooms[j], input);
			++count;
			break ;
		}
		++j;
	}
	return (count);
}

int	count_in(char *str, char *input, char **rooms)
{
	int	i;
	//int	hold;
	int	count;
	char	*temp;
	int	j;
	//int		wait = 0;

	i = 0;
	count = 0;
	while (input[i] != '\0')
	{
		ft_printf("COUNT %i ROOM %s\n", count, str);
		temp = ft_strnstr(&input[i], str, ft_strlen_stop(&input[i], '\n'));
		if (temp && ((temp[-1] == '\n' && temp[ft_strlen(str)] == '-') ||
			(temp[-1] == '-' && temp[ft_strlen(str)] == '\n')))
		{
			if (is_dash(&temp[ft_strlen(str)]) >= 1 && (temp[-1] == '\n' && 
				temp[ft_strlen(str)] == '-'))
			{
				ft_printf("H1\n");
				while (*temp != '-') //this will not work if - is in the name. use something to get to end of name
					++temp;
				if (*temp == '-')
					++temp;
				j = 0;
				if (!ft_strcmp(rooms[j], str))
					++j;
				while (rooms[j])
				{
					if (!ft_strcmp(rooms[j], str))
						++j;
					if (!ft_strncmp(temp, rooms[j], ft_strlen_stop(temp, '\n')))
					{
						++count;
						break;
					}
					++j;
				}
			}
			else if (funki(&input[i], temp) >= 1 && 
				(temp[-1] == '-' && temp[ft_strlen(str)] == '\n'))
			{
				ft_printf("H2\n");
				/*j = 0;
				if (!ft_strcmp(rooms[j], str))
					++j;
				while (rooms[j])
				{
					if (rooms[j] && !ft_strcmp(rooms[j], str))
						++j;
					if (rooms[j] && !ft_strncmp(&input[i], rooms[j], addi_diff(&input[i], &temp[-1])))
					{
						++count;
						break ;
					}
					++j;
				}*/
				count += minus_newline(rooms, str, &input[i], temp);

			}
			/*else
			{
				ft_printf("H3\n");
				++count;
			}*/
		}
		while (temp && ft_strnstr(&temp[1], str, ft_strlen_stop(&temp[1], '\n'))) //&& (temp[-1] != '\n' || temp[ft_strlen(str)] != '-') 
		{
				//ft_printf("H4\n");
			temp = ft_strnstr(&temp[1], str, ft_strlen_stop(&temp[1], '\n'));
		/*	if (temp[-1] == '-' && temp[ft_strlen(str)] == '\n')
				++count;*/
			count += minus_newline(rooms, str, &input[i], temp);
		}
		while (input[i] != '\n')
			++i;
		++i;
	}
	return (count);

}

void	match_route(char *room, char *input, int *links, t_room *pass)
{
	int	i;
	int	j;
	int k;
	char	*temp;

	i = 0;
	while (input[i] != '\0')
	{
		j = 0;
		temp = ft_strnstr(&input[i], room, ft_strlen_stop(&input[i], '\n'));
		if (temp)
		{
			/*if (temp[-1] == '\n' && temp[ft_strlen(room)] == '-')
			{
				j += ft_strlen(room);
				if (temp[j] == '-')
					++j;
				k = 0;
				if (!ft_strcmp(pass->rooms[k], room))
					++k;
				while (pass->rooms[k] && ft_strncmp(&temp[j], pass->rooms[k], ft_strlen_stop(&temp[j], '\n')))
				{
					++k;
					if (!pass->rooms[k])
					{
						exit (0); //and delete
					}
					if (!ft_strcmp(pass->rooms[k], room))
						++k;
				}
				j = 0;
				while (links[j] >= 0)
					++j;
				links[j] = k;
			}
			else if (temp[-1] == '-' && temp[ft_strlen(room)] == '\n')*/
			if ((temp[-1] == '\n' && temp[ft_strlen(room)] == '-') || (temp[-1] == '-' && temp[ft_strlen(room)] == '\n'))
			{
				k = 0;
				if (!ft_strcmp(pass->rooms[k], room))
					++k;
				while (pass->rooms[k] && !ft_strnstr(&input[i], pass->rooms[k], ft_strlen_stop(&input[i], '\n')))
				{
					++k;
					if (!pass->rooms[k])
						exit (0); //and delete
					if (!ft_strcmp(pass->rooms[k], room))
						++k;
				}
				j = 0;
				while (links[j] >= 0)
					++j;
				links[j] = k;
			}
			while (ft_strnstr(&temp[1], room, ft_strlen_stop(&temp[1], '\n'))) //&& (temp[-1] != '\n' || temp[ft_strlen(str)] != '-') 
			{
				temp = ft_strnstr(&temp[1], room, ft_strlen_stop(&temp[1], '\n'));
				if (temp && (temp[-1] == '-' && temp[ft_strlen(room)] == '\n'))
				{
					k = 0;
					if (!ft_strcmp(pass->rooms[k], room))
						++k;
					while (pass->rooms[k] && !ft_strnstr(&input[i], pass->rooms[k], ft_strlen_stop(&input[i], '\n')))
					{
						++k;
						if (!pass->rooms[k])
							exit (0); //and delete
						if (!ft_strcmp(pass->rooms[k], room))
							++k;
					}
					j = 0;
					while (links[j] >= 0)
						++j;
					links[j] = k;
				}
			}
		}
		while (input[i] != '\n' && input[i] != '\0')
			++i;
		if (input[i] == '\n')
			++i;
	}
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

int	create(t_room *pass, char *input)	
{
	int	count;
	int	i;
	int	j;
	int	k;
	int	hold;
	int p, m;

	i = 0;
	j = 1;
	k = 0;
	p = 0;
	m = 0;
	hold = -1;
	pass = (t_room *) malloc(sizeof(t_room));
	if (!pass)
		return (-1);
	count = parsing_phase(pass, &input);
	if (count == -1)
		return (-1);
	pass->rooms = NULL;
	pass->links = NULL;
	if (count > 0)
	{
		pass->rooms = (char **) malloc((count + 1) * sizeof(char *));
		pass->links = (int **) malloc((count + 1) * sizeof(int *));
		if (!pass->rooms || !pass->links)
		{
			//delete and return 
		}
		pass->rooms[count] = NULL;
		pass->links[count] = NULL;
		pass->rooms[0] = NULL;
		pass->rooms[count - 1] = NULL;
		pass->rooms[count] = NULL;
		while (input[i] != '\0')
		{
			if (hold == 5 || hold == 6)
			{
				if (hold == 5)
					hold = 0;//pass->rooms[0] = ft_strnew(ft_strlen_stop(&input[i], ' '));
				else
					hold = count - 1;//pass->rooms[count - 1] = ft_strnew(ft_strlen_stop(&input[i], ' '));
				if (pass->rooms[hold])
					exit (0); //free and exit
				pass->rooms[hold] = ft_strnew(ft_strlen_stop(&input[i], ' '));
				if (!pass->rooms[hold])
				{
					exit (0);
					//free exit
				}
				ft_strncat(pass->rooms[hold], &input[i], ft_strlen_stop(&input[i], ' '));
				ft_printf("%s-%i\n", pass->rooms[hold], hold);
				while (input[i] != '\n')
					++i;
			}
			hold = by_line(&input[i]);
			if (hold < 2 || hold == 5 || hold == 6)
			{
				while (input[i] != '\n')
					++i;
			}
			if (hold == 3)
			{
				pass->rooms[j] = ft_strnew(ft_strlen_stop(&input[i], ' '));
				if (!pass->rooms[j])
				{
					exit (0);
					//free exit
				}
				//pass->rooms[j + 1] = NULL;
				ft_strncat(pass->rooms[j++], &input[i], ft_strlen_stop(&input[i], ' '));
				ft_printf("%s-%i\n", pass->rooms[j - 1], j - 1);
				while (input[i] != '\n')
					++i;

			}
			else if (hold == 2)// && ft_strlchr(&input[i], '-', ft_strlen_stop(&input[i], '\n')))
			{
				if (duplicated(pass->rooms) == -1)
					return (-1); //free and exit
				j = 0;
				while (pass->rooms[j])
				{
					pass->links[j] = (int *) malloc((count_in(pass->rooms[j], &input[i], pass->rooms) + 1) * sizeof(int));
					if (!pass->links[j])
					{
						exit (0);
						//free exit
					}
					k = 0;
					while (k < count_in(pass->rooms[j], &input[i], pass->rooms) + 1)
						pass->links[j][k++] = -1;
					//ft_printf("kkkkkkkkkkkkk %s %i\n", pass->rooms[j], k -1);
					match_route(pass->rooms[j], &input[i], pass->links[j], pass);
					++j;
				}
				while (pass->rooms[p])
				{
					m = 0;
					ft_printf("room %s count [%i]\n", pass->rooms[p], count_in(pass->rooms[p], &input[i], pass->rooms));
					while (m <= count_in(pass->rooms[p], &input[i], pass->rooms))
						ft_printf("%i ", pass->links[p][m++]);
					ft_printf("\n");
					++p;
				}
				exit (0);
			}
			++i;
		}
	}
	return (1);
}
