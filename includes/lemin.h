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

typedef enum
{
	NO_ANTS,
	TOO_MANY_ANTS,
	NON_DIGIT_ANTS,
	COMMAND,
	COORDINATES,
	CONNECTION,
} error_message;

#endif
