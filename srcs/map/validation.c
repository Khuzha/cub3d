/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:39:20 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 19:36:54 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	check_sprite(char **arr, int y, int x, t_map *data)
{
	if (arr[y][x] == '2')
		data->s_count++;
}

int		find_player(char **arr, size_t *pos_x, size_t *pos_y, t_map *data)
{
	size_t	x;
	size_t	y;
	int		counter;

	y = 0;
	counter = 0;
	while (arr[y])
	{
		x = 0;
		while (arr[y][x])
		{
			if (ft_strchr("WENS", arr[y][x]))
			{
				*pos_x = x;
				*pos_y = y;
				data->player = arr[y][x];
				counter++;
			}
			check_sprite(arr, y, x, data);
			x++;
		}
		y++;
	}
	return (counter);
}

void	flood_fill(char **arr, int x, int y)
{
	// printf("y = %d, x = %d\n", y, x);
	// printf("char = %c\n", arr[y][x]);
	if (x < 0 || y < 0)
		error("Map validation failed");
	if (arr[y] && arr[y][x] != '0' && arr[y][x] != '1'
		&& !ft_strchr("2@$", arr[y][x]))
		check_char(arr[y][x]);
	if (arr[y] && (arr[y][x] == '0' || ft_strchr("2WENS", arr[y][x])))
	{
		arr[y][x] = (arr[y][x] == '0' ||
			ft_strchr("WENS", arr[y][x])) ? '@' : '$';
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
	int	y;
	int	x;

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

	if (find_player(arr, &x, &y, data) != 1)
		error("Wrong players count");
	data->pos.x = (double)x;
	data->pos.y = (double)y;
	ff_middleware(arr);
	init_sprites(arr, data);
	init_windows(arr, data);
}
