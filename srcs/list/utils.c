/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:25:26 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 13:33:55 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	init_str_and_map(char **str, t_map *map)
{
	*str = NULL;
	map->list = NULL;
	map->res.x = 0;
	map->res.y = 0;
	map->we = NULL;
	map->ea = NULL;
	map->so = NULL;
	map->no = NULL;
	map->s = NULL;
	map->c_colors.defined = 0;
	map->f_colors.defined = 0;
	map->pos.x = 0;
	map->pos.y = 0;
}

void	miss_zeros(char **res_x, char **res_y)
{
	while (**res_x == '0')
		(*res_x)++;
	while (**res_y == '0')
		(*res_y)++;
}

int		get_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int		count_commas(char *str)
{
	int res;

	res = 0;
	while (*str)
	{
		if (*str == ',')
			res++;
		str++;
	}
	return (res);
}

size_t	ft_strlen_without_spaces(char *str)
{
	size_t	len;

	while (*str == ' ')
		str++;
	len = ft_strlen(str);
	while (str[len - 1] == ' ')
		len--;
	return (len);
}
