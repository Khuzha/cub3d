#include "../../cub.h"

void	put_pixel(t_img img, int x, int y, int color)
{
	char	*pos;

	pos = img.addr + (y * img.length + x * (img.bpp / 8));
	*((unsigned int	*)pos) = color;
}

void	init_windows(char **arr, t_map *data)
{
	void	*mlx;
	void	*win;
	t_img	img;

	mlx = mlx_init();
	win = mlx_new_window(mlx, data->res.y, data->res.x, "21");
	img.ptr = mlx_new_image(mlx, data->res.y, data->res.x);
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.length, &img.endian);

	arr++;
}
