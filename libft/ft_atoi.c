/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:53:42 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 13:55:59 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	pos;

	pos = 1;
	res = 0;
	while (*str && ft_strchr(" \n\t\v\f\r", *str))
		str++;
	if (*str == '-')
		pos = -1;
	if (ft_strchr("+-", *str))
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = (*str - '0') + (res * 10);
		str++;
	}
	return (res * pos);
}
