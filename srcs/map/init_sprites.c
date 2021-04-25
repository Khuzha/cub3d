/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:37:42 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 13:39:00 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void		print_sprites(t_map *data, t_dxy player_pos)
{
	int i;

	i = 0;
	printf("-----\nplayer position: y = %f, x = %f\n",
		player_pos.y, player_pos.x);
	while (i < data->s_count)
	{
		printf("i = %d, sprite: y = %f, x = %f, dist = %f\n",
			i, data->sprites[i].y, data->sprites[i].x,
			data->sprites[i].dist);
		i++;
	}
	printf("\n");
}

static void	calc_sprites(char **arr, t_sprite *sprites)
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
			if (arr[y][x] == '$')
			{
				sprites[i].y = y + 0.5;
				sprites[i].x = x + 0.5;
				i++;
			}
			x++;
		}
		y++;
	}
}

void		init_sprites(char **arr, t_map *data)
{
	if (!(data->sprites = ft_calloc(sizeof(t_sprite) *
		data->s_count, sizeof(t_sprite) * data->s_count)))
		error("Malloc error");
	calc_sprites(arr, data->sprites);
}

void		recalc_sprites(t_rc *rc)
{
	int i;

	i = 0;
	while (i < rc->data->s_count)
	{
		rc->data->sprites[i].dist =
			(rc->player_pos.x - rc->data->sprites[i].x) *
			(rc->player_pos.x - rc->data->sprites[i].x) +
			(rc->player_pos.y - rc->data->sprites[i].y) *
			(rc->player_pos.y - rc->data->sprites[i].y);
		i++;
	}
}
