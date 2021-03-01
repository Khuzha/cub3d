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
	if (!counter)
		error("No player found");
	// printf("found %d players\n", (int)counter);
}

char	emp(char c)
{
	if (c == ' ' || c == 0)
		return (1);
	else
		return (0);
}

void	check_char(char c)
{
	if (!ft_strchr("WENS", c) && c != '0' && c != '@')
		error("Map validation failed");
}

void	flood_fill(char **arr, size_t x, size_t y)
{
	printf("x = %lu, y = %lu\n", x, y);
	if (arr[y] && arr[y][x] != '1')
		check_char(arr[y][x]);
	if (x >= 0 && y >= 0 && (arr[y][x] == '0' || ft_strchr("WENS", arr[y][x])))
	{
		arr[y][x] = '@';
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

	printf("bef find player\n");
	find_player(arr, &x, &y);
	printf("bef flood_fill\n");
	flood_fill(arr, x, y);
	data++;
}