#include "../cub.h"

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
		if (was_space && ft_isdigit(*str))
			return 0;
		str++;
	}
	return (1);
}