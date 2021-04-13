NAME = cub3D.lib
FINALNAME = cub3D
SRCS =	main.c gnl/get_next_line.c \
		srcs/list/utils.c srcs/list/list_validator.c \
		srcs/list/list_validator_utils.c srcs/list/list_validator_utils2.c \
		srcs/map/convert_to_array.c srcs/map/validation.c \
		srcs/utils/lib_utils.c srcs/utils/error.c srcs/utils/quicksort.c \
		srcs/gui/start.c srcs/map/init_sprites.c

SRCOBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

$(NAME): $(SRCOBJS)
	make bonus -C libft
	ar -rcs $(NAME) $(SRCOBJS) libft/*.o 
	gcc $(NAME) -framework OpenGL -framework AppKit minilibx/libmlx.a -g -o $(FINALNAME)

all: $(NAME)

clean :
		rm -rf $(SRCOBJS) $(NAME)
		make clean -C libft

fclean : clean
		make fclean -C libft
		rm -rf $(FINALNAME)

re :  fclean all
