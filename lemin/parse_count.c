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

static int	newline_minus(char **rooms, char *str, char *temp)
{
	int	j;
	int	count;

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
	return (count);
}

int	count_in(char *str, char *input, char **rooms)
{
	int	i;
	//int	hold;
	int	count;
	char	*temp;
	//int		wait = 0;

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
				count += newline_minus(rooms, str, temp);
			else if (dash_in_section(&input[i], temp) >= 1 && 
				(temp[-1] == '-' && temp[ft_strlen(str)] == '\n'))
				count += minus_newline(rooms, str, &input[i], temp);
		}
		while (temp && ft_strnstr(&temp[1], str, ft_strlen_stop(&temp[1], '\n'))) //&& (temp[-1] != '\n' || temp[ft_strlen(str)] != '-') 
		{
			temp = ft_strnstr(&temp[1], str, ft_strlen_stop(&temp[1], '\n'));
			count += minus_newline(rooms, str, &input[i], temp);
		}
		while (input[i] != '\n')
			++i;
		++i;
	}
	return (count);

}
