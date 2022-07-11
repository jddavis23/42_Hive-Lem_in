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

typedef enum
{
	NO_ANTS,
	TOO_MANY_ANTS,
	NON_DIGIT_ANTS,
	COMMAND,
	COORDINATES,
	CONNECTION,
} error_message;

int	parsing_phase(t_room *pass, char **input);
int	error(int err);
int	only_digits(char *str, int *i);
int	is_coordinates(char *str);
int is_connection(char *str);
int	create(t_room *pass, char *input);

// parsing
void	match_in(char *str, char *input, t_room *pass, int k);
int		count_in(char *str, char *input, char **rooms);
int		addi_diff(char *start, char *finish);
int		dash_in_section(char *full, char *inside);
int		is_dash(char *str);

#endif
