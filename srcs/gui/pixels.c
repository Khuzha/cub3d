#include "../../cub.h"

int		get_pixel(t_txtr txtr, t_rc *rc, t_txtr_data *data)
{
	char *pos;

	data->tex_y = (int)data->tex_pos & (rc->t.so.h - 1);
	data->tex_pos += data->step;
	pos = txtr.img.addr + (int)(data->tex_y * txtr.img.length + data->tex_x * (txtr.img.bpp / 8));
	return *((unsigned int	*)pos);
}

void	put_pixel(t_img img, int x, int y, int color)
{
	char	*pos;

	pos = img.addr + (y * img.length + x * (img.bpp / 8));
	*((unsigned int	*)pos) = color;
}