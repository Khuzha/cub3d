#include "../../cub.h"

void	put_pixel(t_img img, int x, int y, int color)
{
	char	*pos;

	// if (x < 0 || x > data->res.x || y < 0 || y > data->res.y)
	// 	error("Ты уебан");

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
	rc->cam = 0;
	rc->plane.x = 0.66;
	rc->plane.y = 0;
	rc->speed.y = 0;
	rc->speed.rot = 0;
	rc->was_hit = 0;
	data++;
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
		rc->closest_line.x = (rc->pos.x - rc->ray_square.x) * rc->next_line.x;
	}
	else
	{
		rc->ray_step.x = 1;
		rc->closest_line.x = (rc->ray_square.x + 1 - rc->pos.x) * rc->next_line.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->ray_step.y = -1;
		rc->closest_line.y = (rc->pos.y - rc->ray_square.y) * rc->next_line.y;
	}
	else
	{
		rc->ray_step.y = 1;
		rc->closest_line.y = (rc->ray_square.y + 1 - rc->pos.y) * rc->next_line.y;
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
		rc->next_line.x = rc->ray_dir.x != 0 ? ft_abs_dbl(1 / rc->ray_dir.x) : 0;
	if (rc->ray_dir.x == 0)
		rc->next_line.y = rc->ray_dir.y != 0 ? ft_abs_dbl(1 / rc->ray_dir.y) : 0;

	prepare_rc(rc);
}

void	run_dda(t_rc *rc, char **arr)
{
	while (!rc->was_hit)
	{
		if (rc->closest_line.x < rc->closest_line.y)
		{
			rc->closest_line.x += rc->next_line.x;
			rc->ray_square.x += rc->ray_step.x;
			rc->side = 0;
		}
		else
		{
			rc->closest_line.y += rc->next_line.y;
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
		rc->wall.color = make_trgb(0, 0xFF, 0xFF, 0x00);
	else
		rc->wall.color = make_trgb(0, 0xFF, 0x00, 0x00) / 2;
}

void	draw_line(t_rc *rc, t_map *data, int x)
{
	int	y;

	// printf("x = %d, res.y = %d, dist = %lf, start = %d, finish = %d, h = %d\n", x, data->res.y, rc->dist_to_wall, rc->wall.start, rc->wall.finish, rc->wall.height);
	y = 0;
	while (y < data->res.y)
	{
		printf("x = %d, y = %d\n", x, y);
		if (y < rc->wall.start)
			put_pixel(rc->img, x, y, 0x00FFFFFF);
		else if (y < rc->wall.finish)
			put_pixel(rc->img, x, y, rc->wall.color);
		else
			put_pixel(rc->img, x, y, 0x00000000);
		y++;
	}
	printf("success\n");
}

void	init_windows(char **arr, t_map *data)
{
	t_rc	*rc;
	int		x;

	if (!(rc = malloc(sizeof(t_dxy))))
		error("Malloc error\n");
	rc->mlx = mlx_init();
	rc->win = mlx_new_window(rc->mlx, data->res.x, data->res.y, "21");
	rc->img.ptr = mlx_new_image(rc->mlx, data->res.x, data->res.y);
	rc->img.addr = mlx_get_data_addr(rc->img.ptr, &rc->img.bpp, &rc->img.length, &rc->img.endian);
	rc->pos.x = data->pos.x;
	rc->pos.y = data->pos.y;

	x = 0;
	printf("bef loop\n");
	while (x <= data->res.x)
	{
		init_rc(rc, data);
		handle_rc(rc, data, x);
		run_dda(rc, arr);
		calc_wall(rc, data);
		define_color(rc);
		// printf("side = %d, square.y = %d, pos.y = %lf, step.y = %d, dir.y = %lf, cam = %lf\n", rc->side, rc->ray_square.y, rc->pos.y, rc->ray_step.y, rc->ray_dir.y, rc->cam);
		draw_line(rc, data, x);
		x++;
	}
	mlx_put_image_to_window(rc->mlx, rc->win, rc->img.ptr, 0, 0);
	mlx_loop(rc->mlx);
}
