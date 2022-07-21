NAME = lem-in

CC = gcc -Wall -Wextra -Werror

C = lemin/

SRC = $(C)main.c
SRC += $(C)error.c
SRC += $(C)file_save.c
SRC += $(C)file_check.c
SRC += $(C)parse.c
SRC += $(C)parse_count.c
SRC += $(C)parse_collect.c
SRC += $(C)distance.c
SRC += $(C)path_init.c
SRC += $(C)path_finder.c
SRC += $(C)path_create.c
SRC += $(C)path_del_cpy.c
SRC += $(C)solve.c

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
