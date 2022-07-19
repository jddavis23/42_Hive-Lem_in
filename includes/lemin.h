#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/libft.h"

typedef struct		s_index
{
	int				index;
	struct s_index	*next;
}					t_index;

typedef struct		s_path
{
	int				nbr;
	int				len;
	int				found;
	t_index			*move_head;
	struct s_index	*move;
	struct s_path	*next;
}					t_path;

typedef struct  s_room
{
	char	**rooms;
	int		**links;
	int		end;
	int		ants;
	int		*distance;
	int		*used;
	int		total;
	int		path_nbr;
	int		len;
	int		longest_path;
	int		max_paths;
	t_path	*head;
	t_path	*final_head;
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

// error handling
int	parsing_phase(t_room *pass, char **input);
int	error(int err);
int	only_digits(char *str, int *i);
int	is_coordinates(char *str);
int	is_connection(char *str);
int	create(t_room *pass, char *input);

// parsing
void	match_in(char *str, char *input, t_room *pass, int k);
int		count_in(char *str, char *input, char **rooms);
int		addi_diff(char *start, char *finish);
int		dash_in_section(char *full, char *inside);
int		is_dash(char *str);

// path finder
void	distance(t_room *pass);
int		path_finder(t_room *pass);
int		len_array(int *links);
void	create_index(t_index **move, t_path *path, int i);
void	create_path(t_path **path, t_room *pass);
void	initialize_path_finder(t_path **path, t_room *pass);
t_path	*cpy_pth(t_path *file);
void	del_first_index(t_path *file);
void	del_last_path(t_path **path, t_room *pass);

#endif
