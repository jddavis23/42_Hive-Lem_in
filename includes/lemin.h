#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/libft.h"

typedef enum
{
	NO_ANTS,
	TOO_MANY_ANTS,
	NON_DIGIT_ANTS,
	COMMAND,
	COORDINATES,
	CONNECTION,
} error_message;

int	parsing_phase(int *total);
int	error(int err);
int	only_digits(char *str, int *i);
int	is_coordinates(char *str);
int is_connection(char *str);

#endif
