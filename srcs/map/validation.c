#include "../../cub.h"

void	find_player(char **arr, size_t *pos_x, size_t *pos_y)
{
	size_t	x;
	size_t	y;
	char	counter;

	x = 0;
	y = 0;
	counter = 0;
	while (arr[y])
	{
		while (arr[y][x])
		{
			if (ft_strchr("WENS", arr[y][x]))
			{
				*pos_x = x;
				*pos_y = y;
				counter++;
			}
			if (counter > 1)
				error("Wrong players count");
			x++;
		}
		x = 0;
		y++;
	}
	printf("found %d players\n", (int)counter);
}

void	flood_fill(char **arr, size_t x, size_t y)
{
	if (x >= 0 && y >= 0 && (arr[y][x] == '0' || ft_strchr("WENS", arr[y][x])))
	{
		flood_fill(arr, x + 1, y + 1);
		flood_fill(arr, x + 1, y);
		flood_fill(arr, x + 1, y - 1);
		flood_fill(arr, x, y - 1);
		flood_fill(arr, x - 1, y - 1);
		flood_fill(arr, x - 1, y);
		flood_fill(arr, x - 1, y + 1);
	}
}

void	validate_map(char **arr, t_map *data)
{
	size_t	x;
	size_t	y;

	find_player(arr, &x, &y);
	flood_fill(arr, x, y);
	data++;
}