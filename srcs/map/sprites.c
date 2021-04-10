#include "../../cub.h"

void	init_sprites(char **arr, t_map *data)
{
	int y;
	int x;
	int i;

	y = 0;
	i = 0;
	if (!(data->sprites = malloc(sizeof(t_sprite) * data->s_count)))
		error("Malloc error");
	while (arr[y])
	{
		x = 0;
		while (arr[y][x])
		{
			if (arr[y][x] == '2')
			{
				data->sprites[i].y = y + 0.5;
				data->sprites[i].x = x + 0.5;
				data->sprites[i].dist = ((data->pos.x - data->sprites[i].x) * (data->pos.x - data->sprites[i].x) + (data->pos.y - data->sprites[i].y) * (data->pos.y - data->sprites[i].y));
				printf("sprite found: y = %f, x = %f, dist = %f\n", data->sprites[i].y, data->sprites[i].x, data->sprites[i].dist);
			}
			x++;
		}
		y++;
	}
}