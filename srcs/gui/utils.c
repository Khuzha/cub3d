#include "../../cub.h"

double	get_decimal(double num)
{
	int	integer;

	if ((num < 1 && num > 0) || (num > -1 && num < 0))
		return (num);
	integer = (int)num;
	return (num - integer);
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

int		make_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int		finish(t_rc *rc)
{
	rc->speed.forward = 0;
	exit(0);
	return (0);
}
