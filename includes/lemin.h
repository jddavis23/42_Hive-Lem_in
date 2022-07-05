#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/libft.h"

typedef struct  s_room
{
	char	**rooms;
	int		**links;
	int		start;
	int		end;
	int		ants;
}				t_room;

int	parsing_phase(t_room *pass, char **input);
int	error(void);
int	create(t_room *pass, char *input);

#endif
