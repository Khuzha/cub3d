/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initions.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:14:21 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/29 01:09:54 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void		init_keys(t_rc *rc)
{
	rc->keys.a = 0;
	rc->keys.d = 0;
	rc->keys.s = 0;
	rc->keys.w = 0;
	rc->keys.arr_l = 0;
	rc->keys.arr_r = 0;
	rc->keys.arr_t = 0;
	rc->keys.arr_d = 0;
	rc->speed.forward = 0.1;
	rc->speed.rot = 0.03;
}

void		init_rc(t_rc *rc, t_map *data)
{
	if (!rc->wens_defined)
		handle_player_dir(rc, data);
	rc->was_hit = 0;
	rc->side = -1;
	data++;
}

static void	init_txtr_imgs_2(t_rc *rc)
{
	rc->t.we.img.ptr = mlx_xpm_file_to_image(rc->mlx,
		rc->data->we, &rc->t.we.h, &rc->t.we.w);
	check_txtr(rc->t.we.img.ptr);
	rc->t.we.img.addr = mlx_get_data_addr(rc->t.we.img.ptr,
		&rc->t.we.img.bpp, &rc->t.we.img.length, &rc->t.we.img.endian);
	rc->t.s.img.ptr = mlx_xpm_file_to_image(rc->mlx,
		rc->data->s, &rc->t.s.h, &rc->t.s.w);
	check_txtr(rc->t.s.img.ptr);
	rc->t.s.img.addr = mlx_get_data_addr(rc->t.s.img.ptr,
		&rc->t.s.img.bpp, &rc->t.s.img.length, &rc->t.s.img.endian);
	free_file_paths(rc->data);
}

static void	init_txtr_imgs(t_rc *rc)
{
	rc->t.so.img.ptr = mlx_xpm_file_to_image(rc->mlx,
		rc->data->so, &rc->t.so.h, &rc->t.so.w);
	check_txtr(rc->t.so.img.ptr);
	rc->t.so.img.addr = mlx_get_data_addr(rc->t.so.img.ptr,
		&rc->t.so.img.bpp, &rc->t.so.img.length, &rc->t.so.img.endian);
	rc->t.no.img.ptr = mlx_xpm_file_to_image(rc->mlx,
		rc->data->no, &rc->t.no.h, &rc->t.no.w);
	check_txtr(rc->t.no.img.ptr);
	rc->t.no.img.addr = mlx_get_data_addr(rc->t.no.img.ptr,
		&rc->t.no.img.bpp, &rc->t.no.img.length, &rc->t.no.img.endian);
	rc->t.ea.img.ptr = mlx_xpm_file_to_image(rc->mlx,
		rc->data->ea, &rc->t.ea.h, &rc->t.ea.w);
	check_txtr(rc->t.ea.img.ptr);
	rc->t.ea.img.addr = mlx_get_data_addr(rc->t.ea.img.ptr,
		&rc->t.ea.img.bpp, &rc->t.ea.img.length, &rc->t.ea.img.endian);
	init_txtr_imgs_2(rc);
}

void		init_mlx(t_rc *rc)
{
	rc->mlx = mlx_init();
	if (!rc->data->is_scnsht)
		rc->win = mlx_new_window(rc->mlx,
			rc->data->res.x, rc->data->res.y, "21");
	rc->img.ptr = mlx_new_image(rc->mlx, rc->data->res.x, rc->data->res.y);
	rc->img.addr = mlx_get_data_addr(rc->img.ptr,
		&rc->img.bpp, &rc->img.length, &rc->img.endian);
	rc->player_pos.x = (double)rc->data->pos.x + 0.5;
	rc->player_pos.y = (double)rc->data->pos.y + 0.5;
	init_txtr_imgs(rc);
	rc->wens_defined = 0;
	rc->zb = malloc(sizeof(double) * rc->data->res.x);
}
