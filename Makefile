NAME = cub3D.lib
FINALNAME = cub3D
SRCS =	main.c gnl/get_next_line.c srcs/utils.c srcs/map_validator.c srcs/lib_utils.c \
	srcs/map_validator_utils.c srcs/map_validator_utils2.c

SRCOBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

$(NAME): $(SRCOBJS)
	make bonus -C libft
	ar -rcs $(NAME) $(SRCOBJS) libft/*.o
	gcc $(NAME) -g -o $(FINALNAME)

all: $(NAME)

clean :
		rm -rf $(SRCOBJS) $(NAME)
		make -C libft/ clean

fclean : clean
		make -C libft/ fclean
		rm -rf $(FINALNAME)

re :  fclean all
