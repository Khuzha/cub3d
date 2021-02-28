#include "../../cub.h"

void error(char *err)
{
	ft_putstr_fd(err, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}