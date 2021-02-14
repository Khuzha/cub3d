#include "../cub.h"

void	fill_resolution(t_map *map, int res_x, int res_y)
{
	map->res_x = res_x;
	map->res_y = res_y;
}

int		is_dir(char *str)
{
	if (!str || !(*str) ||
		(ft_strncmp(str, "WE", 3) &&
		ft_strncmp(str, "EA", 3) &&
		ft_strncmp(str, "SO", 3) &&
		ft_strncmp(str, "NO", 3)))
		return (0);
	return (1);
}