#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/libft.h"

int	parsing_phase(int *total);
int	error(int err);

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
