/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:09:31 by molesen           #+#    #+#             */
/*   Updated: 2022/09/12 10:09:33 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/libft.h"

typedef struct s_index
{
	int				index;
	struct s_index	*next;
}					t_index;

typedef struct s_path
{
	int				nbr;
	int				len;
	int				max_ants;
	t_index			*move_head;
	struct s_index	*move;
	struct s_path	*next;
	struct s_path	*prev;
}					t_path;

typedef struct s_ants
{
	int				ant;
	t_index			*move;
	struct s_ants	*next;
	struct s_ants	*prev;
}					t_ants;

typedef struct s_input
{
	char			*input;
	int				capacity;
	int				current;
}					t_input;

typedef struct s_connect
{
	int					count;
	int					current_room;
	struct s_connect	*next;
}					t_connect;

typedef struct s_room
{
	char		**rooms;
	int			**links;
	int			**info;
	int			end;
	int			ants;
	int			total;
	int			min_row;
	int			hold;//lock_path
	int			next;//lock_path
	int			print_row;//flag
	int			print_paths;
	int			print_len;
	int			print_count;
	t_connect	*tmp_con;
	t_connect	*head_con;
	t_path		*final_head;
}				t_room;

typedef enum info
{
	PATH,//path nbr in every rooms index
	PREV,//rooms index we just came from
	LEN,//len of path in this room
	CURRENT,//room current path is on
	NEXT,//room index we are going to
	JUMP,//entry point of non locked path into a locked path
	LOCKED,
	MOVE,
}	t_info;

typedef enum error_message
{
	NO_ANTS,
	TOO_MANY_ANTS,
	NON_DIGIT_ANTS,
	COMMAND,
	COORDINATES,
	CONNECTION,
}	t_error_message;

// error handling
int		file_save(t_room *pass, t_input **build);
int		only_digits(char *str, int *i);
int		is_coordinates(char *str);
int		is_connection(char *str);
int		create(t_room *pass, t_input **build);
int		error(int err);
int		error_free(t_room *pass, t_input **build, int j, int first);
int		error_path(t_room *pass, t_input **build, int first);
int		**free2d_int(int **links, int j, int end);

void	del_first_index(t_path *file);//use in error freeing function

// parsing
void	match_in(char *str, char *input, t_room *pass, int k);
//int		match_in(char *str, char *input, char **rooms, int k, t_room *pass);
int		count_in(char *str, char *input, t_room *pass);
int		addi_diff(char *start, char *finish);
int		dash_in_section(char *full, char *inside);
int		is_dash(char *str);

// path finder
int		initialize_path_finder(t_room *pass, t_input **build);
int		len_array(int *links);
int		path_finder(t_path **path, t_room *pass);
void	del_last_path(t_path **path, t_room *pass);
void	free_and_del_path(t_path **path, t_room *pass);
void	del_path(t_path **path);
int		copy_to_path(t_room *pass, t_path **path, int **len);

// path select
void	initialize_path(t_room *pass);
int		path_select(t_path **path, t_room *pass, int **len, int *increase);
int		create_path(t_path **path, t_room *pass, int nbr, int len);
int		create_index(t_index **move, t_path **path, int i);

// breadth first
void	breadth_first(t_room *pass, int indx, int i);
void	travel_locked_path(t_room *pass, int indx, int *i);
void	remove_branch(t_room *pass, int *i);
void	set_correct_current_index(t_room *pass, int *i, int new_indx);
void	update_non_locked_path(t_room *pass, int indx, int j, int *i);
void	update_locked_path(t_room *pass, int indx, int j, int *i);
void	calc_len(t_room *pass, int **len);
int		create_len(int *array, int **len);
void	reset_len(t_room *pass, int **len);
int		current_len(t_room *pass);
int		current_true(t_room *pass);
int		first_algorithm(t_path **path, t_room *pass, int **len, int first);
int		second_algorithm(t_path **path, t_room *pass, int **len, int i);
int		free_len(int **len);

void	lock_path_init(t_room *pass, int indx);
void	lock_path(t_room *pass, int indx);
void	info_set_to_zero(t_room *pass, int i);
int		on_lock_path(t_room *pass, int *i, int c_len);

//didnt know where to put
int		create_connect(t_room *pass, int j);

// solve
void	solve(t_room *pass, t_input **build);
void	create_ants(t_ants **ants_move, int ant, t_index *index);
void	solve_calc(t_room *pass, t_ants *ants_move, t_ants *head);
void	print_count(int print_count, int line);
t_ants	*print_ants_move(t_ants *head, t_room *pass, int line);

// print
void	printf_struct(t_room *pass);

//delete this later
void	print_output(t_room *pass);
#endif
