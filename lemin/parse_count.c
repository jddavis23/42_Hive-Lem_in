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
# include <string.h>

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

static int	find_connec_room(t_room *pass, char *str, char **arr, int choice)//, char *temp)
{
	int	j;

	j = 0;
	if (!ft_strcmp(pass->rooms[j], str))
		++j;	
	while (pass->rooms[j])
	{
		if (pass->rooms[j] && !ft_strcmp(pass->rooms[j], str))
			++j;
		if (choice == 0 && pass->rooms[j] && !ft_strcmp(*arr, pass->rooms[j]))
		{
			create_connect(pass, j);
			free(*arr);
			return (1);
		}
		else if (choice == 1 && !ft_strncmp(&(*arr)[ft_strlen(str) + 1], pass->rooms[j], ft_strlen_stop(&(*arr)[ft_strlen(str) + 1], '\n')))
		{
			create_connect(pass, j);
			return (1);
		}
		++j;
	}
	//if (*arr)//choice == 0)
	//	free(*arr);
	//ft_printf("%s\n", *arr);
	if (choice == 0)
		free(*arr);
	return (-1);
}

static int	room_finder(t_room *pass, char *str, int j)
{
	if (pass->rooms[j] && !ft_strcmp(pass->rooms[j], str))
		++j;
	while (pass->rooms[j])
	{
		if (pass->rooms[j] && !ft_strcmp(pass->rooms[j], str))
			++j;
		if (pass->rooms[j] && ft_strstr(pass->rooms[j], str))
			break ;
		else if (ft_strstr(str, pass->rooms[j]))
			return (-1);
		++j;
	}
	return (j);
}

static int	mnl_helper(t_room *pass, int *j, char *input, char *temp)
{
	int			i;
	char		*arr;
	static int	flag = 0;

	arr = NULL;
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
			if (pass->rooms[i] && !ft_strncmp(input, pass->rooms[i], ft_strlen(pass->rooms[i])))//, ft_strlen_stop(&help[ft_strlen(pass->rooms[*j]) + 1], '\n')))
			{
				arr = ft_strnew(addi_diff(input, &temp[-1]));
				if (!arr)
					return (-1);
				ft_strncpy(arr, input, addi_diff(input, &temp[-1]));
				if (ft_strcmp(arr, pass->rooms[i]))
					break ;
				free(arr);
				arr = NULL;
			}
			++i;
		}
	}
	if (arr)
	{
		free(arr);
		arr = NULL;
	}
	if (pass->rooms[*j])
		++(*j);
	if (!flag)
		return (-1);
	return (i);
}

static int	minus_newline(t_room *pass, char *str, char *input, char *temp)
{
	int		j;
	char	*arr;
	int		i;
	char	*hold;

	hold = temp;
	j = addi_diff(input, &temp[-1]);
	arr = ft_strnew(j);
	if (!arr)
		return (-1);
	ft_strncpy(arr, input, j);
	//ft_printf("mnl\n");
	if (find_connec_room(pass, str, &arr, 0) == 1)
		return (1);
	else
	{
		arr = NULL;
		j = 0;
		i = -1;
		while (pass->rooms[j])
		{
			j = room_finder(pass, str, j);
			if (j == -1)
				return (2); //not an error. returning so show that str is on the other side of search
			temp = NULL;
			if (pass->rooms[j])
				temp = ft_strstr(input, pass->rooms[j]);
			i = mnl_helper(pass, &j, input, temp);
		}
		if ((i != -1 && !pass->rooms[i]) || (i == -1 && hold[-1] == '-'))
			return (error(CONNECTION));
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

static int	newline_minus(t_room *pass, char *str, char *temp, char *input)
{
	int		j;
	int		i;

	//ft_printf("nlm\n");
	if (find_connec_room(pass, str, &temp, 1) == 1)
		return (1);
	else
	{
		j = 0;
		i = 0;
		while (pass->rooms[j])
		{
			j = room_finder(pass, str, j);
			if (j == -1)
				return (2); //not an error. returning so show that str is on the other side of search
			if (pass->rooms[j])
				temp = ft_strnstr(input, pass->rooms[j], ft_strlen(pass->rooms[j]));
			i = nlm_helper(pass, &j, temp);
			if (pass->rooms[i])
				break;
		}
		if (!pass->rooms[i] || !pass->rooms[j])
			return (error(CONNECTION));
	}
	return (2);
}

static int	found_or_not(t_room *pass, char *str, char *temp, char *input)
{
	if (temp && input[0] != '#' && ((temp[-1] == '\n' && temp[ft_strlen(str)] == '-') ||
		(temp[-1] == '-' && temp[ft_strlen(str)] == '\n')))
	{
		if (is_dash(&temp[ft_strlen(str)]) >= 1 && (temp[-1] == '\n' && 
			temp[ft_strlen(str)] == '-'))
			return (newline_minus(pass, str, temp,  input));
		else if (dash_in_section(input, temp) >= 1 && 
			(temp[-1] == '-' && temp[ft_strlen(str)] == '\n'))
			return (minus_newline(pass, str, input, temp));
	}
	return (0);
}

int	count_in(char *str, char *input, t_room *pass)
{
	int		i;
	char	*temp;
	int		diff;

	i = 0;
	while (input[i] != '\0')
	{
		temp = ft_strnstr(&input[i], str, ft_strlen_stop(&input[i], '\n'));
		diff = found_or_not(pass, str, temp, &input[i]); //maybe get rid
		if (diff == -1)
			return (-1);
		while (temp && input[i] != '#' && ft_strnstr(&temp[1], str, ft_strlen_stop(&temp[1], '\n')) && diff == 2) //&& (temp[-1] != '\n' || temp[ft_strlen(str)] != '-') 
		{
			temp = ft_strnstr(&temp[1], str, ft_strlen_stop(&temp[1], '\n'));
			if (temp[-1] == '-' && temp[ft_strlen(str)] == '\n')
			{
				if (minus_newline(pass, str, &input[i], temp) == -1)
					return (-1);
			}
		}
		while (input[i] != '\n')
			++i;
		++i;
	}
	return (0);
}
