#include "../../cub.h"

void	check_sprite(char **arr, int y, int x, t_map *data)
{
	if (arr[y][x] == '2')
		data->s_count++;
}

void	find_player(char **arr, size_t *pos_x, size_t *pos_y, t_map *data)
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
				data->player = arr[y][x];
				counter++;
			}
			if (counter > 1)
				error("Wrong players count");
			check_sprite(arr, y, x, data);
			x++;
		}
		x = 0;
		y++;
	}
	if (!counter)
		error("No player found");
}

void	check_char(char c)
{
	if (!c || !ft_strchr("WENS", c))
		error("Map validation failed");
}

void	flood_fill(char **arr, size_t x, size_t y)
{
	if (x < 0 || y < 0)
		error("Map validation failed");
	if (arr[y] && arr[y][x] != '0' && arr[y][x] != '1'
		&& !ft_strchr("2@$", arr[y][x]))
		check_char(arr[y][x]);
	if (arr[y] && (arr[y][x] == '0' || ft_strchr("2WENS", arr[y][x])))
	{
		arr[y][x] = (arr[y][x] == '0' || ft_strchr("WENS", arr[y][x])) ? '@' : '$';
		flood_fill(arr, x + 1, y - 1);
		flood_fill(arr, x + 1, y);
		flood_fill(arr, x + 1, y + 1);
		flood_fill(arr, x, y + 1);
		flood_fill(arr, x - 1, y + 1);
		flood_fill(arr, x - 1, y);
		flood_fill(arr, x - 1, y - 1);
		flood_fill(arr, x, y - 1);
	}
}

void	ff_middleware(char **arr)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (arr && arr[y])
	{
		x = 0;
		while (arr[y][x])
		{
			if (ft_strchr("02WESN", arr[y][x]))
				flood_fill(arr, x, y);
			x++;
		}
		y++;
	}
}

void	validate_map(char **arr, t_map *data)
{
	size_t	x;
	size_t	y;

	find_player(arr, &x, &y, data);

	data->pos.x = (double)x;
	data->pos.y = (double)y;
	ff_middleware(arr);
	printf("found %d sprites\n", data->s_count);
	init_sprites(arr, data);
	init_windows(arr, data);
}
