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

	counter = 1;
	while (list->next)
	{
		list = list->next;
		counter++;
	}
	return (counter);
}

void	init_lines(char **arr, size_t width)
{
	while (*arr)
	{
		if (!(*arr = ft_calloc(sizeof(char) * width, width)))
			error("Malloc error");
		arr++;
	}
}

void	fill_lines(char **arr, t_list *list, size_t height)
{
	size_t	i;

	i = 0;
	while (i < height)
	{
		arr[i] = list->content;
		i++;
		list = list->next;
	}
	list++;
}

void	convert_to_array(t_list *list, t_map *data)
{
	size_t	width;
	size_t	height;
	char	**arr;

	height = get_height(list);
	width = get_width(list, height);
	if (!(arr = ft_calloc(sizeof(char *) * (height + 1), height + 1)))
		error("Malloc error");
	// printf("bef init_lines\n");
	init_lines(arr, width);
	// printf("bef fill_lines\n");
	fill_lines(arr, list, height);
	// printf("bef validate_map\n");
	validate_map(arr, data);
	// printf("aft validate_map\n");
}
