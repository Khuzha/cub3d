#include "../../cub.h"

void	print_sprites(t_map *data)
{
	int i;
	
	i = 0;
	while (i < data->s_count)
	{
		printf("i = %d, sprite: y = %f, x = %f, dist = %f\n", i, data->sprites[i].y, data->sprites[i].x, data->sprites[i].dist);
		i++;
	}
	printf("\n");
}

static void	calc_sprites(char **arr, t_sprite *sprites, t_dxy pos, int need_dist)
{
	int y;
	int x;
	int	i;

	y = 0;
	i = 0;
	while (arr[y])
	{
		x = 0;
		while (arr[y][x])
		{
			if (arr[y][x] == '2')
			{
				sprites[i].y = y + 0.5;
				sprites[i].x = x + 0.5;
				if (need_dist)
					sprites[i].dist = ((pos.x - sprites[i].x) * (pos.x - sprites[i].x) + (pos.y - sprites[i].y) * (pos.y - sprites[i].y));
				i++;
			}
			x++;
		}
		y++;
	}
}

void	init_sprites(char **arr, t_map *data)
{
	t_dxy	pos;

	if (!(data->sprites = ft_calloc(sizeof(t_sprite) * data->s_count, sizeof(t_sprite) * data->s_count)))
		error("Malloc error");
	pos.y = (double)data->pos.y + 0.5;
	pos.x = (double)data->pos.x + 0.5;
	calc_sprites(arr, data->sprites, pos, 0);
}

void	recalc_sprites(t_rc *rc)
{
	int i;
	
	i = 0;
	while (i < rc->data->s_count)
	{
		rc->data->sprites[i].dist = ((rc->player_pos.x - rc->data->sprites[i].x) * (rc->player_pos.x - rc->data->sprites[i].x) + (rc->player_pos.y - rc->data->sprites[i].y) * (rc->player_pos.y - rc->data->sprites[i].y));
		i++;
	}
}