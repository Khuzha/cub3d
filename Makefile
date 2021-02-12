# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/05 23:28:24 by zskeeter          #+#    #+#              #
#    Updated: 2021/02/05 23:28:25 by zskeeter         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRCS =	printf.c utils.c utils_2.c parser_utils.c \
		handlers/print_d.c handlers/print_c.c handlers/print_s.c \
		handlers/print_p.c handlers/print_x.c handlers/print_u.c \
		handlers/print_d_utils.c handlers/print_p_utils.c \
		handlers/print_u_utils.c handlers/print_x_utils.c

SRCOBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

$(NAME): $(SRCOBJS) printf.h
	make -C libft
	ar -rcs $(NAME) $(SRCOBJS) libft/*.o

all: $(NAME)

clean : 
		rm -rf $(SRCOBJS) 
		make -C libft/ clean

fclean : clean
		make -C libft/ fclean
		rm -rf $(NAME)

re :  fclean all 

d:
	gcc -Wall -Wextra -Werror -g printf.c atoi.c print_d.c

t: fclean all
	gcc -Wall -Wextra -Werror -g main.c libftprintf.a

f: fclean all
	gcc -Wall -Wextra -Werror -g -fsanitize=address main.c libftprintf.a

w: fclean all
	gcc -g main.c libftprintf.a

dbg: fclean
	gcc -g main.c $(SRCS) libft/ft_itoa.c libft/ft_atoi.c libft/ft_strlen.c libft/ft_substr.c libft/ft_isdigit.c libft/ft_memcpy.c libft/ft_memset.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_strdup.c