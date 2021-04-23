#include "../../cub.h"

void	fill_resolution(t_map *map, char *res_x, char *res_y)
{
	int trash;

	if (ft_strlen(res_x) > 5)
		mlx_get_screen_size(&map->res.x, &trash);
	else
		map->res.x = ft_atoi(res_x);
	if (ft_strlen(res_y) > 5)
		mlx_get_screen_size(&trash, &map->res.y);
	else
		map->res.y = ft_atoi(res_y);
}

void	define_file(t_map *map, char *type, char *file)
{
	int fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Invalid map (file couldn't be open)");
	if (!ft_strncmp(type, "WE", 3) && !map->we)
		map->we = file;
	else if (!ft_strncmp(type, "EA", 3) && !map->ea)
		map->ea = file;
	else if (!ft_strncmp(type, "SO", 3) && !map->so)
		map->so = file;
	else if (!ft_strncmp(type, "NO", 3) && !map->no)
		map->no = file;
	else if (!ft_strncmp(type, "S", 2) && !map->s)
		map->s = file;
	else
		error("Invalid map (textures)");
}

int		count_commas(char *str)
{
	int res;

	res = 0;
	while (*str)
	{
		if (*str == ',')
			res++;
		str++;
	}
	return (res);
}

// void	validate_colors(char **arr)
// {
// 	while (*arr)
// 	{
// 		printf("*arr = |%s|\n", *arr);
// 		if (!ft_isnumber(*arr))
// 			error("Invalid map (colors)");
// 		arr++;
// 	}
// }

void	store_colors(t_map *map, char type, char *str)
{
	char	**set;

	str += 2;
	if (count_commas(str) != 2)
		error("Invalid map (commas in colors)");
	set = ft_split(str, ',');
	if (type == 'C')
	{
		if (map->c_colors.defined)
			error("Ceiling colors are repeating");
		map->c_colors.defined = 1;
		map->c_colors.r = ft_atoi(set[0]);
		map->c_colors.g = ft_atoi(set[1]);
		map->c_colors.b = ft_atoi(set[2]);
	}
	if (type == 'F')
	{
		if (map->f_colors.defined)
			error("Floor colors are repeating");
		map->f_colors.defined = 1;
		map->f_colors.r = ft_atoi(set[0]);
		map->f_colors.g = ft_atoi(set[1]);
		map->f_colors.b = ft_atoi(set[2]);
	}
}

int		is_param(char *str)
{
	if (ft_strncmp(str, "R", 2) &&
		ft_strncmp(str, "WE", 3) &&
		ft_strncmp(str, "EA", 3) &&
		ft_strncmp(str, "SO", 3) &&
		ft_strncmp(str, "NO", 3) &&
		ft_strncmp(str, "S", 2) &&
		ft_strncmp(str, "C", 2) &&
		ft_strncmp(str, "F", 2))
	{
		return (0);
	}
	return (1);
}