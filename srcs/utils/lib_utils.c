#include "../../cub.h"

int		ft_isnumber(char *str)
{
	printf("str = |%s|\n", str);
	int was_space;
	int	was_num;

	was_num = 0;
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
		ft_isdigit(*str) ? was_num = 1 : 0;
		str++;
	}
	printf("isnumber = %d\n", was_num);
	return (was_num);
}

size_t	get_max(size_t a, size_t b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

double	ft_abs_dbl(double num) {
	if (num >= 0)
		return (num);
	else
		return (num *= -1);
}