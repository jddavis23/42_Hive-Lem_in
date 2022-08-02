/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_collect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:19:54 by jdavis            #+#    #+#             */
/*   Updated: 2022/07/11 13:19:55 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

static void	collect_index(t_room *pass, int j, int i)
{
	int	k;

	k = 0;
	while (pass->links[i][k] >= 0)
		++k;
	pass->links[i][k] = j;
}

static void	minus_newline_collect(t_room *pass, int k, char *input, char *temp)
{
	int		j;
	char	arr[addi_diff(input, &temp[-1]) + 1];

	j = 0;
	ft_bzero(arr, addi_diff(input, &temp[-1]) + 1);
	ft_strncpy(arr, input, addi_diff(input, &temp[-1]));
	//ft_printf("ARR %s\n", arr);
	if (pass->rooms[j] && pass->rooms[k] && !ft_strcmp(pass->rooms[j], pass->rooms[k]))
		++j;
	while (pass->rooms[j])
	{
		if (pass->rooms[j] && !ft_strcmp(pass->rooms[j], pass->rooms[k]))
			++j;
		if (!pass->rooms[j])
			break ;
		if (pass->rooms[j] && !ft_strcmp(arr, pass->rooms[j]))
		{
			//ft_printf("FOUND %s  INPPUT %s\n", rooms[j], input);
			collect_index(pass, j, k);
			break ;
		}
		++j;
	}
}

static void newline_minus_collect(t_room *pass, int k, char *temp)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(pass->rooms[k]); 
	if (pass->rooms[j] && pass->rooms[k] && !ft_strcmp(pass->rooms[j], pass->rooms[k]))
		++j;
	while (pass->rooms[j])
	{
		if (!ft_strcmp(pass->rooms[j], pass->rooms[k]))
			++j;
		if (!ft_strncmp(&temp[len + 1], pass->rooms[j], ft_strlen_stop(&temp[len + 1], '\n')))
		{
			collect_index(pass, j, k);
			break;
		}
		++j;
	}
}

/*	recursive function. looks for the connections	*/

void match_in(char *str, char *input, t_room *pass, int k)
{
	int		i;
	char	*temp;

	i = 0;
	while (input[i] != '\0')
	{
		temp = ft_strnstr(&input[i], str, ft_strlen_stop(&input[i], '\n'));
		if (temp && ((temp[-1] == '\n' && temp[ft_strlen(str)] == '-') ||
			(temp[-1] == '-' && temp[ft_strlen(str)] == '\n')))
		{
			if (is_dash(&temp[ft_strlen(str)]) >= 1 && (temp[-1] == '\n' && 
				temp[ft_strlen(str)] == '-'))
				newline_minus_collect(pass, k, temp);
			else if (dash_in_section(&input[i], temp) >= 1 && 
				(temp[-1] == '-' && temp[ft_strlen(str)] == '\n'))
			{
				minus_newline_collect(pass, k, &input[i], temp);
			}
		}
		while (temp && ft_strnstr(&temp[1], str, ft_strlen_stop(&temp[1], '\n'))) //&& (temp[-1] != '\n' || temp[ft_strlen(str)] != '-') 
		{
			temp = ft_strnstr(&temp[1], str, ft_strlen_stop(&temp[1], '\n'));
			if (temp[-1] == '-' && temp[ft_strlen(str)] == '\n')
				minus_newline_collect(pass, k, &input[i], temp);
		}
		while (input[i] != '\n')
			++i;
		++i;
	}
}

/////////////////////////////////

/*int	is_dash(char *str)
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
}*/

/*static int	addi_diff(char *start, char *finish) //undefined behaviour if finish is not infront of start
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
}*/

// static int	minus_newline_collect(char **rooms, char *str, char *input, char *temp, int k, t_room *pass)
// {
// 	int		j;
// 	int		count;
// 	char	*arr;//arr[addi_diff(input, &temp[-1]) + 1];
// 	int		i;
// 	char	*hold;

// 	count = 0;
// 	hold = temp;
// 	j = addi_diff(input, &temp[-1]);
// 	arr = ft_strnew(j);
// 	if (!arr)
// 	{
// 		exit (0); //wipe everything
// 	} 
// 	ft_strncpy(arr, input, j); //addi_diff(input, &temp[-1]));
// 	j = 0;
// 	if (!ft_strcmp(rooms[j], str))
// 		++j;
// 	while (rooms[j])
// 	{
// 		if (rooms[j] && !ft_strcmp(rooms[j], str))
// 			++j;
// 		if (rooms[j] && !ft_strcmp(arr, rooms[j]))
// 		{
// 			collect_index(pass, j, k);
// 			//++count;
// 			break ;
// 		}
// 		++j;
// 	}
// 	free(arr);
// 	arr = NULL;
// 	if (!rooms[j])
// 	{
// 		j = 0;
// 		i = -1;
// 		while (rooms[j])
// 		{
// 			if (rooms[j] && !ft_strcmp(rooms[j], str))
// 				++j;
// 			while (rooms[j])
// 			{
// 				if (rooms[j] && !ft_strcmp(rooms[j], str))
// 					++j;
// 				if (rooms[j] && ft_strstr(rooms[j], str))
// 					break;
// 				else if (ft_strstr(str, rooms[j]))
// 					return (0);
// 				++j;
// 			}
// 			temp = NULL;
// 			if (rooms[j])
// 				temp = ft_strstr(input, rooms[j]);
// 			if (rooms[j] && temp && temp[-1] == '-' && temp[ft_strlen(rooms[j])] == '\n')
// 			{
// 				i = 0;
// 				if (rooms[i] && !ft_strcmp(rooms[i], rooms[j]))
// 					++i;
// 				while (rooms[i])
// 				{
// 					if (rooms[i] && !ft_strcmp(rooms[i], rooms[j]))
// 						++i;
// 					if (rooms[i] && !ft_strncmp(input, rooms[i], ft_strlen(rooms[i])))//, ft_strlen_stop(&help[ft_strlen(rooms[j]) + 1], '\n')))
// 					{
// 						arr = ft_strnew(addi_diff(input, &temp[-1]));
// 						if (!arr)
// 						{
// 							exit(0);//delete everything 
// 						}
// 						ft_strncpy(arr, input, addi_diff(input, &temp[-1]));
// 						if (ft_strcmp(arr, rooms[i]))
// 							break ;
// 						free(arr);
// 						arr = NULL;
// 					}
// 					++i;
// 				}
// 				if (rooms[i])
// 					break ;
// 			}
// 			if (rooms[j])
// 				++j;
// 		}
// 		if ((i != -1 && !rooms[i]) || (i == -1 && hold[-1] == '-'))
// 			return (-1);
// 	}
// 	if (arr)
// 		free(arr);
// 	return (count);
// }

