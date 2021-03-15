#include "../../cub.h"

void	put_pixel(t_img img, int x, int y, int color)
{
	char	*pos;

	pos = img.addr + (y * img.length + x * (img.bpp / 8));
	*((unsigned int	*)pos) = color;
}

void	handle_player_dir(t_rc *rc, t_map *data)
{
	rc->wens.x = 0;
	rc->wens.y = 0;
	rc->plane.x = 0;
	rc->plane.y = 0;
	if (data->player == 'N')
		rc->wens.y = -1;
	if (data->player == 'S')
		rc->wens.y = 1;
	if (data->player == 'W')
		rc->wens.x = -1;
	if (data->player == 'E')
		rc->wens.x = 1;
	if (ft_strchr("NS", data->player))
		rc->plane.x = 0.66;
	if (ft_strchr("WE", data->player))
		rc->plane.y = 0.66;
}

void	init_rc(t_rc *rc, t_map *data)
{
	handle_player_dir(rc, data);
	rc->player_pos.x = (double)data->pos.x + 0.5;
	rc->player_pos.y = (double)data->pos.y + 0.5;
	rc->ray_square.x = 0;
	rc->ray_square.y = 0;
	rc->ray_dir.x = 0;
	rc->ray_dir.y = 0;
	rc->cam = 0;
	rc->speed.y = 0;
	rc->speed.rot = 0;
	rc->was_hit = 0;
	rc->side = -1;
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
		rc->closest_line.x = (rc->player_pos.x - rc->ray_square.x) * rc->next_line.x;
	}
	else
	{
		rc->ray_step.x = 1;
		rc->closest_line.x = (rc->ray_square.x + 1 - rc->player_pos.x) * rc->next_line.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->ray_step.y = -1;
		rc->closest_line.y = (rc->player_pos.y - rc->ray_square.y) * rc->next_line.y;
	}
	else
	{
		rc->ray_step.y = 1;
		rc->closest_line.y = (rc->ray_square.y + 1 - rc->player_pos.y) * rc->next_line.y;
	}
}

void	handle_rc(t_rc *rc, t_map *data, int x)
{
	rc->cam = 2 * x / (double)data->res.x - 1;

	rc->ray_dir.x = rc->wens.x + rc->plane.x * rc->cam;
	rc->ray_dir.y = rc->wens.y + rc->plane.y * rc->cam;

	rc->ray_square.x = (int)rc->player_pos.x;
	rc->ray_square.y = (int)rc->player_pos.y;

	// printf("rc->wens.x = %d, rc->plane.x = %lf, rc->cam = %lf, rc->ray_dir.x in handle_rc = %lf\n", rc->wens.x, rc->plane.x, rc->cam, rc->ray_dir.x);

	if (rc->ray_dir.y == 0)
		rc->next_line.x = 0;
	else
		rc->next_line.x = rc->ray_dir.x != 0 ? ft_abs_dbl(1 / rc->ray_dir.x) : 0;

	if (rc->ray_dir.x == 0)
		rc->next_line.y = 0;
	else
		rc->next_line.y = rc->ray_dir.y != 0 ? ft_abs_dbl(1 / rc->ray_dir.y) : 0;

	// printf("rc->ray_dir.x in handle_rc = %lf\n", rc->ray_dir.x);
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
		// printf("x = %d, side = %d, ray.y = %d, ray.x = %d, char = %c, was_hit = %d, side = %d, clY = %lf, clX = %lf\n", x, rc->side, rc->ray_square.y, rc->ray_square.x, arr[rc->ray_square.y][rc->ray_square.x], rc->was_hit, rc->side, rc->closest_line.y, rc->closest_line.x);
	}

	if (rc->side)
		rc->dist_to_wall = (rc->ray_square.y - rc->player_pos.y + (1 - rc->ray_step.y) / 2) / rc->ray_dir.y;
	else
		rc->dist_to_wall = (rc->ray_square.x - rc->player_pos.x + (1 - rc->ray_step.x) / 2) / rc->ray_dir.x; // здесь делю на 0
	// printf("side = %d, rsx = %d, rsy = %d, ray_step.x = %d, ray_step.y = %d, ray_dir.x = %lf, ray_dir.y = %lf, dist_to_wall = %lf, x = %d\n", rc->side, rc->ray_square.x, rc->ray_square.y, rc->ray_step.x, rc->ray_step.y, rc->ray_dir.x, rc->ray_dir.y, rc->dist_to_wall, x);
	// printf("side = %d, rsx = %d, player.x = %lf, ray_step.x = %d, ray_dir.x = %lf, dist_to_wall = %lf, x = %d\n", rc->side, rc->ray_square.x, rc->player_pos.x, rc->ray_step.x, rc->ray_dir.x, rc->dist_to_wall, x);
}

void	calc_wall(t_rc *rc, t_map *data)
{
	rc->wall.height = (int)(data->res.x / rc->dist_to_wall * 0.75);
	rc->wall.start = (int)(-rc->wall.height / 2 + data->res.y / 2);
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
		if (y < rc->wall.start)
			put_pixel(rc->img, x, y, 0x00FFFFFF);
		else if (y < rc->wall.finish)
			put_pixel(rc->img, x, y, rc->wall.color);
		else
			put_pixel(rc->img, x, y, 0x00000000);
		y++;
	}
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
	rc->player_pos.x = data->pos.x;
	rc->player_pos.y = data->pos.y;

	x = 000;
	printf("bef loop\n");
	while (x < data->res.x)
	{
		init_rc(rc, data);
		handle_rc(rc, data, x);
		run_dda(rc, arr);
		calc_wall(rc, data);
		define_color(rc);
		// printf("side = %d, square.y = %d, pos.y = %lf, step.y = %d, dir.y = %lf, cam = %lf\n", rc->side, rc->ray_square.y, rc->player_pos.y, rc->ray_step.y, rc->ray_dir.y, rc->cam);
		draw_line(rc, data, x);
		x++;
	}
	mlx_put_image_to_window(rc->mlx, rc->win, rc->img.ptr, 0, 0);
	mlx_loop(rc->mlx);
}
