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

void	init_lines(char **arr, size_t width)
{
	size_t	i;

	while (*arr)
	{
		if (!(*arr = malloc(sizeof(char) * width)))
			error("Malloc error");
		i = 0;
		while (i < width)
		{
			*arr[i] = 0;
			i++;
		}
		arr++;
	}
}

// void	fill_lines(char **arr, t_list *list)
// {
// 	while (*arr)
// 	{
// 		// printf()
// 	}
// }

void	convert_to_array(t_list *list, t_map *data)
{
	size_t	width;
	size_t	height;
	char	**arr;

	height = get_height(list);
	width = get_width(list, height);
	if (!(arr = malloc(sizeof(char *) * height)))
		error("Malloc error");
	init_lines(arr, width);
	// fill_lines(arr, list);
	printf("height = %lu, width = %lu\n", height, width);
	data++;
	width = 0;
}