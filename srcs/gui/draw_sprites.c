#include "../../cub.h"

#define uDiv 1
#define vDiv 1
#define vMove 256.0

void	draw_sprites(t_rc *rc)
{
	int i;

	
	i = 0;
	while (i < rc->data->s_count)
	{
		sprite_x = rc->data->sprites[i].x - rc->player_pos.x;
		sprite_y = rc->data->sprites[i].y - rc->player_pos.y;

		inv_det = (double)1 / (rc->plane.x * rc->wens.y - rc->plane.y * rc->wens.x);
		transform_x = inv_det * (rc->wens.y * sprite_x - rc->wens.x * sprite_y);
		transform_y = inv_det * (-rc->plane.y * sprite_x + rc->plane.x * sprite_y);
		sprite_screen_x = (int)((rc->data->res.x / 2) * (1 + transform_x / transform_y));
		mv_scr = (int)(vMove / transform_y);

		sprite_height = abs((int)(rc->data->res.y / transform_y));
		draw_start_y = -sprite_height / 2 + rc->data->res.y / 2 + mv_scr;
		if (draw_start_y < 0)
			draw_start_y = 0;
		draw_end_y = sprite_height / 2 + rc->data->res.y / 2 + mv_scr;
		if (draw_end_y >= rc->data->res.y)
			draw_end_y = rc->data->res.y - 1;

		sprite_width = abs((int)(rc->data->res.y / transform_y));
		draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		draw_end_x = sprite_width / 2 + sprite_screen_x;
		if (draw_end_x >= rc->data->res.x)
			draw_end_x = rc->data->res.x - 1;
		
		int stripe = draw_start_x;
		while (stripe < draw_end_x)
		{
			int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * rc->t.s.w / sprite_width) / 256;
			if (transform_y > 0 && stripe > 0 && stripe < rc->data->res.x && transform_y < (double)rc->zb[stripe])
			{
				int y = draw_start_y;
				while (y < draw_end_y)
				{
					int d = (y - mv_scr) * 256 - rc->data->res.y * 128 + sprite_height * 128;
					int tex_y = ((d * rc->t.s.h) / sprite_height) / 256;
					char *pos = rc->t.s.img.addr + rc->t.s.img.length * tex_y + tex_x * (rc->t.s.img.bpp / 8);
					int color = *((unsigned int	*)pos);
					if((color & 0x00FFFFFF) != 0)
						put_pixel(rc->img, stripe, y, color);
					y++;
				}
			}
			stripe++;
		}
		i++;
	}
}