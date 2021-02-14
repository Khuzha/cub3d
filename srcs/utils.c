#include "../cub.h"

void	init_str_and_map(char **str, t_map **map)
{
	*str = NULL;
	(*map)->list = NULL;
	(*map)->res_x = 0;
	(*map)->res_y = 0;
}