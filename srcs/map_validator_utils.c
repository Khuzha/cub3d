#include "../cub.h"

void	fill_resolution(t_map *map, int res_x, int res_y)
{
	map->res_x = res_x;
	map->res_y = res_y;
}

void	fill_wside(t_map *map, char *wside, char *file)
{
	if (!ft_strncmp(wside, "WE", 2))
		map->we = file;
	if (!ft_strncmp(wside, "EA", 2))
		map->ea = file;
	if (!ft_strncmp(wside, "SO", 2))
		map->so = file;
	if (!ft_strncmp(wside, "NO", 2))
		map->no = file;
}