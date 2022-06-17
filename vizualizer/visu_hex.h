#ifndef VISU_HEX_H
# define VISU_HEX_H

# include "../libft/ft_printf.h"
# include <stdlib.h>

typedef struct s_data
{
	int		ants;
	int		start;
	int		end;
	int		*room;
	int		*room_x;
	int		*room_y;
	int		room_total;
	char	**connect;
	int		connect_total;
	char	**board;
}	t_data;

int		collect_data(t_data *data, char *line);
void	make_visual(t_data *data);

#endif
