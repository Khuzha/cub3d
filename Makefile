NAME = cub3D.lib
FINALNAME = cub3D
SRCS =	main.c gnl/get_next_line.c \
		srcs/list/utils.c srcs/list/list_validator.c \
		srcs/list/list_validator_utils.c srcs/list/list_validator_utils2.c \
		srcs/map/convert_to_array.c srcs/map/validation.c \
		srcs/utils/lib_utils.c srcs/utils/error.c srcs/utils/sorting.c \
		srcs/gui/start.c srcs/gui/draw_sprites.c srcs/gui/drawer.c \
		srcs/gui/handlers.c srcs/gui/initions.c srcs/gui/key_hooks.c \
		srcs/gui/pixels.c srcs/gui/rotations.c srcs/gui/steps.c \
		srcs/gui/utils.c srcs/gui/utils2.c \
		srcs/map/init_sprites.c srcs/map/utils.c \
		srcs/screenshot/save.c

SRCOBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

$(NAME): $(SRCOBJS)
	make bonus -C libft
	make -C minilibx
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
