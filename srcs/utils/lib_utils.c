/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:45:59 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 20:37:15 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

int		ft_isnumber(char *str)
{
	int was_space;
	int	was_num;

	if (!str)
		return (0);
	was_num = 0;
	was_space = 0;
	while (*str == ' ')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != ' ')
			return (0);
		if (*str == ' ')
			was_space = 1;
		if (was_space && *str != ' ')
			return (0);
		ft_isdigit(*str) ? was_num = 1 : 0;
		str++;
	}
	return (was_num);
}

size_t	get_max(size_t a, size_t b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

double	ft_abs_dbl(double num)
{
	if (num >= 0)
		return (num);
	else
		return (num *= -1);
}
