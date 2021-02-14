#include "../cub.h"



char	get_line_type(t_map *map, char **arr)
{
	size_t i = 0;

	while (arr[i])
	{
		if (arr[i][0] == 'R' && !arr[i][1] && ft_isnumber(arr[i + 1]) && ft_isnumber(arr[i + 2]))
			fill_resolution(map, ft_atoi(arr[i + 1]), ft_atoi(arr[i + 2]));
		i++;
	}



	return (0);
}

int		validate_map(t_map *map)
{
	while (map->list->next)
	{
		get_line_type(map, ft_split(map->list->content, ' '));
		printf("\n");
		// char **arr = ft_split(map_list->content, ' ');

		// printf("type = %c, str = |%s|\n", get_line_type(map_list->content), map_list->content);
		map->list = map->list->next;
	}
	printf("res_x = %d, res_y = %d", map->res_x, map->res_y);
	return (1);
}
