NAME = cub3D.lib
FINALNAME = cub3D
SRCS =	main.c gnl/get_next_line.c

SRCOBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

$(NAME): $(SRCOBJS)
	make bonus -C libft
	ar -rcs $(NAME) $(SRCOBJS) libft/*.o
	gcc $(NAME) -I libft/libft.h gnl/get_next_line.h
	gcc $(NAME) -o $(FINALNAME)

all: $(NAME)

clean : 
		rm -rf $(SRCOBJS) 
		make -C libft/ clean

fclean : clean
		make -C libft/ fclean
		rm -rf $(NAME)

re :  fclean all

d:
	make -C libft
	gcc main.c gnl/get_next_line.c libft/*.o
	# gcc $(CFLAGS) main.o get_next_line.o
