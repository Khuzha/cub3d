/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 20:57:47 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/23 21:24:30 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

#define VMOVE 256.0

static void	make_prep(t_rc *rc, t_s_rc *s, int i)
{
	s->sprite_x = rc->data->sprites[i].x - rc->player_pos.x;
	s->sprite_y = rc->data->sprites[i].y - rc->player_pos.y;
	s->inv_det = (double)1 /
		(rc->plane.x * rc->wens.y - rc->plane.y * rc->wens.x);
	s->transform_x = s->inv_det *
		(rc->wens.y * s->sprite_x - rc->wens.x * s->sprite_y);
	s->transform_y = s->inv_det *
		(-rc->plane.y * s->sprite_x + rc->plane.x * s->sprite_y);
	s->sprite_screen_x = (int)((rc->data->res.x / 2) *
		(1 + s->transform_x / s->transform_y));
	s->mv_scr = (int)(VMOVE / s->transform_y);
}

static void	calc_sprite(t_rc *rc, t_s_rc *s)
{
	s->sprite_height = abs((int)(rc->data->res.x / s->transform_y * 0.75));
	s->draw_start_y = -s->sprite_height / 2 + rc->data->res.y / 2 + s->mv_scr;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->sprite_height / 2 + rc->data->res.y / 2 + s->mv_scr;
	if (s->draw_end_y >= rc->data->res.y)
		s->draw_end_y = rc->data->res.y - 1;
	s->sprite_width = abs((int)(rc->data->res.x / s->transform_y * 0.75));
	s->draw_start_x = -s->sprite_width / 2 + s->sprite_screen_x;
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	s->draw_end_x = s->sprite_width / 2 + s->sprite_screen_x;
	if (s->draw_end_x >= rc->data->res.x)
		s->draw_end_x = rc->data->res.x - 1;
}

static void	draw_helper(t_rc *rc, t_s_rc *s, int y, int x)
{
	int		color;
	char	*pos;

	while (y < s->draw_end_y)
	{
		s->d = (y - s->mv_scr) * 256 -
			rc->data->res.y * 128 + s->sprite_height * 128;
		s->tex_y = ((s->d * rc->t.s.h) / s->sprite_height) / 256;
		pos = rc->t.s.img.addr + rc->t.s.img.length * s->tex_y
			+ s->tex_x * (rc->t.s.img.bpp / 8);
		color = *((unsigned int	*)pos);
		if ((color & 0x00FFFFFF) != 0)
			put_pixel(rc->img, x, y, color);
		y++;
	}
}

static void	draw(t_rc *rc, t_s_rc *s)
{
	int		x;
	int		y;

	x = s->draw_start_x;
	while (x < s->draw_end_x)
	{
		s->tex_x = (int)(256 * (x - (-s->sprite_width / 2 + s->sprite_screen_x))
			* rc->t.s.w / s->sprite_width) / 256;
		if (s->transform_y > 0 && x > 0 && x < rc->data->res.x &&
			s->transform_y < (double)rc->zb[x])
		{
			y = s->draw_start_y;
			draw_helper(rc, s, y, x);
		}
		x++;
	}
}

void		draw_sprites(t_rc *rc)
{
	t_s_rc	*s;
	int		i;

	i = 0;
	if (!(s = malloc(sizeof(t_s_rc))))
		error("Malloc error\n");
	while (i < rc->data->s_count)
	{
		make_prep(rc, s, i);
		calc_sprite(rc, s);
		draw(rc, s);
		i++;
	}
}
