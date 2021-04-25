/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:25:26 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 13:25:26 by zskeeter         ###   ########.fr       */
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