// static int	newline_minus_collect(char **rooms, char *str, char *temp, char *input, int k, t_room *pass)
// {
// 	int		j;
// 	int		i;
// 	int		count;
// 	char	*help;

// 	j = 0;
// 	count = 0;
// 	if (!ft_strcmp(rooms[j], str))
// 		++j;
// 	while (rooms[j])
// 	{
// 		if (!ft_strcmp(rooms[j], str))
// 			++j;
// 		if (!ft_strncmp(&temp[ft_strlen(str) + 1], rooms[j], ft_strlen_stop(&temp[ft_strlen(str) + 1], '\n')))
// 		{
// 			//if (!ft_strcmp(str, "Cqp4"))
// 			//	ft_printf("HERE\n");
// 			collect_index(pass, j, k);
// 			//++count;
// 			break;
// 		}
// 		++j;
// 	}
// 	if (!rooms[j])
// 	{
// 		j = 0;
// 		i = 0;
// 		while (rooms[j])
// 		{
// 			if (rooms[j] && !ft_strcmp(rooms[j], str))
// 				++j;
// 			while (rooms[j])
// 			{
// 				if (rooms[j] && !ft_strcmp(rooms[j], str))
// 					++j;
// 				if (rooms[j] && ft_strstr(rooms[j], str))
// 					break ;
// 				else if (ft_strstr(str, rooms[j]))
// 					return (0);
// 				++j;
// 			}
// 			if (rooms[j])
// 				help = ft_strnstr(input, rooms[j], ft_strlen(rooms[j]));
// 			if (rooms[j] && help && help[-1] == '\n' && help[ft_strlen(rooms[j])] == '-')
// 			{
// 				i = 0;
// 				if (rooms[i] && !ft_strcmp(rooms[i], rooms[j]))
// 					++i;
// 				while (rooms[i])
// 				{
// 					if (rooms[i] && !ft_strcmp(rooms[i], rooms[j]))
// 						++i;
// 					if (rooms[i] && !ft_strncmp(&help[ft_strlen(rooms[j]) + 1], rooms[i], ft_strlen_stop(&help[ft_strlen(rooms[j]) + 1], '\n')))
// 						break ;
// 					++i;
// 				}
// 				if (rooms[i])
// 					break ;
// 			}
// 			if (rooms[j])
// 			++j;
// 		}
// 		if (!rooms[i] || !rooms[j])
// 			return (-1);
// 	}
// 	return (count);
// }

// int	match_in(char *str, char *input, char **rooms, int k, t_room *pass)
// {
// 	int		i;
// 	int		count;
// 	char	*temp;
// 	int		error;
// 	int		diff;

// 	i = 0;
// 	count = 0;
// 	while (input[i] != '\0')
// 	{
// 		//error with checking if line is comment to skipp
// 		diff = count;
// 		temp = ft_strnstr(&input[i], str, ft_strlen_stop(&input[i], '\n'));
// 		if (temp && input[i] != '#' && ((temp[-1] == '\n' && temp[ft_strlen(str)] == '-') ||
// 			(temp[-1] == '-' && temp[ft_strlen(str)] == '\n')))
// 		{
// 			if (is_dash(&temp[ft_strlen(str)]) >= 1 && (temp[-1] == '\n' && 
// 				temp[ft_strlen(str)] == '-'))
// 			{
// 				error = newline_minus_collect(rooms, str, temp,  &input[i], k, pass);
// 				if (error == -1)
// 					return (-1);
// 				count += error; //newline_minus(rooms, str, temp,  &input[i]);
// 			}
// 			else if (dash_in_section(&input[i], temp) >= 1 && 
// 				(temp[-1] == '-' && temp[ft_strlen(str)] == '\n'))
// 			{
// 				error = minus_newline_collect(rooms, str, &input[i], temp, k, pass);
// 				if (error == -1)
// 					return (-1);
// 				count += error; 
// 			}
// 				//count += minus_newline(rooms, str, &input[i], temp);
// 		}
// 		while (temp && input[i] != '#' && ft_strnstr(&temp[1], str, ft_strlen_stop(&temp[1], '\n')) && diff == count) //&& (temp[-1] != '\n' || temp[ft_strlen(str)] != '-') 
// 		{
// 			temp = ft_strnstr(&temp[1], str, ft_strlen_stop(&temp[1], '\n'));
// 			error = minus_newline_collect(rooms, str, &input[i], temp, k, pass);
// 			if (error == -1)
// 				return (-1);
// 			count += error; 
// 		}
// 		while (input[i] != '\n')
// 			++i;
// 		++i;
// 	}
// 	return (count);
// }

