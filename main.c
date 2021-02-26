#include "cub.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*str;
	t_map	map;

	if (argc < 1)
		return (-1);
	init_str_and_map(&str, &map);
	fd = open(argv[1], O_RDONLY);
	while(get_next_line(fd, &str) > 0)
	{
		ft_lstadd_back(&map.list, ft_lstnew(str));
	}
	ft_lstadd_back(&map.list, ft_lstnew(str));
	iterate_list(&map);
	printf("res_x = %d, res_y = %d, x_max = %d, y_max = %d \nwe = %s, ea = %s, so = %s, no = %s, \nsprite = %s \n", map.res.x, map.res.y, map.res.x_max, map.res.y_max, map.we, map.ea, map.so, map.no, map.s);
	printf("c = %d,%d,%d; f = %d,%d,%d\n", map.c_colors.r, map.c_colors.g, map.c_colors.b, map.f_colors.r, map.f_colors.g, map.f_colors.b);
}