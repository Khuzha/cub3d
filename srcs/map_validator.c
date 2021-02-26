#include "../cub.h"

char	fill_struct(t_map *map, char **arr, char *str)
{
	// if (arr[0] && !is_param(arr[0])) {
	// 	error("Invalid map (parameters)");
	// }
	if (!arr[0] && *str == ' ')
		error("Invalid map (empty line contains spaces)");
	if (arr[0] && arr[0][0] == 'R' && !arr[0][1] && ft_isnumber(arr[1]) && ft_isnumber(arr[2]) && !arr[3])
		fill_resolution(map, arr[1], arr[2]);
	if ((is_wside(arr[0]) || (arr[0] && arr[0][0] == 'S')) && is_xpm_file(arr[1]) && !arr[2])
		define_file(map, arr[0], arr[1]);
	if (arr[0] && arr[0][0] && arr[1] && arr[0] && ft_strchr("CF", arr[0][0]) && !arr[0][1] && is_colors_set(str))
		store_colors(map, arr[0][0], str);
	return (0);
}

void	check_map(t_map *map)
{
	if (map->res.x <= 0 || map->res.y <= 0 ||
		!map->we || !ft_strlen(map->we) || !map->ea || !ft_strlen(map->ea) ||
		!map->so || !ft_strlen(map->so) || !map->no || !ft_strlen(map->no) ||
		!map->s || !ft_strlen(map->s) ||
		!map->c_colors.defined || !map->f_colors.defined ||
		map->c_colors.r > 255 || map->c_colors.g > 255 || map->c_colors.b > 255 ||
		map->f_colors.r > 255 || map->f_colors.g > 255 || map->f_colors.b > 255)
		error("Invalid map");
}

int		validate_map(t_map *map)
{
	while (map->list->next)
	{
		fill_struct(map, ft_split(map->list->content, ' '), map->list->content); // TODO: free ft_split
		map->list = map->list->next;
	}
	check_map(map);
	printf("res_x = %d, res_y = %d, x_max = %d, y_max = %d \nwe = %s, ea = %s, so = %s, no = %s, \nsprite = %s \n", map->res.x, map->res.y, map->res.x_max, map->res.y_max, map->we, map->ea, map->so, map->no, map->s);
	printf("c = %d,%d,%d; f = %d,%d,%d\n", map->c_colors.r, map->c_colors.g, map->c_colors.b, map->f_colors.r, map->f_colors.g, map->f_colors.b);
	return (1);
}
