# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molesen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/12 10:09:38 by molesen           #+#    #+#              #
#    Updated: 2022/09/12 10:09:40 by molesen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

CC = gcc -Wall -Wextra -Werror

C = lemin/

SRC = $(C)main.c
SRC += $(C)error.c
SRC += $(C)error_free.c
SRC += $(C)file_save.c
SRC += $(C)file_save_line.c
SRC += $(C)file_check.c
SRC += $(C)parse.c
SRC += $(C)parse_count.c
SRC += $(C)parse_collect.c
SRC += $(C)path_init.c
SRC += $(C)path_finder.c
SRC += $(C)path_create.c
SRC += $(C)path_select.c
SRC += $(C)algorithm_first.c
SRC += $(C)algorithm_second.c
SRC += $(C)breadth_first.c
SRC += $(C)breadth_locked.c
SRC += $(C)lock_init.c
SRC += $(C)lock_path.c
SRC += $(C)path_len.c
SRC += $(C)solve.c
SRC += $(C)solve_calc.c

MAKELIB = make -C libft/ fclean && make -C libft/

all: $(NAME)
$(NAME): $(SRC)
	$(MAKELIB)
	$(CC) $(SRC) ./libft/libft.a -o $(NAME)

clean:
	/bin/rm -f *.o
	make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
