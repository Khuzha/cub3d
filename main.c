/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 19:56:30 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 20:22:23 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (get_next_line(fd, &str) > 0)
	{
		ft_lstadd_back(&(map->list), ft_lstnew(str));
	}
	ft_lstadd_back(&(map->list), ft_lstnew(str));
	iterate_list(map);
}
