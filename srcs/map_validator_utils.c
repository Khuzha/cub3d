#include "../cub.h"

void	fill_resolution(t_map *map, int res_x, int res_y)
{
	if (map->res.x || map->res.y)
		return error("Invalid map (resolution)");
	map->res.x = res_x;
	map->res.y = res_y;
}

void	define_file(t_map *map, char *type, char *file)
{
	int fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Invalid map (file didn't open)");
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

void	store_colors(t_map *map, char type, char *str)
{
	char	**set;

	str += 2;
	set = ft_split(str, ',');
	if (type == 'C')
	{
		map->c_colors.defined = 1;
		map->c_colors.r = ft_atoi(set[0]);
		map->c_colors.g = ft_atoi(set[1]);
		map->c_colors.b = ft_atoi(set[2]);
	}
	if (type == 'F')
	{
		map->f_colors.defined = 1;
		map->f_colors.r = ft_atoi(set[0]);
		map->f_colors.g = ft_atoi(set[1]);
		map->f_colors.b = ft_atoi(set[2]);
	}
}

int		is_param(char *str)
{
	printf("str = |%s|\n", str);
	if (ft_strncmp(str, "R", 1) &&
		ft_strncmp(str, "WE", 2) &&
		ft_strncmp(str, "EA", 2) &&
		ft_strncmp(str, "SO", 2) &&
		ft_strncmp(str, "NO", 2) &&
		ft_strncmp(str, "S", 1) &&
		ft_strncmp(str, "C", 1) &&
		ft_strncmp(str, "F", 1))
	{
		return (0);
	}
	return (1);
}