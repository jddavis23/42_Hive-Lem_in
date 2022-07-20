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
	char	arr[addi_diff(input, &temp[-1]) + 1];

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
	ft_printf("%s---\n", str);
	if (!rooms[j])
	{
		j = 0;
		i = 0;
		while (rooms[j])
		{
			//ft_printf("HERE %p\n", rooms[j]);
			if (rooms[j] && !ft_strcmp(rooms[j], str))
				++j;
			//ft_printf("MAN\n");
			while (rooms[j])
			{
				//ft_printf("HERE1\n");
				if (rooms[j] && !ft_strcmp(rooms[j], str))
					++j;
				if (rooms[j] && ft_strstr(rooms[j], str))
					break;
					//ft_printf("HERE6\n");
				++j;
			}
			if (rooms[j])
				help = ft_strnstr(input, rooms[j], ft_strlen(rooms[j]));
			if (rooms[j] && help && help[-1] == '\n' && help[ft_strlen(rooms[j])] == '-')
			{
				//ft_printf("HERE9\n");
				i = 0;
				if (rooms[i] && !ft_strcmp(rooms[i], rooms[j]))
					++i;
				while (rooms[i])
				{
					//ft_printf("HERE2\n");
					if (rooms[i] && !ft_strcmp(rooms[i], rooms[j]))
						++i;
					if (rooms[i] && !ft_strncmp(&help[ft_strlen(rooms[i]) + 1], rooms[i], ft_strlen_stop(&help[ft_strlen(rooms[i]) + 1], '\n')))
					{
						i = -1;
						break ;
					}
					++i;
				}
				if (i == -1)
					break ;
			}
			if (rooms[j])
			++j;
		}
		if (i != -1)
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

	i = 0;
	count = 0;
	while (input[i] != '\0')
	{
		temp = ft_strnstr(&input[i], str, ft_strlen_stop(&input[i], '\n'));
		if (temp && ((temp[-1] == '\n' && temp[ft_strlen(str)] == '-') ||
			(temp[-1] == '-' && temp[ft_strlen(str)] == '\n')))
		{
			if (is_dash(&temp[ft_strlen(str)]) >= 1 && (temp[-1] == '\n' && 
				temp[ft_strlen(str)] == '-'))
			{
				error = newline_minus(rooms, str, temp,  &input[i]);
				if (error == -1)
					return (-1);
				count += error; //newline_minus(rooms, str, temp,  &input[i]);
			}
			else if (dash_in_section(&input[i], temp) >= 1 && 
				(temp[-1] == '-' && temp[ft_strlen(str)] == '\n'))
			{
				error = minus_newline(rooms, str, &input[i], temp);
				if (error == -1)
					return (-1);
				count += error; 
			}
				//count += minus_newline(rooms, str, &input[i], temp);
		}
		while (temp && ft_strnstr(&temp[1], str, ft_strlen_stop(&temp[1], '\n'))) //&& (temp[-1] != '\n' || temp[ft_strlen(str)] != '-') 
		{
			temp = ft_strnstr(&temp[1], str, ft_strlen_stop(&temp[1], '\n'));
			error = minus_newline(rooms, str, &input[i], temp);
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
