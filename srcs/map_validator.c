#include "../cub.h"



char	get_line_type(t_map *map, char **arr)
{
	size_t i = 0;

	if (arr[i][0] == 'R' && !arr[i][1] && ft_isnumber(arr[i + 1]) && ft_isnumber(arr[i + 2]) && !arr[i + 3])
		fill_resolution(map, ft_atoi(arr[i + 1]), ft_atoi(arr[i + 2]));

	return (0);
}

int		validate_map(t_map *map)
{
	while (map->list->next)
	{
		get_line_type(map, ft_split(map->list->content, ' '));
		map->list = map->list->next;
	}
	return (1);
}
