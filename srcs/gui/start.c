#include "../../cub.h"

void	put_pixel(t_img img, int x, int y, int color)
{
	char	*pos;

	pos = img.addr + (y * img.length + x * (img.bpp / 8));
	*((unsigned int	*)pos) = color;
}

void	init_rc(t_rc *rc, t_map *data)
{
	rc->pos.x = 0;
	rc->pos.y = 0;
	rc->wens.x = 0;
	rc->wens.y = 1;
	rc->ray_square.x = 0;
	rc->ray_square.y = 0;
	rc->ray_dir.x = 0;
	rc->ray_dir.y = 0;
	// rc->dirlen.x = 0;
	// rc->dirlen.y = 0;
	// rc->dirdiff.x = 0;
	// rc->dirdiff.y = 0;
	rc->cam = 0;
	rc->plane.x = 0;
	rc->plane.y = 0.66;
	rc->speed.y = 0;
	rc->speed.rot = 0;
	rc->was_hit = 0;
}

double	get_floor(double num)
{
	int tmp;

	tmp = (int)num;
	if ((double)tmp < num)
		return ((double)tmp);
	else
		return ((double)tmp - 1);
}

double	get_up(double num)
{
	int tmp;

	tmp = (int)num;
	if ((double)tmp > num)
		return ((double)tmp);
	else
		return ((double)tmp + 1);
}

void	init_windows(char **arr, t_map *data)
{
	t_rc	*rc;
	int		x;

	init(rc);
	rc->mlx = mlx_init();
	rc->win = mlx_new_window(rc->mlx, data->res.y, data->res.x, "21");
	rc->img.ptr = mlx_new_image(rc->mlx, data->res.y, data->res.x);
	rc->img.addr = mlx_get_data_addr(rc->img.ptr, &rc->img.bpp, &rc->img.length, &rc->img.endian);
	rc->pos.x = data->pos.x;
	rc->pos.y = data->pos.y;

	while (1)
	{
		x = 0;
		while (x < data->res.x)
		{
			rc->cam = 2 * x / (double)data->res.x - 1;
			
			rc->ray_dir.x = rc->wens.x + rc->plane.x + rc->cam;
			rc->ray_dir.y = rc->wens.y + rc->plane.y + rc->cam;

			rc->ray_square.x = (int)rc->pos.x;
			rc->ray_square.y = (int)rc->pos.y;

			if (rc->ray_dir.y == 0)
				rc->d_dist.x = rc->ray_dir.x != 0 ? ft_abs_dbl(1 / rc->ray_dir.x) : 0;
			if (rc->ray_dir.x == 0)
				rc->d_dist.y = rc->ray_dir.y != 0 ? ft_abs_dbl(1 / rc->ray_dir.y) : 0;

			// rc->dirlen.x = rc->dir.x >= 0 ? get_up(rc->pos.x) : get_floor(rc->pos.x);
			// rc->dirlen.y = rc->dir.y >= 0 ? get_up(rc->pos.y) : get_floor(rc->pos.y);

			//       double perpWallDist; ??

			x++;
		}
	}

	arr++;
}
