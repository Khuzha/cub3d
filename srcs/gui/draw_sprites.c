#include "../../cub.h"

void	draw_sprites(t_rc *rc)
{
	int i;
	double	sprite_y;
	double	sprite_x;
	double	inv_det;
	double	transform_y;
	double	transform_x;
	int		sprite_screen_x;
	int		sprite_height;
	int		draw_start_y;
	int		draw_end_y;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;

	printf("enter draw_sprites\n");

	i = 0;
	while (i < rc->data->s_count)
	{
		sprite_y = rc->data->sprites[i].y;
		sprite_x = rc->data->sprites[i].x;
		inv_det = (double)1 / (rc->plane.y * rc->wens.x - rc->plane.x * rc->wens.y);
		transform_y = inv_det * (rc->wens.x * sprite_y - rc->wens.y * sprite_x);
		transform_x = inv_det * (-rc->plane.x * sprite_y + rc->plane.y * sprite_x);
		sprite_screen_x = (int)((rc->data->res.x / 2) * (1 + transform_y / transform_x));

		sprite_height = abs((int)(rc->data->res.y / transform_x));
		draw_start_y = -sprite_height / 2 + rc->data->res.y / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		draw_end_y = sprite_height / 2 + rc->data->res.y / 2;
		if (draw_end_y >= rc->data->res.y)
			draw_end_y = rc->data->res.y - 1;
		
		sprite_width = abs((int)(rc->data->res.y / transform_x));
		draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		draw_end_x = sprite_width / 2 + sprite_screen_x;
		if (draw_end_x > rc->data->res.x)
			draw_end_x = rc->data->res.x - 1;
		
		printf("bef stripe loop\n");
		int stripe = draw_start_x;
		while (stripe < draw_end_x)
		{
			int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * rc->t.s.w / sprite_width) / 256;
			if (transform_x > 0 && stripe > 0 && stripe < rc->data->res.x && transform_x < rc->zb[stripe])
			{
				int y = draw_start_y;
				while (y < draw_end_y)
				{
					int d = y * 256 - rc->data->res.y * 128 + sprite_height * 128;
					int tex_y = ((d * rc->t.s.h) / sprite_height) / 256;
					char *pos = rc->t.s.img.addr + rc->t.s.w * tex_y + tex_x;
					int color = *((unsigned int	*)pos);
					put_pixel(rc->img, stripe, y, color);
					y++;
					printf("drawed y\n");
				}
			}
			stripe++;
		}
		i++;
	}
}