#include "cub.h"


int	main(int argc, char **argv)
{
	int		fd;
	char	*str;
	t_list	*list;

	if (argc < 1)
		return (-1);
	fd = open(argv[1], O_RDONLY);
}