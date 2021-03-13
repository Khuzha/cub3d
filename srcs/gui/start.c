#include "../../cub.h"

void	put_pixel(t_img img, int x, int y, int color)
{
	char	*pos;

	pos = img.addr + (y * img.length + x * (img.bpp / 8));
	*((unsigned int	*)pos) = color;
}

void	init_rc(t_rc *rc, t_map *data)
{
	rc->pos.x = 10;
	rc->pos.y = 3;
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

void	prepare_rc(t_rc *rc)
{
	if (rc->ray_dir.x < 0)
	{
		rc->ray_step.x = -1;
		rc->abs_dist.x = (rc->pos.x - rc->ray_square.x) * rc->delta_dist.x;
	}
	else
	{
		rc->ray_step.x = 1;
		rc->abs_dist.x = (rc->ray_square.x + 1 - rc->pos.x) * rc->delta_dist.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->ray_step.y = -1;
		rc->abs_dist.y = (rc->pos.y - rc->ray_square.y) * rc->delta_dist.y;
	}
	else
	{
		rc->ray_step.y = 1;
		rc->abs_dist.y = (rc->ray_square.y + 1 - rc->pos.y) * rc->delta_dist.y;
	}
}

void	handle_rc(t_rc *rc, t_map *data, int x)
{
	rc->cam = 2 * x / (double)data->res.x - 1;
			
	rc->ray_dir.x = rc->wens.x + rc->plane.x + rc->cam;
	rc->ray_dir.y = rc->wens.y + rc->plane.y + rc->cam;

	rc->ray_square.x = (int)rc->pos.x;
	rc->ray_square.y = (int)rc->pos.y;

	if (rc->ray_dir.y == 0)
		rc->delta_dist.x = rc->ray_dir.x != 0 ? ft_abs_dbl(1 / rc->ray_dir.x) : 0;
	if (rc->ray_dir.x == 0)
		rc->delta_dist.y = rc->ray_dir.y != 0 ? ft_abs_dbl(1 / rc->ray_dir.y) : 0;

	prepare_rc(rc);
}

void	run_dda(t_rc *rc, char **arr, t_map *data)
{
	while (!rc->was_hit)
	{
		if (rc->abs_dist.x < rc->abs_dist.y)
		{
			rc->abs_dist.x += rc->delta_dist.x;
			rc->ray_square.x += rc->ray_step.x;
			rc->side = 0;
		}
		else
		{
			rc->abs_dist.y += rc->delta_dist.y;
			rc->ray_square.y += rc->ray_step.y;
			rc->side = 1;
		}
		if (arr[rc->ray_square.y][rc->ray_square.x] == '1')
			rc->was_hit = 1;
	}
	if (rc->side)
		rc->dist_to_wall = (rc->ray_square.y - rc->pos.y + (1 - rc->ray_step.y) / 2) / rc->ray_dir.y;
	else
		rc->dist_to_wall = (rc->ray_square.x - rc->pos.x + (1 - rc->ray_step.x) / 2) / rc->ray_dir.x;
}

void	calc_wall(t_rc *rc, t_map *data)
{
	rc->wall.height = (int)(data->res.y / rc->dist_to_wall);
	rc->wall.start = -(int)(rc->wall.height / 2 + data->res.y / 2);
	rc->wall.finish = (int)(rc->wall.height / 2 + data->res.y / 2);
	if (rc->wall.start < 0)
		rc->wall.start = 0;
	if (rc->wall.finish >= data->res.y)
		rc->wall.finish = data->res.y - 1;
}

int		make_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void	define_color(t_rc *rc)
{
	if (rc->side)
		rc->wall.color = make_trgb(0, 0xFF, 0x00, 0x00);
	else
		rc->wall.color = make_trgb(0, 0xFF, 0x00, 0x00) / 2;
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
			handle_rc(rc, data, x);
			run_dda(rc, arr, data);
			calc_wall(rc, data);
			define_color(rc);
			// rc->dirlen.x = rc->dir.x >= 0 ? get_up(rc->pos.x) : get_floor(rc->pos.x);
			// rc->dirlen.y = rc->dir.y >= 0 ? get_up(rc->pos.y) : get_floor(rc->pos.y);

			//       double perpWallDist; ??

			x++;
		}
	}
}
