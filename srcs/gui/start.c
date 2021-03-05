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
	win = mlx_new_window(mlx, 500, 500, "21");
	img.ptr = mlx_new_image(mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.length, &img.endian);

	int		y;
	int		x;
	y = 100;
	x = 100;
	while (y < 200)
	{
		while (x < 200)
		{
			put_pixel(img,x, y, 0xFFFFFF);
			x++;
		}
		x = 100;
		y++;
	}
	mlx_put_image_to_window(mlx, win, img.ptr, 0, 0);
	mlx_loop(mlx);
	arr++;
	data++;
}
