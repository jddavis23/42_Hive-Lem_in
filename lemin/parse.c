/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:11:51 by molesen           #+#    #+#             */
/*   Updated: 2022/07/04 16:59:00 by jdavis           ###   ########.fr       */
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


void	by_line(t_room *pass, char *input)
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
		if (input[i] == ' ')
			flag = 1;
		++i;
	}
	return (count);
}

char	*ft_strlchr(const char *str, int c, int len)
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

int	create(t_room *pass, char *input)	
{
	int	count;
	//char *input;
	int	i;
	int	j;

	i = 0;
	j = 0;
	pass = (t_room *) malloc(sizeof(t_room));
	if (!pass)
		return (-1);
	count = parsing_phase(pass, input);
	if (count == -1)
		return (-1);
	pass->rooms = NULL;
	pass->links = NULL;
	if (count > 0)
	{
		pass->rooms = (char **) malloc(count + 1 * sizeof(char *));
		pass->links = (int **) malloc(count + 1 * sizeof(int *));
		if (!pass->rooms || !pass->links)
		{
			//delete and return 
		}
		while (input[i] != '\0')
		{
			j = by_line(pass, input);
			if (j == 3)
			{
				pass->rooms[i] = ft_strnew(ft_strlen_stop(&input[i], ' '));
				ft_strlcat(pass->rooms[i++], &input[i], ft_strlen_stop(&input[i], ' '));

			}
			else if (j == 2 && ft_strlchr(&input[i], '-', ft_strlen_stop(&input[i], '\n')))
			{
				
			}


		}
	}
	return (1);
}

int	parsing_phase(t_room *pass, char *input)
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
		if (!input)
			input = ft_strjoin(line, "\n");
		else
		{
			temp = ft_strjoin(line, "\n");
			just = ft_strjoin(input, temp);
			free(input);
			free(temp);
			input = just;
		}
		ft_printf("%s\n", input);
		free(line);
	}
	return (0);
}

// how to check if path is valid?
