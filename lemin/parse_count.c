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

# include "../includes/lemin.h"
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

static int	minus_newline(char **rooms, char *str, char *input, char *temp)
{
	int		j;
	int		count;
	char	*arr;//arr[addi_diff(input, &temp[-1]) + 1];
	int		i;
	char	*hold;

	count = 0;
	hold = temp;
	j = addi_diff(input, &temp[-1]);
	arr = ft_strnew(j);
	if (!arr)
	{
		exit (0); //wipe everything
	} 
	ft_strncpy(arr, input, j); //addi_diff(input, &temp[-1]));
	if (!ft_strcmp(str, "middle"))
		ft_printf("input\n\n%s\n", input);
	j = 0;
	if (!ft_strcmp(rooms[j], str))
		++j;
	while (rooms[j])
	{
		if (rooms[j] && !ft_strcmp(rooms[j], str))
			++j;
		if (rooms[j] && !ft_strcmp(arr, rooms[j]))
		{
			++count;
			break ;
		}
		++j;
	}
	free(arr);
	arr = NULL;
	if (!rooms[j])
	{
		j = 0;
		i = -1;
		while (rooms[j])
		{
			if (rooms[j] && !ft_strcmp(rooms[j], str))
				++j;
			while (rooms[j])
			{
				if (rooms[j] && !ft_strcmp(rooms[j], str))
					++j;
				if (rooms[j] && ft_strstr(rooms[j], str))
					break;
				else if (ft_strstr(str, rooms[j]))
					return (0);
				++j;
			}
			temp = NULL;
			if (rooms[j])
				temp = ft_strstr(input, rooms[j]);
			if (rooms[j] && temp && temp[-1] == '-' && temp[ft_strlen(rooms[j])] == '\n')
			{
				i = 0;
				if (rooms[i] && !ft_strcmp(rooms[i], rooms[j]))
					++i;
				while (rooms[i])
				{
					if (rooms[i] && !ft_strcmp(rooms[i], rooms[j]))
						++i;
					if (rooms[i] && !ft_strncmp(input, rooms[i], ft_strlen(rooms[i])))//, ft_strlen_stop(&help[ft_strlen(rooms[j]) + 1], '\n')))
					{
						arr = ft_strnew(addi_diff(input, &temp[-1]));
						if (!arr)
						{
							exit(0);//delete everything 
						}
						ft_strncpy(arr, input, addi_diff(input, &temp[-1]));
						if (ft_strcmp(arr, rooms[i]))
							break ;
						free(arr);
						arr = NULL;
					}
					++i;
				}
				if (rooms[i])
					break ;
			}
			if (rooms[j])
				++j;
		}
		if ((i != -1 && !rooms[i]) || (i == -1 && hold[-1] == '-'))
			return (-1);
	}
	if (arr)
		free(arr);
	return (count);
}

static int	newline_minus(char **rooms, char *str, char *temp, char *input)
{
	int		j;
	int		i;
	int		count;
	char	*help;

	j = 0;
	count = 0;
	if (!ft_strcmp(rooms[j], str))
		++j;
	while (rooms[j])
	{
		if (!ft_strcmp(rooms[j], str))
			++j;
		if (!ft_strncmp(&temp[ft_strlen(str) + 1], rooms[j], ft_strlen_stop(&temp[ft_strlen(str) + 1], '\n')))
		{
			++count;
			break;
		}
		++j;
	}
	if (!rooms[j])
	{
		j = 0;
		i = 0;
		while (rooms[j])
		{
			if (rooms[j] && !ft_strcmp(rooms[j], str))
				++j;
			while (rooms[j])
			{
				if (rooms[j] && !ft_strcmp(rooms[j], str))
					++j;
				if (rooms[j] && ft_strstr(rooms[j], str))
					break ;
				else if (ft_strstr(str, rooms[j]))
					return (0);
				++j;
			}
			if (rooms[j])
				help = ft_strnstr(input, rooms[j], ft_strlen(rooms[j]));
			if (rooms[j] && help && help[-1] == '\n' && help[ft_strlen(rooms[j])] == '-')
			{
				i = 0;
				if (rooms[i] && !ft_strcmp(rooms[i], rooms[j]))
					++i;
				while (rooms[i])
				{
					if (rooms[i] && !ft_strcmp(rooms[i], rooms[j]))
						++i;
					if (rooms[i] && !ft_strncmp(&help[ft_strlen(rooms[j]) + 1], rooms[i], ft_strlen_stop(&help[ft_strlen(rooms[j]) + 1], '\n')))
						break ;
					++i;
				}
				if (rooms[i])
					break ;
			}
			if (rooms[j])
			++j;
		}
		if (!rooms[i] || !rooms[j])
			return (-1);
	}
	return (count);
}

int	count_in(char *str, char *input, char **rooms)
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
		//error with checking if line is comment to skipp
		diff = count;
		//if (!ft_strcmp(str, "middle"))
		//	ft_printf("diff %i  count %i\n", diff, count);
		temp = ft_strnstr(&input[i], str, ft_strlen_stop(&input[i], '\n'));
		if (temp && input[i] != '#' && ((temp[-1] == '\n' && temp[ft_strlen(str)] == '-') ||
			(temp[-1] == '-' && temp[ft_strlen(str)] == '\n')))
		{
		//if (!ft_strcmp(str, "middle"))
		//	ft_printf("count %i\n", count);

			if (is_dash(&temp[ft_strlen(str)]) >= 1 && (temp[-1] == '\n' && 
				temp[ft_strlen(str)] == '-'))
			{
				// if (!ft_strcmp(str, "middle"))
				// 	ft_printf("CHECK 1\n");
				error = newline_minus(rooms, str, temp,  &input[i]);
				if (error == -1)
					return (-1);
				count += error; //newline_minus(rooms, str, temp,  &input[i]);
			}
			else if (dash_in_section(&input[i], temp) >= 1 && 
				(temp[-1] == '-' && temp[ft_strlen(str)] == '\n'))
			{
				// if (!ft_strcmp(str, "middle"))
				// 	ft_printf("CHECK 2\n");
				error = minus_newline(rooms, str, &input[i], temp);
				if (error == -1)
					return (-1);
				count += error; 
			}
				//count += minus_newline(rooms, str, &input[i], temp);
		}
		//if (!ft_strcmp(str, "middle"))
		//	ft_printf("diff %i\n", diff);
		while (temp && input[i] != '#' && ft_strnstr(&temp[1], str, ft_strlen_stop(&temp[1], '\n')) && diff == count) //&& (temp[-1] != '\n' || temp[ft_strlen(str)] != '-') 
		{
			// if (!ft_strcmp(str, "middle"))
			// 	ft_printf("count %i\n", count);
			// if (!ft_strcmp(str, "middle"))
			// 		ft_printf("CHECK 3\n");
			temp = ft_strnstr(&temp[1], str, ft_strlen_stop(&temp[1], '\n'));
			if (temp[-1] == '-' && temp[ft_strlen(str)] == '\n')
				error = minus_newline(rooms, str, &input[i], temp);
			else
				error = 0;
			if (error == -1)
				return (-1);
			count += error;
			// if (!ft_strcmp(str, "middle"))
				// ft_printf("count %i\n", count);
		}
		while (input[i] != '\n')
			++i;
		++i;
	}
	return (count);
}
