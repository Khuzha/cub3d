/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:18:24 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/24 20:18:25 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	rot_right(t_rc *rc)
{
	double	wens_y;
	double	plane_y;

	wens_y = rc->wens.y;
	rc->wens.y = rc->wens.y * cos(-rc->speed.rot) -
		rc->wens.x * sin(-rc->speed.rot);
	rc->wens.x = wens_y * sin(-rc->speed.rot) +
		rc->wens.x * cos(-rc->speed.rot);
	plane_y = rc->plane.y;
	rc->plane.y = rc->plane.y * cos(-rc->speed.rot) -
		rc->plane.x * sin(-rc->speed.rot);
	rc->plane.x = plane_y * sin(-rc->speed.rot) +
		rc->plane.x * cos(-rc->speed.rot);
}

void	rot_left(t_rc *rc)
{
	double	wens_y;
	double	plane_y;

	wens_y = rc->wens.y;
	rc->wens.y = rc->wens.y * cos(rc->speed.rot) -
		rc->wens.x * sin(rc->speed.rot);
	rc->wens.x = wens_y * sin(rc->speed.rot) +
		rc->wens.x * cos(rc->speed.rot);
	plane_y = rc->plane.y;
	rc->plane.y = rc->plane.y * cos(rc->speed.rot) -
		rc->plane.x * sin(rc->speed.rot);
	rc->plane.x = plane_y * sin(rc->speed.rot) +
		rc->plane.x * cos(rc->speed.rot);
}
