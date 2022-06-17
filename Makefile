NAME = lem-in
NAME2 = visu-hex

CC = gcc -Wall -Wextra -Werror

C = lemin/
S = vizualizer/

SRC = $(C)main.c

SRC2 = $(S)main.c
SRC2 += $(S)collect_data.c
SRC2 += $(S)make_visual.c

MAKELIB = make -C libft/ fclean && make -C libft/

all: $(NAME) $(NAME2)
$(NAME): $(SRC)
	$(MAKELIB)
	$(CC) $(SRC) ./libft/libft.a -o $(NAME)
$(NAME2): $(SRC2)
	$(MAKELIB)
	$(CC) $(SRC2) ./libft/libft.a -o $(NAME2)

clean:
	/bin/rm -f *.o
	make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME) $(NAME2)
	make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
