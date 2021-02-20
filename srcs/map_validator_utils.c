#include "../cub.h"

void	fill_resolution(t_map *map, int res_x, int res_y)
{
	if (map->res_x || map->res_y)
		return error("Invalid map (resolution)");
	map->res_x = res_x;
	map->res_y = res_y;
}

void	define_file(t_map *map, char *type, char *file)
{
	if (!ft_strncmp(type, "WE", 2) && !map->we)
		map->we = file;
	else if (!ft_strncmp(type, "EA", 2) && !map->ea)
		map->ea = file;
	else if (!ft_strncmp(type, "SO", 2) && !map->so)
		map->so = file;
	else if (!ft_strncmp(type, "NO", 2) && !map->no)
		map->no = file;
	else if (!ft_strncmp(type, "S", 1) && !map->s)
		map->s = file;
	else
		error("Invalid map (textures)");
}

void	store_colors(t_map *map, char c, char *str)
{
	char	**set;

	set = ft_split(str, ',');
	if (c == 'C')
	{
		map->c_colors.r = ft_atoi(set[0]);
		map->c_colors.g = ft_atoi(set[1]);
		map->c_colors.b = ft_atoi(set[2]);
	}
	if (c == 'F')
	{
		map->f_colors.r = ft_atoi(set[0]);
		map->f_colors.g = ft_atoi(set[1]);
		map->f_colors.b = ft_atoi(set[2]);
	}
}