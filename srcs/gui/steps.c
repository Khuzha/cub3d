#include "../../cub.h"

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
