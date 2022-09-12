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

static int	minus_newline(t_room *pass, char *str, char *input, char *temp)
{
	int		j;
	char	*arr;//arr[addi_diff(input, &temp[-1]) + 1];
	int		i;
	char	*hold;

	hold = temp;
	j = addi_diff(input, &temp[-1]);
	arr = ft_strnew(j);
	if (!arr)
	{
		exit (0); //wipe everything
	} 
	ft_strncpy(arr, input, j); //addi_diff(input, &temp[-1]));
	j = 0;
	if (!ft_strcmp(pass->rooms[j], str))
		++j;	
	while (pass->rooms[j])
	{
		if (pass->rooms[j] && !ft_strcmp(pass->rooms[j], str))
			++j;
		if (pass->rooms[j] && !ft_strcmp(arr, pass->rooms[j]))
		{
			create_connect(pass, j);
			free (arr);
			return (1);
		}
		++j;
	}
	free(arr);
	arr = NULL;
	if (!pass->rooms[j])
	{
		j = 0;
		i = -1;
		while (pass->rooms[j])
		{
			if (pass->rooms[j] && !ft_strcmp(pass->rooms[j], str))
				++j;
			while (pass->rooms[j])
			{
				if (pass->rooms[j] && !ft_strcmp(pass->rooms[j], str))
					++j;
				if (pass->rooms[j] && ft_strstr(pass->rooms[j], str))
					break;
				else if (ft_strstr(str, pass->rooms[j]))
					return (0);
				++j;
			}
			temp = NULL;
			if (pass->rooms[j])
				temp = ft_strstr(input, pass->rooms[j]);
			if (pass->rooms[j] && temp && temp[-1] == '-' && temp[ft_strlen(pass->rooms[j])] == '\n')
			{
				i = 0;
				if (pass->rooms[i] && !ft_strcmp(pass->rooms[i], pass->rooms[j]))
					++i;
				while (pass->rooms[i])
				{
					if (pass->rooms[i] && !ft_strcmp(pass->rooms[i], pass->rooms[j]))
						++i;
					if (pass->rooms[i] && !ft_strncmp(input, pass->rooms[i], ft_strlen(pass->rooms[i])))//, ft_strlen_stop(&help[ft_strlen(pass->rooms[j]) + 1], '\n')))
					{
						arr = ft_strnew(addi_diff(input, &temp[-1]));
						if (!arr)
						{
							exit(0);//delete everything 
						}
						ft_strncpy(arr, input, addi_diff(input, &temp[-1]));
						if (ft_strcmp(arr, pass->rooms[i]))
							break ;
						free(arr);
						arr = NULL;
					}
					++i;
				}
				if (pass->rooms[i])
					break ;
			}
			if (pass->rooms[j])
				++j;
		}
		if ((i != -1 && !pass->rooms[i]) || (i == -1 && hold[-1] == '-'))
			return (-1);
	}
	if (arr)
		free(arr);
	return (1);
}

static int	newline_minus(t_room *pass, char *str, char *temp, char *input)
{
	int		j;
	int		i;
	char	*help;

	j = 0;
	if (!ft_strcmp(pass->rooms[j], str))
		++j;
	while (pass->rooms[j])
	{
		if (!ft_strcmp(pass->rooms[j], str))
			++j;
		if (!ft_strncmp(&temp[ft_strlen(str) + 1], pass->rooms[j], ft_strlen_stop(&temp[ft_strlen(str) + 1], '\n')))
		{
			create_connect(pass, j);
			return (1);
		}
		++j;
	}
	if (!pass->rooms[j])
	{
		j = 0;
		i = 0;
		while (pass->rooms[j])
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
					return (0);
				++j;
			}
			if (pass->rooms[j])
				help = ft_strnstr(input, pass->rooms[j], ft_strlen(pass->rooms[j]));
			if (pass->rooms[j] && help && help[-1] == '\n' && help[ft_strlen(pass->rooms[j])] == '-')
			{
				i = 0;
				if (pass->rooms[i] && !ft_strcmp(pass->rooms[i], pass->rooms[j]))
					++i;
				while (pass->rooms[i])
				{
					if (pass->rooms[i] && !ft_strcmp(pass->rooms[i], pass->rooms[j]))
						++i;
					if (pass->rooms[i] && !ft_strncmp(&help[ft_strlen(pass->rooms[j]) + 1], pass->rooms[i], ft_strlen_stop(&help[ft_strlen(pass->rooms[j]) + 1], '\n')))
						break ;
					++i;
				}
				if (pass->rooms[i])
					break ;
			}
			if (pass->rooms[j])
			++j;
		}
		if (!pass->rooms[i] || !pass->rooms[j])
			return (-1);
	}
	return (1);
}

int	count_in(char *str, char *input, t_room *pass)
{
	int		i;
	int		count;
	char	*temp;
	int		error;
	int		diff;

	i = 0;
	count = 0;

	while (input[i] != '\0')
	{
		diff = count;
		temp = ft_strnstr(&input[i], str, ft_strlen_stop(&input[i], '\n'));
		if (temp && input[i] != '#' && ((temp[-1] == '\n' && temp[ft_strlen(str)] == '-') ||
			(temp[-1] == '-' && temp[ft_strlen(str)] == '\n')))
		{
			if (is_dash(&temp[ft_strlen(str)]) >= 1 && (temp[-1] == '\n' && 
				temp[ft_strlen(str)] == '-'))
			{
				error = newline_minus(pass, str, temp,  &input[i]);
				if (error == -1)
					return (-1);
				count += error; //newline_minus(rooms, str, temp,  &input[i]);
			}
			else if (dash_in_section(&input[i], temp) >= 1 && 
				(temp[-1] == '-' && temp[ft_strlen(str)] == '\n'))
			{
				error = minus_newline(pass, str, &input[i], temp);
				if (error == -1)
					return (-1);
				count += error; 
			}
		}
		while (temp && input[i] != '#' && ft_strnstr(&temp[1], str, ft_strlen_stop(&temp[1], '\n')) && diff == count) //&& (temp[-1] != '\n' || temp[ft_strlen(str)] != '-') 
		{
			temp = ft_strnstr(&temp[1], str, ft_strlen_stop(&temp[1], '\n'));
			if (temp[-1] == '-' && temp[ft_strlen(str)] == '\n')
				error = minus_newline(pass, str, &input[i], temp);
			else
				error = 0;
			if (error == -1)
				return (-1);
			count += error;
		}
		while (input[i] != '\n')
			++i;
		++i;
	}
	return (count);
}
