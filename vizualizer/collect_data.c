# include "visu_hex.h"

static int	error(t_data *data)
{
	if (data->room_x)
		free(data->room_x);
	if (data->room_y)
		free(data->room_y);
	if (data->room)
		free(data->room);
	if (data->connect)
		free(data->connect);
	if (data)
		free(data);
	ft_putstr_fd("error\n", 2);
	return (ERROR);
}

static void	expand_room_data(t_data *data, int *room)
{
	int	*temp;

	temp = room;
	free (room);
	room = (int *)malloc(sizeof(int) * data->room_total);
	room = temp;
}

static int	malloc_room_data(t_data *data)
{
	if (data->room_total == 0)
	{
		data->room_total++;
		data->room = (int *)malloc(sizeof(int) * data->room_total);
		data->room_x = (int *)malloc(sizeof(int) * data->room_total);
		data->room_y = (int *)malloc(sizeof(int) * data->room_total);
		if (!data->room || !data->room_x || !data->room_y)
			return (ERROR);
	}
	else
	{
		data->room_total++;
		expand_room_data(data, data->room);
		expand_room_data(data, data->room_x);
		expand_room_data(data, data->room_y);

		if (!data->room || !data->room_x || !data->room_y)
			return (ERROR);
	}
	return (0);
}

static int	collect_coordinates(t_data *data, char *line)
{
	int i = 0;
	int	nbr = FALSE;
	int	x = FALSE;
	int y = FALSE;
	if (malloc_room_data(data) == ERROR)
		return (error(data));
	while (line[i] != '\0')
	{
		if (nbr == FALSE)
		{
			data->room[data->room_total - 1] = ft_atoi(&line[i]);
			nbr = TRUE;
		}
		else if (nbr == TRUE && x == FALSE)
		{
			data->room_x[data->room_total - 1] = ft_atoi(&line[i]);
			x = TRUE;
		}
		else if (nbr == TRUE && x == TRUE && y == FALSE)
		{
			data->room_y[data->room_total - 1] = ft_atoi(&line[i]);
			y = TRUE;
		}
		else
			return (ERROR);
		while (ft_isdigit(line[i]) == 1)
			++i;
		if (line[i] == ' ')
			++i;
	}
	if (data->start == -1)
		data->start = data->room[data->room_total - 1];
	else if (data->end == -1)
		data->end = data->room[data->room_total - 1];
	// i = 0;
	// while (i < data->room_total)
	// {
	// 	ft_printf("data[i]: %d, x: %d, y: %d\n", data->room[i], data->room_x[i], data->room_y[i]);
	// 	++i;
	// }
	return (0);
}

static int	malloc_connection_data(t_data *data)
{
	char	**temp;

	if (data->connect_total == 0)
	{
		data->connect_total++;
		data->connect = (char **)malloc(sizeof(char *) * (data->connect_total + 1));
		if (!data->connect)
			return (ERROR);
	}
	else
	{
		data->connect_total++;

		temp = data->connect;
		free (data->connect);
		data->connect = (char **)malloc(sizeof(char *) * (data->connect_total + 1));
		data->connect = temp;

		if (!data->connect)
			return (ERROR);
	}
	return (0);
}

static int	collect_connections(t_data *data, char *line)
{
	int	len;

	if (malloc_connection_data(data) == ERROR)
		return (ERROR);
	len = ft_strlen(line);
	data->connect[data->connect_total - 1] = (char *)malloc(sizeof(char) * (len + 1));
	if (!data->connect[data->connect_total - 1])
		return (ERROR);
	ft_strcpy(data->connect[data->connect_total - 1], line);
	//ft_printf("dataconnect[i]: %s\n", data->connect[data->connect_total - 1]);
	return (0);
}

int	collect_data(t_data *data, char *line)
{
	int	i;
	ft_printf("%s\n", line);
	if (data->start == -20 && ft_strcmp(line, "##start") == 0)
		data->start = -1;
	else if (data->end == -20 && ft_strcmp(line, "##end") == 0)
		data->end = -1;
	else
	{
		i = 0;
		int	connect = FALSE;
		int	space = FALSE;
		while (line[i] != '\0')
		{
			if (line[i] == '-' && space == FALSE && \
				ft_isdigit(line[i + 1]) == 1 && ft_isdigit(line[i - 1]) == 1)
				connect = TRUE;
			else if (line[i] == ' ' && connect == FALSE && \
				ft_isdigit(line[i + 1]) == 1 && ft_isdigit(line[i - 1]) == 1)
				space = TRUE;
			else if (ft_isdigit(line[i]) != 1)
				return (ERROR);
			++i;
		}
		if (connect == FALSE && space == FALSE)
			data->ants = ft_atoi(line);
		else if (connect == TRUE && space == FALSE)
		{
			if (collect_connections(data, line) == ERROR)
				return (ERROR);
			//ft_printf("looking at connections\n");
		}
		else
		{
			if (collect_coordinates(data, line) == ERROR)
				return (ERROR);
			//ft_printf("looking at coordinates\n");
		}
	}
	return (0);
}
