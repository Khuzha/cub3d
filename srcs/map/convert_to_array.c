#include "../../cub.h"

size_t	get_width(t_list *list, size_t height)
{
	size_t	width;

	width = 0;
	while (height)
	{
		width = get_max(width, ft_strlen(list->content));
		list = list->next;
		height--;
	}
	return (width);
}

size_t	get_height(t_list *list)
{
	size_t	counter;

	counter = 0;
	while (list->next)
	{
		list = list->next;
		counter++;
	}
	return (counter);
}

void	convert_to_array(t_list *list, t_map *data)
{
	size_t	width;
	size_t	height;
	printf("convert_to_array, str = %s\n", list->content);
	
	height = get_height(list);
	width = get_width(list, height);
	printf("height = %lu, width = %lu\n", height, width);
	data++;
	width = 0;
}