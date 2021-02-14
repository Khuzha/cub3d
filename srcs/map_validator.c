#include "../cub.h"

char	get_line_type(t_map *map, char **arr)
{
	if (arr[0] && arr[0][0] == 'R' && !arr[0][1] && ft_isnumber(arr[1]) && ft_isnumber(arr[2]))
		fill_resolution(map, ft_atoi(arr[1]), ft_atoi(arr[2]));
	if (is_wside(arr[0]) && is_xpm_file(arr[1]) && !arr[2])
		fill_wside(map, arr[0], arr[1]);
	return (0);
}

int		validate_map(t_map *map)
{
	while (map->list->next)
	{
		get_line_type(map, ft_split(map->list->content, ' '));
		map->list = map->list->next;
	}
	printf("res_x = %d, res_y = %d, we = %s, ea = %s, so = %s, no = %s\n", map->res_x, map->res_y, map->we, map->ea, map->so, map->no);
	return (1);
}
