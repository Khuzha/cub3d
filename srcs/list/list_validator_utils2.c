/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_validator_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:26:25 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 16:24:34 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

int	is_wside(char *str)
{
	if (!str || !(*str) ||
		(ft_strncmp(str, "WE", 3) &&
		ft_strncmp(str, "EA", 3) &&
		ft_strncmp(str, "SO", 3) &&
		ft_strncmp(str, "NO", 3)))
		return (0);
	return (1);
}

int	is_xpm_file(char *str)
{
	char	*ext;

	ext = ft_substr(str, ft_strlen(str) - 4, 4);
	if (!str || ft_strncmp(ext, ".xpm", 5))
		return (0);
	free(ext);
	return (1);
}

int	is_colors_set_1(char *str)
{
	char	**set;
	int		i;

	i = 0;
	set = ft_split(str, ',');
	while (set && set[i])
	{
		if (!set || !(set[i]) || !ft_isnumber(set[i]))
			return (0);
		i++;
	}
	set ? clean_arr(set) : 0;
	set = NULL;
	return (i == 3);
}

int	is_colors_set(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == ',' && str[i + 1] == ',')
			return (0);
		i++;
	}
	if (i >= 2)
		str += 2;
	else
		return (0);
	return (is_colors_set_1(str));
}

int	is_map_line(char *str)
{
	while (str && *str)
	{
		if (*str != '1' || *str != ' ')
			return (0);
		str++;
	}
	return (1);
}
