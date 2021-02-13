#include "../cub.h"

int		validate_map(t_list *map_list)
{
	printf("str = |%s|\n", (const char *)map_list->content);
	while (map_list->next)
	{
		printf("str = |%s|\n", (const char *)map_list->content);
		map_list = map_list->next;
	}
	return (1);
}