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
				data->sprites[i].y = y;
				data->sprites[i].x = x;
				printf("sprite found: y = %f, x = %f\n", data->sprites[i].y, data->sprites[i].x);	
			}
			x++;
		}
		y++;
	}
}