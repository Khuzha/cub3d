#include "cub.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*str;
	t_map	*map;

	if (argc < 1)
		return (-1);
	if (!(map = ft_calloc(sizeof(t_map), sizeof(t_map))))
		error("Malloc error");
	init_str_and_map(&str, map);
	fd = open(argv[1], O_RDONLY);
	if (argc == 3 && !ft_strncmp(argv[2], "--save", 7))
		map->is_scnsht = 1;
	while(get_next_line(fd, &str) > 0)
		ft_lstadd_back(&(map->list), ft_lstnew(str));
	ft_lstadd_back(&(map->list), ft_lstnew(str));
	iterate_list(map);
}
