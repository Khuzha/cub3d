/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:08:31 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/24 20:08:31 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	prepare_rc(t_rc *rc)
{
	if (rc->ray_dir.x < 0)
	{
		rc->ray_step.x = -1;
		rc->closest_line.x = (rc->player_pos.x - rc->ray_square.x)
			* rc->next_line.x;
	}
	else
	{
		rc->ray_step.x = 1;
		rc->closest_line.x = (rc->ray_square.x + 1 - rc->player_pos.x)
			* rc->next_line.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->ray_step.y = -1;
		rc->closest_line.y = (rc->player_pos.y - rc->ray_square.y)
			* rc->next_line.y;
	}
	else
	{
		rc->ray_step.y = 1;
		rc->closest_line.y = (rc->ray_square.y + 1 - rc->player_pos.y)
			* rc->next_line.y;
	}
}

void	run_dda(t_rc *rc, char **arr)
{
	while (!rc->was_hit)
	{
		if (rc->closest_line.x < rc->closest_line.y)
		{
			rc->closest_line.x += rc->next_line.x;
			rc->ray_square.x += rc->ray_step.x;
			rc->side = 0;
		}
		else
		{
			rc->closest_line.y += rc->next_line.y;
			rc->ray_square.y += rc->ray_step.y;
			rc->side = 1;
		}
		if (arr[rc->ray_square.y][rc->ray_square.x] == '1')
			rc->was_hit = 1;
	}
	if (rc->side)
		rc->dist_to_wall = (rc->ray_square.y - rc->player_pos.y +
			(1 - rc->ray_step.y) / 2) / rc->ray_dir.y;
	else
		rc->dist_to_wall = (rc->ray_square.x - rc->player_pos.x +
			(1 - rc->ray_step.x) / 2) / rc->ray_dir.x;
}

void	define_side(t_rc *rc)
{
	if (!(rc->cur_side = ft_calloc(3, 3)))
		error("Malloc ft_calloc in define_side) error");
	if (rc->side)
	{
		if (rc->ray_dir.y > 0)
			rc->cur_side = &rc->t.so;
		else
			rc->cur_side = &rc->t.no;
	}
	else
	{
		if (rc->ray_dir.x > 0)
			rc->cur_side = &rc->t.ea;
		else
			rc->cur_side = &rc->t.we;
	}
}

void	init_windows(char **arr, t_map *data)
{
	t_rc	*rc;

	if (!(rc = malloc(sizeof(t_rc))))
		error("Malloc error\n");
	rc->arr = arr;
	rc->data = data;
	init_keys(rc);
	init_mlx(rc);
	drawer(rc);
	draw_sprites(rc);
	if (data->is_scnsht)
		return (make_scrsht(rc));
	mlx_hook(rc->win, 2, 0, key_press, rc);
	mlx_hook(rc->win, 3, 0, key_unpress, rc);
	mlx_hook(rc->win, 17, 0, finish, rc);
	mlx_loop_hook(rc->mlx, handle_loop, rc);
	mlx_loop(rc->mlx);
}
