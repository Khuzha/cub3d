#include "../../cub.h"

int		ft_isnumber(char *str)
{
	int was_space;

	was_space = 0;
	while (*str == ' ')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != ' ')
			return (0);
		if (*str == ' ')
			was_space = 1;
		if (was_space && *str != ' ')
			return 0;
		str++;
	}
	return (1);
}

size_t	get_max(size_t a, size_t b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

double	ft_abs_dvl(double num) {
	if (num >= 0)
		return (num);
	else
		return (num *= -1);
}