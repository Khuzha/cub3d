/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_validator_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:27:30 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 14:49:04 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	check_colors(char **set)
{
	if (!ft_strlen(*set) || ft_strlen_without_spaces(*set) > 3 ||
		!ft_strlen(set[1]) || ft_strlen_without_spaces(set[1]) > 3 ||
		!ft_strlen(set[2]) || ft_strlen_without_spaces(set[2]) > 3)
		error("Colors are wrong");
}

void	fill_resolution(t_map *map, char *res_x, char *res_y)
{
	int	max_y;
	int	max_x;

	mlx_get_screen_size(&max_x, &max_y);
	miss_zeros(&res_x, &res_y);
	if (ft_strlen(res_x) > 5)
		map->res.x = max_x;
	else
		map->res.x = get_min(ft_atoi(res_x), max_x);
	if (ft_strlen(res_y) > 5)
		map->res.y = max_y;
	else
		map->res.y = get_min(ft_atoi(res_y), max_y);
}

void	define_file(t_map *map, char *type, char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Invalid map (file couldn't be open)");
	if (!ft_strncmp(type, "WE", 3) && !map->we)
		map->we = file;
	else if (!ft_strncmp(type, "EA", 3) && !map->ea)
		map->ea = file;
	else if (!ft_strncmp(type, "SO", 3) && !map->so)
		map->so = file;
	else if (!ft_strncmp(type, "NO", 3) && !map->no)
		map->no = file;
	else if (!ft_strncmp(type, "S", 2) && !map->s)
		map->s = file;
	else
		error("Invalid map (textures)");
}

void	store_colors(t_map *map, char type, char *str)
{
	char	**set;

	str += 2;
	if (count_commas(str) != 2)
		error("Invalid map (commas in colors)");
	set = ft_split(str, ',');
	check_colors(set);
	if (type == 'C')
	{
		if (map->c_colors.defined)
			error("Ceiling colors are repeating");
		map->c_colors.defined = 1;
		map->c_colors.r = ft_atoi(set[0]);
		map->c_colors.g = ft_atoi(set[1]);
		map->c_colors.b = ft_atoi(set[2]);
	}
	if (type == 'F')
	{
		if (map->f_colors.defined)
			error("Floor colors are repeating");
		map->f_colors.defined = 1;
		map->f_colors.r = ft_atoi(set[0]);
		map->f_colors.g = ft_atoi(set[1]);
		map->f_colors.b = ft_atoi(set[2]);
	}
	set ? free(set) : 0;
	set = NULL;
}

int		is_param(char *str)
{
	if (ft_strncmp(str, "R", 2) &&
		ft_strncmp(str, "WE", 3) &&
		ft_strncmp(str, "EA", 3) &&
		ft_strncmp(str, "SO", 3) &&
		ft_strncmp(str, "NO", 3) &&
		ft_strncmp(str, "S", 2) &&
		ft_strncmp(str, "C", 2) &&
		ft_strncmp(str, "F", 2))
	{
		return (0);
	}
	return (1);
}
