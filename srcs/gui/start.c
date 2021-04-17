#include "../../cub.h"

double	get_decimal(double num)
{
	int	integer;

	if ((num < 1 && num > 0) || (num > -1 && num < 0))
		return (num);
	integer = (int)num;
	return (num - integer);
}

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
	rc->wens_defined = 1;
}

void	init_keys(t_rc	*rc)
{
	rc->keys.a = 0;
	rc->keys.d = 0;
	rc->keys.s = 0;
	rc->keys.w = 0;
	rc->keys.arr_l = 0;
	rc->keys.arr_r = 0;
	rc->keys.arr_t = 0;
	rc->keys.arr_d = 0;
	rc->speed.forward = 0.06;
	rc->speed.rot = 0.015;
}

void	init_rc(t_rc *rc, t_map *data)
{
	if (!rc->wens_defined)
		handle_player_dir(rc, data);
	rc->was_hit = 0;
	rc->side = -1;
	data++;
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

	rc->ray_dir.y = rc->wens.y + rc->plane.y * rc->cam;
	rc->ray_dir.x = rc->wens.x + rc->plane.x * rc->cam;

	rc->ray_square.x = (int)rc->player_pos.x;
	rc->ray_square.y = (int)rc->player_pos.y;

	if (rc->ray_dir.y == 0)
		rc->next_line.x = 0;
	else
		rc->next_line.x = rc->ray_dir.x != 0 ? ft_abs_dbl(1 / rc->ray_dir.x) : 1;

	if (rc->ray_dir.x == 0)
		rc->next_line.y = 0;
	else
		rc->next_line.y = rc->ray_dir.y != 0 ? ft_abs_dbl(1 / rc->ray_dir.y) : 1;
	prepare_rc(rc);
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
		rc->dist_to_wall = (rc->ray_square.y - rc->player_pos.y + (1 - rc->ray_step.y) / 2) / rc->ray_dir.y;
	else
		rc->dist_to_wall = (rc->ray_square.x - rc->player_pos.x + (1 - rc->ray_step.x) / 2) / rc->ray_dir.x;
	recalc_sprites(rc);
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

void	calcs_for_txtr(t_rc *rc, t_txtr_data *data)
{
	if (rc->side == 0)
		data->wall_x = rc->player_pos.y + rc->dist_to_wall * rc->ray_dir.y;
	else
		data->wall_x = rc->player_pos.x + rc->dist_to_wall * rc->ray_dir.x;
	data->wall_x -= floor(data->wall_x);

	data->tex_x = (int)(data->wall_x * (double)(rc->t.so.w));

	if (rc->side == 0 && rc->ray_dir.x > 0)
		data->tex_x = rc->t.so.w - data->tex_x - 1;
	if (rc->side == 1 && rc->ray_dir.y < 0)
		data->tex_x = rc->t.so.w - data->tex_x - 1;

	data->step = 1.0 * rc->t.so.h / rc->wall.height;
	data->tex_pos = (rc->wall.start - rc->data->res.y / 2 + rc->wall.height / 2) * data->step;
}

int		get_pixel(t_txtr txtr, t_rc *rc, t_txtr_data *data)
{
	char *pos;

	data->tex_y = (int)data->tex_pos & (rc->t.so.h - 1);
	data->tex_pos += data->step;
	pos = txtr.img.addr + (int)(data->tex_y * txtr.img.length + data->tex_x * (txtr.img.bpp / 8));
	return *((unsigned int	*)pos);
}

void	define_side(t_rc *rc)
{
	if (!(rc->cur_side = ft_calloc(3, 3)))
		error("Malloc ft_calloc in define_side) error");
	if (rc->side)
	{
		if (rc->ray_dir.y > 0)
			rc->cur_side = &rc->t.so;
		else
			rc->cur_side = &rc->t.no;
	}
	else
	{
		if (rc->ray_dir.x > 0)
			rc->cur_side = &rc->t.ea;
		else
			rc->cur_side = &rc->t.we;
	}
}

void	draw_line(t_rc *rc, t_map *data, int x)
{
	t_colors	c;
	t_colors	f;
	t_txtr_data	*txtr_data;
	int	y;

	y = 0;
	c = rc->data->c_colors;
	f = rc->data->f_colors;
	if (!(txtr_data = malloc(sizeof(t_txtr_data))))
		error("Malloc error");
	calcs_for_txtr(rc, txtr_data);
	define_side(rc);
	// printf("cur_side = %s\n", rc->cur_side);
	while (y < data->res.y)
	{
		if (y < rc->wall.start)
			put_pixel(rc->img, x, y, make_trgb(0, c.r, c.g, c.b));
		else if (y < rc->wall.finish)
		{
			int color = get_pixel(*rc->cur_side, rc, txtr_data);
			put_pixel(rc->img, x, y, color);
		}
		else
			put_pixel(rc->img, x, y, make_trgb(0, f.r, f.g, f.b));
		y++;
	}
}

int		drawer(t_rc *rc)
{
	int		x;

	x = 0;
	while (x < rc->data->res.x)
	{
		init_rc(rc, rc->data);
		handle_rc(rc, rc->data, x);
		run_dda(rc, rc->arr);
		calc_wall(rc, rc->data);
		define_color(rc);
		draw_line(rc, rc->data, x);
		rc->zb[x] = rc->dist_to_wall;
		x++;
	}
	return (0);
}

#define offset 0.03

void	step_forward(t_rc *rc)
{
	if (rc->arr[(int)(rc->player_pos.y + rc->wens.y * rc->speed.forward)][(int)(rc->player_pos.x)] == '@')
		rc->player_pos.y += rc->wens.y * rc->speed.forward;
	if (rc->arr[(int)(rc->player_pos.y)][(int)(rc->player_pos.x + rc->wens.x * rc->speed.forward)] == '@')
		rc->player_pos.x += rc->wens.x * rc->speed.forward;
}

void	step_back(t_rc *rc)
{
	if (rc->arr[(int)(rc->player_pos.y - rc->wens.y * rc->speed.forward)][(int)(rc->player_pos.x)] == '@')
		rc->player_pos.y -= rc->wens.y * rc->speed.forward;
	if (rc->arr[(int)(rc->player_pos.y)][(int)(rc->player_pos.x - rc->wens.x * rc->speed.forward)] == '@')
		rc->player_pos.x -= rc->wens.x * rc->speed.forward;
}

void	step_right(t_rc *rc)
{
    if (rc->arr[(int)(rc->player_pos.y + rc->plane.y * rc->speed.forward)][(int)(rc->player_pos.x)] == '@')
        rc->player_pos.y += rc->plane.y * rc->speed.forward;
    if (rc->arr[(int)(rc->player_pos.y)][(int)(rc->player_pos.x + rc->plane.x * rc->speed.forward)] == '@')
        rc->player_pos.x += rc->plane.x * rc->speed.forward;
}

void	step_left(t_rc *rc)
{
    if (rc->arr[(int)(rc->player_pos.y - rc->plane.y * rc->speed.forward)][(int)(rc->player_pos.x)] == '@')
        rc->player_pos.y -= rc->plane.y * rc->speed.forward;
    if (rc->arr[(int)(rc->player_pos.y)][(int)(rc->player_pos.x - rc->plane.x * rc->speed.forward)] == '@')
        rc->player_pos.x -= rc->plane.x * rc->speed.forward;
}

void	rot_right(t_rc *rc)
{
	double	wens_y;
	double	plane_y;
	
	wens_y = rc->wens.y;
	rc->wens.y = rc->wens.y * cos(rc->speed.rot) - rc->wens.x * sin(rc->speed.rot);
	rc->wens.x = wens_y * sin(rc->speed.rot) + rc->wens.x * cos(rc->speed.rot);
	plane_y = rc->plane.y;
	rc->plane.y = rc->plane.y * cos(rc->speed.rot) - rc->plane.x * sin(rc->speed.rot);
	rc->plane.x = plane_y * sin(rc->speed.rot) + rc->plane.x * cos(rc->speed.rot);
}

void	rot_left(t_rc *rc)
{
	double	wens_y;
	double	plane_y;
	
	wens_y = rc->wens.y;
	rc->wens.y = rc->wens.y * cos(-rc->speed.rot) - rc->wens.x * sin(-rc->speed.rot);
	rc->wens.x = wens_y * sin(-rc->speed.rot) + rc->wens.x * cos(-rc->speed.rot);
	plane_y = rc->plane.y;
	rc->plane.y = rc->plane.y * cos(-rc->speed.rot) - rc->plane.x * sin(-rc->speed.rot);
	rc->plane.x = plane_y * sin(-rc->speed.rot) + rc->plane.x * cos(-rc->speed.rot);
}

int		finish(t_rc *rc)
{
	rc->speed.forward = 0;
	exit(0);
	return (0);
}

int		key_press(int code, t_rc *rc)
{
	printf("key pressed: %d\n", code);
	if (code == KEY_ESC)
		finish(rc);
	if (code == KEY_W)
		rc->keys.w = 1;
	if (code == KEY_S)
		rc->keys.s = 1;
	if (code == KEY_A)
		rc->keys.a = 1;
	if (code == KEY_D)
		rc->keys.d = 1;
	if (code == KEY_AR)
		rc->keys.arr_r = 1;
	if (code == KEY_AL)
		rc->keys.arr_l = 1;
	if (code == KEY_SHIFT_L || code == KEY_SHIFT_R)
	{
		rc->speed.forward *= 2;
		rc->speed.rot *= 2;
	}
	
	return (0);
}

int		key_unpress(int code, t_rc *rc)
{
	if (code == KEY_W)
		rc->keys.w = 0;
	if (code == KEY_S)
		rc->keys.s = 0;
	if (code == KEY_A)
		rc->keys.a = 0;
	if (code == KEY_D)
		rc->keys.d = 0;
	if (code == KEY_AR)
		rc->keys.arr_r = 0;
	if (code == KEY_AL)
		rc->keys.arr_l = 0;
	if (code == KEY_SHIFT_L || code == KEY_SHIFT_R)
	{
		rc->speed.forward /= 2;
		rc->speed.rot /= 2;
	}

	return (0);
}

int		handle_loop(t_rc	*rc)
{
	// mlx_do_sync(rc->mlx);
	if (rc->keys.w)
		step_forward(rc);
	if (rc->keys.s)
		step_back(rc);
	if (rc->keys.a)
		step_left(rc);
	if (rc->keys.d)
		step_right(rc);
	if (rc->keys.arr_l)
		rot_left(rc);
	if (rc->keys.arr_r)
		rot_right(rc);

	drawer(rc);
	draw_sprites(rc);
	mlx_put_image_to_window(rc->mlx, rc->win, rc->img.ptr, 0, 0);
	return (0);
}

void	init_txtr_imgs(t_rc	*rc)
{
	rc->t.so.img.ptr = mlx_xpm_file_to_image(rc->mlx, rc->data->so, &rc->t.so.h, &rc->t.so.w);
	rc->t.so.img.addr = mlx_get_data_addr(rc->t.so.img.ptr, &rc->t.so.img.bpp, &rc->t.so.img.length, &rc->t.so.img.endian);
	rc->t.no.img.ptr = mlx_xpm_file_to_image(rc->mlx, rc->data->no, &rc->t.no.h, &rc->t.no.w);
	rc->t.no.img.addr = mlx_get_data_addr(rc->t.no.img.ptr, &rc->t.no.img.bpp, &rc->t.no.img.length, &rc->t.no.img.endian);
	rc->t.ea.img.ptr = mlx_xpm_file_to_image(rc->mlx, rc->data->ea, &rc->t.ea.h, &rc->t.ea.w);
	rc->t.ea.img.addr = mlx_get_data_addr(rc->t.ea.img.ptr, &rc->t.ea.img.bpp, &rc->t.ea.img.length, &rc->t.ea.img.endian);
	rc->t.we.img.ptr = mlx_xpm_file_to_image(rc->mlx, rc->data->we, &rc->t.we.h, &rc->t.we.w);
	rc->t.we.img.addr = mlx_get_data_addr(rc->t.we.img.ptr, &rc->t.we.img.bpp, &rc->t.we.img.length, &rc->t.we.img.endian);
	rc->t.s.img.ptr = mlx_xpm_file_to_image(rc->mlx, rc->data->s, &rc->t.s.h, &rc->t.s.w);
	rc->t.s.img.addr = mlx_get_data_addr(rc->t.s.img.ptr, &rc->t.s.img.bpp, &rc->t.s.img.length, &rc->t.s.img.endian);
}

void	init_mlx(t_rc *rc)
{
	rc->mlx = mlx_init();
	rc->win = mlx_new_window(rc->mlx, rc->data->res.x, rc->data->res.y, "21");
	rc->img.ptr = mlx_new_image(rc->mlx, rc->data->res.x, rc->data->res.y);
	rc->img.addr = mlx_get_data_addr(rc->img.ptr, &rc->img.bpp, &rc->img.length, &rc->img.endian);
	rc->player_pos.x = (double)rc->data->pos.x + 0.5;
	rc->player_pos.y = (double)rc->data->pos.y + 0.5;
	init_txtr_imgs(rc);
	rc->wens_defined = 0;
	rc->zb = malloc(sizeof(int) * rc->data->res.x);
}

void	init_windows(char **arr, t_map *data)
{
	t_rc	*rc;

	if (!(rc = malloc(sizeof(t_rc))))
		error("Malloc error\n");
	rc->arr = arr;
	rc->data = data;
	init_keys(rc);
	init_mlx(rc);

	drawer(rc);
	draw_sprites(rc);
	mlx_hook(rc->win, 2, 0, key_press, rc);
	mlx_hook(rc->win, 3, 0, key_unpress, rc);
	mlx_hook(rc->win, 17, 0, finish, rc);
	mlx_loop_hook(rc->mlx, handle_loop, rc);
	mlx_loop(rc->mlx);
}
