# include "visu_hex.h"

static void	make_board(t_data *data)
{
	int max_y = 1;
	int	max_x = 0;

	int i = 0;
	while (i < data->room_total)
	{
		if (max_x < data->room_x[i])
			max_x = data->room_x[i];
		if (max_y < data->room_y[i])
			max_y = data->room_y[i];
		++i;
	}
	max_x += 5;
	max_y += 4;
	data->board = (char **)malloc(sizeof(char *) * (max_y + 1));
	i = 0;
	while (i < max_y)
	{
		data->board[i] = (char *)malloc(sizeof(char) * (max_x + 1));
		ft_memset(data->board[i], '.', max_x - 1);
		++i;
	}
	data->board[i] = 0;
}

int	main(void)
{
	t_data	*data;
	int		ret;
	char	*line;

	ret = 1;
	line = NULL;
	data = malloc(sizeof(t_data));
	data->start = -20;
	data->end = -20;
	data->room_total = 0;
	data->connect_total = 0;
	while (ret == 1)
	{
		ret = get_next_line(0, &line);
		if (ret == ERROR)
			return (0);
		if (!line)
			break ;
		if (collect_data(data, line) == ERROR)
			return (1);
		free(line);
	}
	make_board(data);
	make_visual(data);
	return (0);
}
