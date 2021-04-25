# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/31 18:40:15 by zskeeter          #+#    #+#              #
#    Updated: 2021/04/25 20:32:16 by zskeeter         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ft_memset.c ft_atoi.c ft_bzero.c ft_memmove.c ft_memcpy.c ft_memccpy.c \
		ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
		ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_strdup.c \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_toupper.c ft_tolower.c ft_calloc.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_split.c \
		ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c

BNS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
	  ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
	  ft_lstiter.c ft_lstmap.c

SRCOBJS = $(SRCS:.c=.o)
BNSOBJS = $(BNS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCOBJS) libft.h
		ar -rcs $(NAME) $(SRCOBJS)

bonus: $(SRCOBJS) $(BNSOBJS) libft.h
	ar -rcs $(NAME) $(SRCOBJS) $(BNSOBJS)

clean:
	rm -f $(SRCOBJS) $(BNSOBJS)

fclean: clean
	rm -f $(NAME) $(BNSOBJS)

re: clean fclean all
