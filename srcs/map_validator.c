#include "../cub.h"

char	get_line_type(t_map *map, char **arr)
{
	if (arr[0] && arr[0][0] == 'R' && !arr[0][1] && ft_isnumber(arr[1]) && ft_isnumber(arr[2]))
		fill_resolution(map, ft_atoi(arr[1]), ft_atoi(arr[2]));
	if ((is_wside(arr[0]) || (arr[0] && arr[0][0] == 'S')) && is_xpm_file(arr[1]) && !arr[2])
		define_file(map, arr[0], arr[1]);
	// if (arr[0] && ft_strchr("CF", arr[0][0]) && !arr[0][1] && is_colors_set(arr[1]))
	// 	store_colors(map, arr[0][0], arr[1]);
	return (0);
}

int		validate_map(t_map *map)
{
	printf("enter validate\n");
	while (map->list->next)
	{
		printf("str = |%s|\n", map->list->content);
		get_line_type(map, ft_split(map->list->content, ' '));
		map->list = map->list->next;
	}
	printf("res_x = %d, \nres_y = %d, we = %s, ea = %s, so = %s, no = %s, \nsprite = %s \n", map->res_x, map->res_y, map->we, map->ea, map->so, map->no, map->s);
	// printf("c = %s, f =  \n", map->c);
	return (1);
}
