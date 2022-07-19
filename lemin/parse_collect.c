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
	if (!ft_strcmp(pass->rooms[j], pass->rooms[k]))
		++j;
	while (pass->rooms[j])
	{
		if (pass->rooms[j] && !ft_strcmp(pass->rooms[j], pass->rooms[k]))
			++j;
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
	if (!ft_strcmp(pass->rooms[j], pass->rooms[k]))
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
				minus_newline_collect(pass, k, &input[i], temp);
		}
		while (temp && ft_strnstr(&temp[1], str, ft_strlen_stop(&temp[1], '\n'))) //&& (temp[-1] != '\n' || temp[ft_strlen(str)] != '-') 
		{
			temp = ft_strnstr(&temp[1], str, ft_strlen_stop(&temp[1], '\n'));
			minus_newline_collect(pass, k, &input[i], temp);
		}
		while (input[i] != '\n')
			++i;
		++i;
	}
}
