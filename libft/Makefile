# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molesen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 12:16:20 by molesen           #+#    #+#              #
#    Updated: 2021/12/15 09:51:20 by molesen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc -Wall -Wextra -Werror

SRCS = ft_atoi.c
SRCS += ft_bzero.c
SRCS += ft_isalnum.c
SRCS += ft_isalpha.c
SRCS += ft_isascii.c
SRCS += ft_isdigit.c
SRCS += ft_isxdigit.c
SRCS += ft_isoctal.c
SRCS += ft_isprint.c
SRCS += ft_isspace.c
SRCS += ft_itoa.c
SRCS += ft_lstadd.c
SRCS += ft_lstdel.c
SRCS += ft_lstdelone.c
SRCS += ft_lstiter.c
SRCS += ft_lstmap.c
SRCS += ft_lstnew.c
SRCS += ft_memalloc.c
SRCS += ft_memccpy.c
SRCS += ft_memchr.c
SRCS += ft_memcmp.c
SRCS += ft_memcpy.c
SRCS += ft_memdel.c
SRCS += ft_memmove.c
SRCS += ft_memset.c
SRCS += ft_putchar_fd.c
SRCS += ft_putchar.c
SRCS += ft_putendl_fd.c
SRCS += ft_putendl.c
SRCS += ft_putnbr_fd.c
SRCS += ft_putnbr.c
SRCS += ft_putstr_fd.c
SRCS += ft_putstr.c
SRCS += ft_strcat.c
SRCS += ft_strchr.c
SRCS += ft_strclr.c
SRCS += ft_strcmp.c
SRCS += ft_strcpy.c
SRCS += ft_strdel.c
SRCS += ft_strdup.c
SRCS += ft_strequ.c
SRCS += ft_striter.c
SRCS += ft_striteri.c
SRCS += ft_strjoin.c
SRCS += ft_strlcat.c
SRCS += ft_strlen.c
SRCS += ft_strmap.c
SRCS += ft_strmapi.c
SRCS += ft_strncat.c
SRCS += ft_strncmp.c
SRCS += ft_strncpy.c
SRCS += ft_strnequ.c
SRCS += ft_strnew.c
SRCS += ft_strnstr.c
SRCS += ft_strrchr.c
SRCS += ft_strsplit.c
SRCS += ft_strstr.c
SRCS += ft_strsub.c
SRCS += ft_strtrim.c
SRCS += ft_tolower.c
SRCS += ft_toupper.c
SRCS += ft_begin_of_str.c
SRCS += ft_end_of_str.c
SRCS += ft_isspace_s.c
SRCS += ft_strlen_stop.c
SRCS += ft_word_count.c
SRCS += ft_lstdel_content.c
SRCS += ft_lstprint.c
SRCS += ft_lstprint_size.c
SRCS += ft_free2d.c
SRCS += get_next_line.c
SRCS += ft_itoa_base.c
SRCS += ft_strrev.c
SRCS += ft_int_len.c
SRCS += ft_long_len.c
SRCS += ft_ulong_len.c
SRCS += ft_htoa.c
SRCS += ft_pow.c
SRCS += ft_ulltoa.c
SRCS += ft_ulltoa_base.c
SRCS += ft_strrev_len.c
SRCS += ft_addr_to_str.c
SRCS += ft_printf.c
SRCS += ft_printf_flags.c
SRCS += ft_printf_specifier.c
SRCS += ft_printf_print_str.c
SRCS += ft_printf_prec_str.c
SRCS += ft_printf_width_str.c
SRCS += ft_printf_csp_print.c
SRCS += ft_printf_diu_print.c
SRCS += ft_printf_ox_print.c
SRCS += ft_printf_fp_print.c
SRCS += ft_printf_ftoa.c
SRCS += ft_printf_ftoa_end.c
SRCS += ft_printf_bonus.c
SRCS += ft_printf_error.c
SRCS += ft_strlchr.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)
$(NAME): $(SRCS)
	@$(CC) -c -I ./includes $(SRCS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

clean:
	@/bin/rm -f *.o

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
