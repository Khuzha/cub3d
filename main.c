/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 19:56:30 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/27 19:58:58 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_args(int argc, char **argv, t_map *data)
{
	if (ft_strncmp(argv[0], "./cub3D", 8))
		error("Executable file's name should be 'cub3D'");
	if (argc == 1 || (argc > 2 && ft_strncmp(argv[2], "--save", 7)))
		error("Wrong arguements");
	if (argc == 3 && !ft_strncmp(argv[2], "--save", 7))
		data->is_scnsht = 1;
	if (ft_strncmp(ft_substr(argv[1], ft_strlen(argv[1]) - 4, 4), ".cub", 5))
		error("Wrong map file format");
}

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
	check_args(argc, argv, map);
	while (get_next_line(fd, &str) > 0)
		ft_lstadd_back(&(map->list), ft_lstnew(str));
	ft_lstadd_back(&(map->list), ft_lstnew(str));
	iterate_list(map);
}
