#include "../../cub.h"

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