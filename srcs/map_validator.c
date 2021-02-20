#include "../cub.h"

char	get_line_type(t_map *map, char **arr, char *str)
{
	// if (arr[0] && !is_param(arr[0])) {
	// 	error("Invalid map (parameters)");
	// }
	if (arr[0] && arr[0][0] == 'R' && !arr[0][1] && ft_isnumber(arr[1]) && ft_isnumber(arr[2]))
		fill_resolution(map, ft_atoi(arr[1]), ft_atoi(arr[2]));
	if ((is_wside(arr[0]) || (arr[0] && arr[0][0] == 'S')) && is_xpm_file(arr[1]) && !arr[2])
		define_file(map, arr[0], arr[1]);
	// printf("ics = %d, str = |%s|\n", is_colors_set(str), str);
	if (arr[0] && arr[0][0] && arr[1])
	if (arr[0] && ft_strchr("CF", arr[0][0]) && !arr[0][1] && is_colors_set(str))
		store_colors(map, arr[0][0], str);
	return (0);
}

int		validate_map(t_map *map)
{
	// char **arr;

	while (map->list->next)
	{
		// printf("str = |%s|\n", map->list->content);
		get_line_type(map, ft_split(map->list->content, ' '), map->list->content); // TODO: free ft_split
		map->list = map->list->next;
	}
	printf("res_x = %d, \nres_y = %d, we = %s, ea = %s, so = %s, no = %s, \nsprite = %s \n", map->res_x, map->res_y, map->we, map->ea, map->so, map->no, map->s);
	printf("c = %d,%d,%d; f = %d,%d,%d\n", map->c_colors.r, map->c_colors.g, map->c_colors.b, map->f_colors.r, map->f_colors.g, map->f_colors.b);
	return (1);
}
