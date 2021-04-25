/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:12:31 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 13:17:42 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	handle_player_dir(t_rc *rc, t_map *data)
{
	rc->wens.x = 0;
	rc->wens.y = 0;
	rc->plane.x = 0;
	rc->plane.y = 0;
	if (data->player == 'N')
		rc->wens.y = -1;
	if (data->player == 'S')
		rc->wens.y = 1;
	if (data->player == 'W')
		rc->wens.x = -1;
	if (data->player == 'E')
		rc->wens.x = 1;
	if (data->player == 'N')
		rc->plane.x = 0.66;
	if (data->player == 'S')
		rc->plane.x = -0.66;
	if (data->player == 'E')
		rc->plane.y = 0.66;
	if (data->player == 'W')
		rc->plane.y = -0.66;
	rc->wens_defined = 1;
}

void	handle_rc(t_rc *rc, t_map *data, int x)
{
	rc->cam = 2 * x / (double)data->res.x - 1;
	rc->ray_dir.y = rc->wens.y + rc->plane.y * rc->cam;
	rc->ray_dir.x = rc->wens.x + rc->plane.x * rc->cam;
	rc->ray_square.x = (int)rc->player_pos.x;
	rc->ray_square.y = (int)rc->player_pos.y;
	if (rc->ray_dir.y == 0)
		rc->next_line.x = 0;
	else
		rc->next_line.x = rc->ray_dir.x != 0 ?
			ft_abs_dbl(1 / rc->ray_dir.x) : 1;
	if (rc->ray_dir.x == 0)
		rc->next_line.y = 0;
	else
		rc->next_line.y = rc->ray_dir.y != 0 ?
			ft_abs_dbl(1 / rc->ray_dir.y) : 1;
	prepare_rc(rc);
}
