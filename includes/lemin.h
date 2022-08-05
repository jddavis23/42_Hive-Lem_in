#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/libft.h"

typedef struct		s_index
{
	int		index;
	struct s_index	*next;
}					t_index;

typedef struct		s_path
{
	int				nbr;
	int				len;
	int				max_ants;
	t_index			*move_head;
	struct s_index	*move;
	struct s_path	*next;
	struct s_path	*prev;
}					t_path;

typedef struct		s_ants
{
	int				ant;
	t_index			*move;
	struct s_ants	*next;
	struct s_ants	*prev;
}					t_ants;

typedef struct  s_room
{
	char	**rooms;
	int		**links;
	int		*distance;
	int		**info;
	int		end;
	int		ants;
	int		total;
	int		row;
	t_path	*head;
	t_path	*final_head;
}				t_room;

typedef enum
{
	PATH,//path nbr in every rooms index
	PREV,//rooms index we just came from
	LEN,//len of path in this room
	CURRENT,//room current path is on
	CONNECT,//amount of connections in room
} info;

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
int	file_save(t_room *pass, char **input);
int	only_digits(char *str, int *i);
int	is_coordinates(char *str);
int	is_connection(char *str);
int	create(t_room *pass, char **input);
int	error(int err);
int	error_free(t_room *pass, char *input, int j, int first);
int	error_path(t_room *pass, char *input, int first);
int	**free2d_int(int **links, int j, int end);

// parsing
void	match_in(char *str, char *input, t_room *pass, int k);
//int		match_in(char *str, char *input, char **rooms, int k, t_room *pass);
int		count_in(char *str, char *input, char **rooms);
int		addi_diff(char *start, char *finish);
int		dash_in_section(char *full, char *inside);
int		is_dash(char *str);

// path finder
void	distance(t_room *pass);
int		initialize_path_finder(t_room *pass, char *input);
int		len_array(int *links);
void	create_index(t_index **move, t_path **path, int i);
void	create_path(t_path **path, t_room *pass, int nbr, int len);
void	path_finder(t_path **path, t_room *pass, int i, int **len);
t_path	*cpy_pth(t_path *file);
void	del_first_index(t_path *file);
void	del_last_path(t_path **path, t_room *pass);
void	solve(t_room *pass);
void	free_and_del_path(t_path **path, t_room *pass);
void	del_path(t_path **path);

#endif
