/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 09:29:31 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 16:56:31 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	fill_struct(t_map *map, char **arr, char *str)
{
	if (!ft_strchr("AECFNORSW", ((char *)map->list->content)[0]))
		return ;
	if (!arr[0] && *str == ' ')
		error("Invalid map (empty line contains spaces)");
	if (arr[0] && arr[0][0] == 'R' && !arr[0][1] &&
		ft_isnumber(arr[1]) && ft_isnumber(arr[2]) && !arr[3])
		fill_resolution(map, arr[1], arr[2]);
	if ((is_wside(arr[0]) || (arr[0] && arr[0][0] == 'S'))
		&& is_xpm_file(arr[1]) && !arr[2])
		define_file(map, arr[0], arr[1]);
	if (arr[0] && arr[0][0] && arr[1] && arr[0] &&
		ft_strchr("CF", arr[0][0]) && !arr[0][1] && is_colors_set(str))
		store_colors(map, arr[0][0], str);
}

void	check_map(t_map *map)
{
	if ((map->res.x <= 0) || (map->res.y <= 0) ||
		!map->we || !ft_strlen(map->we) || !map->ea || !ft_strlen(map->ea) ||
		!map->so || !ft_strlen(map->so) || !map->no || !ft_strlen(map->no) ||
		!map->s || !ft_strlen(map->s) ||
		!map->c_colors.defined || !map->f_colors.defined ||
		map->c_colors.r > 255 || map->c_colors.g > 255 ||
		map->c_colors.b > 255 || map->f_colors.r > 255 ||
		map->f_colors.g > 255 || map->f_colors.b > 255)
		error("Invalid map");
}

void	clean_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	iterate_list(t_map *map)
{
	char	**arr;
	char	was_map;

	map->backup = map->list;
	was_map = 0;
	while (map->list->next)
	{
		arr = ft_split(map->list->content, ' ');
		if (arr[0] && !(is_param(arr[0]) && arr[1]) &&
			!is_map_line(map->list->content))
		{
			was_map = 1;
			check_map(map);
			convert_to_array(map->list, map);
			clean_arr(arr);
			break ;
		}
		fill_struct(map, arr, map->list->content);
		map->list = map->list->next;
		clean_arr(arr);
		arr = NULL;
	}
	if (!was_map)
		error("No map found");
}
