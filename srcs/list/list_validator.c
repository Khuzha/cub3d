#include "../../cub.h"

void	fill_struct(t_map *map, char **arr, char *str)
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
}

void	check_map(t_map *map)
{
	// printf("res.x = %d, res.y = %d\n", map->res.x, map->res.y);
	// printf("f def = %d, c def = %d\n",map->f_colors.defined, map->c_colors.defined);
	if ((map->res.x <= 0 && !map->res.x_max) || (map->res.y <= 0 && !map->res.y_max) ||
		!map->we || !ft_strlen(map->we) || !map->ea || !ft_strlen(map->ea) ||
		!map->so || !ft_strlen(map->so) || !map->no || !ft_strlen(map->no) ||
		!map->s || !ft_strlen(map->s) ||
		!map->c_colors.defined || !map->f_colors.defined ||
		map->c_colors.r > 255 || map->c_colors.g > 255 || map->c_colors.b > 255 ||
		map->f_colors.r > 255 || map->f_colors.g > 255 || map->f_colors.b > 255)
		error("Invalid map");
}

void		iterate_list(t_map *map)
{
	char	**arr;
	char	was_map;

	was_map = 0;
	while (map->list->next)
	{
		arr = ft_split(map->list->content, ' ');
		if (arr[0] && !(is_param(arr[0]) && arr[1]) && !is_map_line(map->list->content))
		{
			// printf("map started, str = %s\n", map->list->content);
			was_map = 1;
			// printf("before convert_to_array\n");
			convert_to_array(map->list, map);
			// printf("after convert_to_array\n");
			break ;
		}
		fill_struct(map, arr, map->list->content); // TODO: free ft_split
		map->list = map->list->next;
		free(arr);
	}
	// printf("iterate_list bef call check_map\n");
	if (!was_map)
		error("No map found");
	// printf("bef check_map\n");
	check_map(map);
	// free(arr);
}
