#include "../../cub.h"

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