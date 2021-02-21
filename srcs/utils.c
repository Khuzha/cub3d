#include "../cub.h"

void	init_str_and_map(char **str, t_map *map)
{
	*str = NULL;
	map->list = NULL;
	map->res.x = 0;
	map->res.y = 0;
	map->res.x_max = 0;
	map->res.y_max = 0;
	map->we = NULL;
	map->ea = NULL;
	map->so = NULL;
	map->no = NULL;
	map->c_colors.defined = 0;
	map->f_colors.defined = 0;
}