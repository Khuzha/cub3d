#include "cub.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*str;
	t_list	*map_list;

	if (argc < 1)
		return (-1);
	init_str_and_list(&str, &map_list);
	fd = open(argv[1], O_RDONLY);
	while(get_next_line(fd, &str) > 0)
	{
		ft_lstadd_back(&map_list, ft_lstnew(str));
	}
	ft_lstadd_back(&map_list, ft_lstnew(str));
	validate_map(map_list);
}