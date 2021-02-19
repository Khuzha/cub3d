#include "cub.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*str;
	t_map	*map;

	if (argc < 1)
		return (-1);
	if (!(map = ft_calloc(1, sizeof(map))))
		return (-1);
	init_str_and_map(&str, map);
	fd = open(argv[1], O_RDONLY);
	printf("bef loop, fd = %d\n", fd);
	while(get_next_line(fd, &str) > 0)
	{
		printf("in loop\n");
		ft_lstadd_back(&map->list, ft_lstnew(str));
	}
	printf("aft loop\n");
	ft_lstadd_back(&map->list, ft_lstnew(str));
	validate_map(map);
}