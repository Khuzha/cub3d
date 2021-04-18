#include "../../cub.h"

#define uDiv 1
#define vDiv 1
#define vMove 64.0

void	draw_sprites(t_rc *rc)
{
	for(int i = 0; i < rc->data->s_count; i++)
	{
		double spriteX = rc->data->sprites[i].x - rc->player_pos.x;
		double spriteY = rc->data->sprites[i].y - rc->player_pos.y;

		double invDet = 1.0 / (rc->plane.x * rc->wens.y - rc->wens.x * rc->plane.y);

		double transformX = invDet * (rc->wens.y * spriteX - rc->wens.x * spriteY);
		double transformY = invDet * (-rc->plane.y * spriteX + rc->plane.x * spriteY);

		int spriteScreenX = (int)((rc->data->res.x / 2) * (1 + transformX / transformY));

		int vMoveScreen = (int)(vMove / transformY);

		int spriteHeight = (int)fabs((rc->data->res.y / transformY) / vDiv);
		int drawStartY = -spriteHeight / 2 + rc->data->res.y / 2 + vMoveScreen;
		if (drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + rc->data->res.y / 2 + vMoveScreen;
		if(drawEndY >= rc->data->res.y) drawEndY = rc->data->res.y - 1;

		int spriteWidth = (int)fabs((rc->data->res.y / transformY) / uDiv);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= rc->data->res.x) drawEndX = rc->data->res.x - 1;

		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * rc->t.s.w / spriteWidth) / 256);
			// printf("x = %f, y = %f, dist = %f\n", rc->data->sprites[i].x, rc->data->sprites[i].y, rc->data->sprites[i].dist);

			if(transformY > 0 && stripe > 0 && stripe < rc->data->res.x && transformY < rc->zb[stripe])
			for(int y = drawStartY; y < drawEndY; y++)
			{
				int d = (y-vMoveScreen) * 256 - rc->data->res.y * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((d * rc->t.s.h) / spriteHeight) / 256;
				char *pos = rc->t.s.img.addr + rc->t.s.img.length * texY + texX * (rc->t.s.img.bpp / 8);
				int color = *((unsigned int	*)pos);
				if((color & 0x00FFFFFF) != 0)
					put_pixel(rc->img, stripe, y, color);
			}
		}
	}
}

// void	draw_sprites(t_rc *rc)
// {
// 	int i;
// 	double	sprite_x;
// 	double	sprite_y;
// 	double	inv_det;
// 	double	transform_y;
// 	double	transform_x;
// 	int		sprite_screen_x;
// 	int		sprite_height;
// 	int		draw_start_y;
// 	int		draw_end_y;
// 	int		sprite_width;
// 	int		draw_start_x;
// 	int		draw_end_x;

// 	i = 0;
// 	while (i < rc->data->s_count)
// 	{
// 		sprite_x = rc->data->sprites[i].x - rc->player_pos.x;
// 		sprite_y = rc->data->sprites[i].y - rc->player_pos.y;

// 		inv_det = (double)1 / (rc->plane.x * rc->wens.y - rc->plane.y * rc->wens.x);
// 		transform_x = inv_det * (rc->wens.y * sprite_x - rc->wens.x * sprite_y);
// 		transform_y = inv_det * (-rc->plane.y * sprite_x + rc->plane.x * sprite_y);
// 		sprite_screen_x = (int)((rc->data->res.x / 2) * (1 + transform_x / transform_y));

// 		sprite_height = abs((int)(rc->data->res.y / transform_y));
// 		draw_start_y = -sprite_height / 2 + rc->data->res.y / 2;
// 		if (draw_start_y < 0)
// 			draw_start_y = 0;
// 		draw_end_y = sprite_height / 2 + rc->data->res.y / 2;
// 		if (draw_end_y >= rc->data->res.y)
// 			draw_end_y = rc->data->res.y - 1;

// 		sprite_width = abs((int)(rc->data->res.y / transform_y));
// 		draw_start_x = -sprite_width / 2 + sprite_screen_x;
// 		if (draw_start_x < 0)
// 			draw_start_x = 0;
// 		draw_end_x = sprite_width / 2 + sprite_screen_x;
// 		if (draw_end_x >= rc->data->res.x)
// 			draw_end_x = rc->data->res.x - 1;
		
// 		int stripe = draw_start_x;
// 		while (stripe < draw_end_x)
// 		{
// 			int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * rc->t.s.w / sprite_width) / 256;
// 			if (transform_y > 0 && stripe > 0 && stripe < rc->data->res.x && transform_y < rc->zb[stripe])
// 			{
// 				int y = draw_start_y;
// 				while (y < draw_end_y)
// 				{
// 					int d = (y) * 256 - rc->data->res.y * 128 + sprite_height * 128;
// 					int tex_y = ((d * rc->t.s.h) / sprite_height) / 256;
					// char *pos = rc->t.s.img.addr + rc->t.s.img.length * tex_y + tex_x * (rc->t.s.img.bpp / 8);
					// int color = *((unsigned int	*)pos);
// 					put_pixel(rc->img, stripe, y, color);
// 					y++;
// 				}
// 			}
// 			stripe++;
// 		}
// 		i++;
// 	}
// }