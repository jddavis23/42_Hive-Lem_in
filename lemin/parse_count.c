/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:20:20 by jdavis            #+#    #+#             */
/*   Updated: 2022/07/11 13:20:25 by jdavis           ###   ########.fr       */
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

int	addi_diff(char *start, char *finish) //undefined behaviour if finish is not infront of start
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
static int	ft_strcmp_stop(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\n' && (str1[i] != '\0' || str2[i] != '\0'))
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

static int	find_connec_room(t_room *pass, int r, char **arr, int choice)//, char *temp)
{
	int	j;
	int	str_len;
	//int	stop;

	str_len = ft_strlen(pass->rooms[r]) + 1;
	//stop = ft_strlen_stop(&(*arr)[str_len], '\n');
	j = 0;
	if (j == r)
		++j;
	while (pass->rooms[j])
	{
		if (j == r)
			++j;
		if (choice == 0 && pass->rooms[j] && !ft_strcmp(*arr, pass->rooms[j]))
		{
			create_connect(pass, j);
			free(*arr);
			return (1);
		}
		else if (choice == 1 && pass->rooms[j] && !ft_strcmp_stop(&(*arr)[str_len], pass->rooms[j]))//!ft_strncmp(&(*arr)[str_len], pass->rooms[j], stop))
		{
			create_connect(pass, j);
			return (1);
		}
		++j;
	}
	if (choice == 0)
		free(*arr);
	return (-1);
}

static int	room_finder(t_room *pass, int r, int j)
{
	if (j == r)//compare index
		++j;
	while (pass->rooms[j])
	{
		if (j == r)
			++j;
		if (pass->rooms[j] && ft_strstr(pass->rooms[j], pass->rooms[r]))
			break ;
		else if (ft_strstr(pass->rooms[r], pass->rooms[j]))
			return (-1);
		++j;
	}
	return (j);
}

static int	mnl_found_room(t_room *pass, int *i, char *input, char *temp)
{
	char	*arr;

	if (pass->rooms[*i] && !ft_strncmp(input, pass->rooms[*i], ft_strlen(pass->rooms[*i])))
	{
		arr = ft_strnew(addi_diff(input, &temp[-1]));
		if (!arr)
		{
			*i = ERROR;
			return (ERROR);
		}
		ft_strncpy(arr, input, addi_diff(input, &temp[-1]));
		if (ft_strcmp(arr, pass->rooms[*i]))
		{
			free(arr);
			arr = NULL;
			return (TRUE);
		}
		free(arr);
		arr = NULL;
	}
	return (FALSE);
}

static int	mnl_helper(t_room *pass, int *j, char *input, char *temp)
{
	static int	flag = 0;
	int			i;
	int			ret;

	i = 0;
	if (pass->rooms[*j] && temp && temp[-1] == '-' && temp[ft_strlen(pass->rooms[*j])] == '\n')
	{
		++flag;
		if (pass->rooms[i] && !ft_strcmp(pass->rooms[i], pass->rooms[*j]))
			++i;
		while (pass->rooms[i])
		{
			if (pass->rooms[i] && !ft_strcmp(pass->rooms[i], pass->rooms[*j]))
				++i;
			ret = mnl_found_room(pass, &i, input, temp);
			if (i == ERROR || ret == TRUE)
				break ;
			++i;
		}
	}
	if (pass->rooms[*j])
		++(*j);
	if (!flag)
		return (-1);
	return (i);
}

int	free_connect(t_room *pass)
{
	t_connect *tp;

	while (pass->head_con)
	{
		tp = pass->head_con->next;
		free(pass->head_con);
		pass->head_con = tp;
	}
	return (ERROR);
}

static int	loop_through_rooms(t_room *pass, int r, char *input, char *temp)
{
	char	*hold;
	int		i;
	int		j;

	hold = temp;
	i = -1;
	j = 0;
	while (pass->rooms[j])
	{
		j = room_finder(pass, r, j);
		if (j == -1)
			return (2); //not an error. returning so show that str is on the other side of search
		temp = NULL;
		if (pass->rooms[j])
			temp = ft_strstr(input, pass->rooms[j]);
		i = mnl_helper(pass, &j, input, temp);
	}
	if ((i != -1 && !pass->rooms[i]) || (i == -1 && hold[-1] == '-'))
		return (free_connect(pass));
	return (1);
}

static int	minus_newline(t_room *pass, int r, char *input, char *temp)
{
	int		j;
	char	*arr;

	j = addi_diff(input, &temp[-1]);
	arr = ft_strnew(j);
	if (!arr)
		return (-1);
	ft_strncpy(arr, input, j);
	if (find_connec_room(pass, r, &arr, 0) == 1)
		return (1);
	else 
	{
		arr = NULL;
		if (loop_through_rooms(pass, r, input, temp) == ERROR)
			return (ERROR);
	}
	if (arr)
		free(arr);
	return (2);
}

static int	nlm_helper(t_room *pass, int *j, char *help)
{
	int	i;

	if (pass->rooms[*j] && help && help[-1] == '\n' && help[ft_strlen(pass->rooms[*j])] == '-')
	{
		i = 0;
		if (pass->rooms[i] && !ft_strcmp(pass->rooms[i], pass->rooms[*j]))
			++i;
		while (pass->rooms[i])
		{
			if (pass->rooms[i] && !ft_strcmp(pass->rooms[i], pass->rooms[*j]))
				++i;
			if (pass->rooms[i] && !ft_strncmp(&help[ft_strlen(pass->rooms[*j]) + 1], pass->rooms[i], ft_strlen_stop(&help[ft_strlen(pass->rooms[*j]) + 1], '\n')))
				return (i);
			++i;
		}
	}
	if (pass->rooms[*j])
		++(*j);
	return (pass->total);
}

static int	newline_minus(t_room *pass, int r, char *temp, char *input)
{
	int		j;
	int		i;

	if (find_connec_room(pass, r, &temp, 1) == 1)
		return (1);
	else
	{
		j = 0;
		i = 0;
		while (pass->rooms[j])
		{
			j = room_finder(pass, r, j);
			if (j == -1)
				return (2); //not an error. returning so show that str is on the other side of search
			if (pass->rooms[j])
				temp = ft_strnstr(input, pass->rooms[j], ft_strlen(pass->rooms[j]));
			i = nlm_helper(pass, &j, temp);
			if (pass->rooms[i])
				break;
		}
		if (!pass->rooms[i] || !pass->rooms[j])
			return (free_connect(pass));
	}
	return (2);
}

static int	found_or_not(t_room *pass, int r, char *temp, char *input)
{
	int	str_len;

	if (temp && input[0] != '#')
	{
		str_len = ft_strlen(pass->rooms[r]);
		if (((temp[-1] == '\n' && temp[str_len] == '-') ||
			(temp[-1] == '-' && temp[str_len] == '\n')))
		{
			if (is_dash(&temp[str_len]) >= 1 && (temp[-1] == '\n' && 
				temp[str_len] == '-'))
				return (newline_minus(pass, r, temp,  input));
			else if (dash_in_section(input, temp) >= 1 && 
				(temp[-1] == '-' && temp[str_len] == '\n'))
				return (minus_newline(pass, r, input, temp));
		}
	}
	return (0);
}

int	count_in(int r, char *input, t_room *pass)
{
	int		i;
	char	*temp;
	int		diff;
	int		stop;
	int	count = 0;

	i = 0;
	while (input[i] != '\0')
	{
		temp = ft_strnstr(&input[i], pass->rooms[r], ft_strlen_stop(&input[i], '\n'));
		diff = found_or_not(pass, r, temp, &input[i]); //maybe get rid
		if (diff == -1)
			return (-1);
		if (temp && input[i] != '#')
		{
			stop = ft_strlen_stop(&temp[1], '\n');
			while (ft_strnstr(&temp[1], pass->rooms[r], stop) && diff == 2) //&& (temp[-1] != '\n' || temp[ft_strlen(pass->rooms[r])] != '-') 
			{
				temp = ft_strnstr(&temp[1], pass->rooms[r], stop);
				if (temp[-1] == '-' && temp[ft_strlen(pass->rooms[r])] == '\n')
				{
					if (minus_newline(pass, r, &input[i], temp) == -1)
						return (-1);
				}
			}
		}
		else
		{
			if (!ft_strncmp(&input[i], "##start\n", 8))
				return (free_connect(pass));
			else if (!ft_strncmp(&input[i], "##end\n", 6))
				return (free_connect(pass));
		}
		while (input[i] != '\n')
			++i;
		++i;
	}
	if (count++ == 1)
		exit(0);
	return (0);
}
