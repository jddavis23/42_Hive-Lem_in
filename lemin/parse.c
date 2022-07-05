/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:11:51 by molesen           #+#    #+#             */
/*   Updated: 2022/07/05 13:56:59 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

static int	below_max_int(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 10 || (len == 10 && ft_strcmp(str, "2147483647") > 0))
		return (FALSE);
	return (TRUE);
}

static int	only_digits(char *str, int *i)
{
	if (ft_strcmp("0", str) == 0 || ft_strcmp("\0", str) == 0)
		return (FALSE);
	if (below_max_int(str) == FALSE)
		return (FALSE);
	while (*str != '\0')
	{
		if (ft_isdigit(*str) == 0)
			return (FALSE);
		str++;
	}
	if (i)
		 (*i)++;
	return (TRUE);
}

static int	is_comment(char *str)
{
	int	count;

	count = 0;
	while (*str == '#')
	{
		++count;
		++str;
	}
	if (count < 1)
		return (FALSE);
	return (count);
}

static int	is_coordinates(char *str)
{
	if (*str == 'L')
		return (FALSE);
	if (ft_word_count(str, ' ') != 3)
		return (FALSE);
		//below_max_int(char *str)
	// while (*str != '\0')
	// {
	// 	++count;
	// 	++str;
	// }
	// return (TRUE);
	// // count words has to be three
	// // two last words has to only consist of digits and has to be below max int
	// // duplicate rooms can first be checked when collecting phase aka jeff has easier time implementing this
	// if (str)
	// 	return (TRUE);
	return (TRUE);
}

static int is_connection(char *str)
{
	//words has to be two split by '-'
	//has to be digits not above max int
	if (str)
		return (TRUE);
	return (TRUE);
}


int	by_line(char *input)
{
	int	flag;
	int	count;
	int	i;

	i = 0;
	count = 0;
	flag = 1;
	if (input[i] == '#')
		return (-1);
	while (input[i] != '\n' && input[i] != '\0')
	{
		if (flag && input[i] != ' ' && input[i] != '-')
		{
			 flag = 0;
			 ++count;
		}
		if (input[i] == ' ' || input[i] == '-')
			flag = 1;
		++i;
	}
	return (count);
}

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

int	find_indx(t_room *pass, char *input, int count)
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
}

void	realloc_arr(t_room *pass, int k, int insert)
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
}

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

int	count_in(char *str, char *input)
{
	int	i;
	int	hold;
	int	count;

	i = 0;
	count = 0;
	if (ft_strlen_stop(input, '-') < ft_strlen_stop(input, '\n'))
		hold = ft_strlen_stop(input, '-');
	else
		hold = ft_strlen_stop(input, '\n');
	while (input[i] != '\0')
	{
		if (!ft_strncmp(str, &input[i], hold))
			++count;
		while (input[i] != '-' && input[i] != '\n' && input[i] != '\0')
			++i;
		if (input[i] == '\n' || input[i] == '-')
			++i;
	}
	return (count);

}

int	create(t_room *pass, char *input)	
{
	int	count;
	int	i;
	int	j;
	int	k;
	int	hold;

	i = 0;
	j = 0;
	k = 0;
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
		while (input[i] != '\0')
		{
			hold = by_line(&input[i]);
			if (hold < 2)
			{
				while (input[i] != '\n')
					++i;
			}
			//ft_printf("%i\n", hold);
			if (hold == 3)
			{
				pass->rooms[j] = ft_strnew(ft_strlen_stop(&input[i], ' '));
				if (!pass->rooms[j])
				{
					exit (0);
					//free exit
				}
				ft_strncat(pass->rooms[j++], &input[i], ft_strlen_stop(&input[i], ' '));
				ft_printf("%s-\n", pass->rooms[j - 1]);
				while (input[i] != '\n')
					++i;

			}
			else if (hold == 2 && ft_strlchr(&input[i], '-', ft_strlen_stop(&input[i], '\n')))
			{
				j = 0;
				while (pass->rooms[j])
				{
					ft_printf("room %s   %i\n", pass->rooms[j], count_in(pass->rooms[j], &input[i]));
					++j;
				}
				exit (0);
				/*k = find_indx(pass, &input[i]);
				if (k == -1)
					//free and exit

				count_in(&input[i]);
				initial_mal(pass, k);
				while (input[i] != '-')
					++i;
				++i;
				realloc_arr(pass, k, find_indx(pass, &input[i]));
				//write(1, &input[i], ft_strlen_stop(&input[i], '\n'));	
				//ft_printf("\n");*/
			}
			++i;
		}
		pass->rooms[count] = NULL;
		pass->links[count] = NULL;
	}
	j = 0;
	//while (pass->rooms[j])
	//	ft_printf("%s\n", pass->rooms[j++]);
	return (1);
}

int	parsing_phase(t_room *pass, char **input)
{
	int		ret;
	int		i;
	int		comment;
	char	*line;
	char	*temp;
	char	*just;  //will think of better way

	temp = NULL;
	ret = 1;
	line = NULL;
	i = 0;
	while (ret == 1)
	{
		ret = get_next_line(0, &line);
		if (ret == ERROR)
			return (0);
		if (!line)
			break ;
		comment = is_comment(line);
		if (i == 0 && only_digits(line, &i) == TRUE)
			pass->ants = ft_atoi(line);
		else if (comment >= TRUE && i > 0)
		{
			//## start and end has to be done at coordinates and can only happen once.
			// so if it has already been found it is an erroir
			ft_printf("call function to collect comment if it contains ##start or ##end\n");
		}
		else if (i == 1 && is_coordinates(line) == TRUE)
			ft_printf("call function to collect name of rooms\n");
		else if (i >= 1 && is_connection(line) == TRUE)
		{
			++i;
			ft_printf("call function to collect connections\n");
		}
		else
		{
			free(line);
			return (ERROR);
		}
		if (!(*input))
			*input = ft_strjoin(line, "\n");
		else
		{
			temp = ft_strjoin(line, "\n");
			just = ft_strjoin(*input, temp);
			free(*input);
			free(temp);
			*input = just;
		}
		free(line);
	}
	return (4);
}

// how to check if path is valid?
