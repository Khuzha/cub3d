/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_validator_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:27:30 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/27 20:25:23 by zskeeter         ###   ########.fr       */
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

	miss_zeros(&res_x, &res_y);
	if (map->res.defined || !res_x || !res_y ||
		!ft_strlen(res_x) || !ft_strlen(res_y))
		error("Wrong resolution");
	if (map->is_scnsht)
	{
		max_y = 10000;
		max_x = 10000;
	}
	else
		mlx_get_screen_size(&max_x, &max_y);
	if (ft_strlen(res_x) > 5)
		map->res.x = max_x;
	else
		map->res.x = get_min(ft_atoi(res_x), max_x);
	if (ft_strlen(res_y) > 5)
		map->res.y = max_y;
	else
		map->res.y = get_min(ft_atoi(res_y), max_y);
	map->res.defined = 1;
}

void	define_file(t_map *map, char *type, char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Invalid map (file couldn't be open)");
	if (!ft_strncmp(type, "WE", 3) && !map->we)
		map->we = ft_strdup(file);
	else if (!ft_strncmp(type, "EA", 3) && !map->ea)
		map->ea = ft_strdup(file);
	else if (!ft_strncmp(type, "SO", 3) && !map->so)
		map->so = ft_strdup(file);
	else if (!ft_strncmp(type, "NO", 3) && !map->no)
		map->no = ft_strdup(file);
	else if (!ft_strncmp(type, "S", 2) && !map->s)
		map->s = ft_strdup(file);
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
	if ((type == 'C' && map->c_colors.defined) ||
		(type == 'F' && map->f_colors.defined))
		error("Colors are repeating");
	check_colors(set);
	if (type == 'C')
	{
		map->c_colors.defined = 1;
		map->c_colors.r = ft_atoi(set[0]);
		map->c_colors.g = ft_atoi(set[1]);
		map->c_colors.b = ft_atoi(set[2]);
	}
	if (type == 'F')
	{
		map->f_colors.defined = 1;
		map->f_colors.r = ft_atoi(set[0]);
		map->f_colors.g = ft_atoi(set[1]);
		map->f_colors.b = ft_atoi(set[2]);
	}
	set ? clean_arr(set) : 0;
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
