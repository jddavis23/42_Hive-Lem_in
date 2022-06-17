# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molesen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 11:33:19 by molesen           #+#    #+#              #
#    Updated: 2022/02/09 12:21:28 by molesen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc -Wall -Wextra -Werror -I ./libft

SRC = main.c
SRC += flags.c
SRC += specifier.c
SRC += print_str.c
SRC += prec_str.c
SRC += width_str.c
SRC += csp_print.c
SRC += diu_print.c
SRC += ox_print.c
SRC += fp_print.c
SRC += ftoa.c
SRC += ftoa_end.c
SRC += bonus.c
SRC += error.c

OBJ = $(SRC:.c=.o)

MAKELIB = make -C libft/ fclean && make -C libft/

all: $(NAME)
$(NAME): $(SRC)
	@$(MAKELIB)
	@$(CC) -c -I ./includes $(SRC)
	@ar rc $(NAME) $(OBJ) libft/*.o
	@ranlib $(NAME)

clean:
	@/bin/rm -f *.o
	@make -C libft/ clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
