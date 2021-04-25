/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:16:02 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 20:03:43 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

int		key_press(int code, t_rc *rc)
{
	if (code == KEY_ESC)
		finish(rc);
	if (code == KEY_W)
		rc->keys.w = 1;
	if (code == KEY_S)
		rc->keys.s = 1;
	if (code == KEY_A)
		rc->keys.a = 1;
	if (code == KEY_D)
		rc->keys.d = 1;
	if (code == KEY_AR)
		rc->keys.arr_r = 1;
	if (code == KEY_AL)
		rc->keys.arr_l = 1;
	if (code == KEY_SHIFT_L || code == KEY_SHIFT_R)
	{
		rc->speed.forward *= 2;
		rc->speed.rot *= 2;
	}
	return (0);
}

int		key_unpress(int code, t_rc *rc)
{
	if (code == KEY_W)
		rc->keys.w = 0;
	if (code == KEY_S)
		rc->keys.s = 0;
	if (code == KEY_A)
		rc->keys.a = 0;
	if (code == KEY_D)
		rc->keys.d = 0;
	if (code == KEY_AR)
		rc->keys.arr_r = 0;
	if (code == KEY_AL)
		rc->keys.arr_l = 0;
	if (code == KEY_SHIFT_L || code == KEY_SHIFT_R)
	{
		rc->speed.forward /= 2;
		rc->speed.rot /= 2;
	}
	return (0);
}

int		handle_loop(t_rc *rc)
{
	if (rc->keys.w)
		step_forward(rc);
	if (rc->keys.s)
		step_back(rc);
	if (rc->keys.a)
		step_left(rc);
	if (rc->keys.d)
		step_right(rc);
	if (rc->keys.arr_l)
		rot_left(rc);
	if (rc->keys.arr_r)
		rot_right(rc);
	drawer(rc);
	draw_sprites(rc);
	recalc_sprites(rc);
	bubblesort(rc->data->sprites, rc->data->s_count);
	if (!rc->data->is_scnsht)
		mlx_put_image_to_window(rc->mlx, rc->win, rc->img.ptr, 0, 0);
	return (0);
}
