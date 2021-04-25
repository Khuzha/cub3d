/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:46:43 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 13:49:37 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	quicksort(t_sprite *arr, int first, int last)
{
	t_sprite	tmp;
	t_qs		data;

	if (first < last)
	{
		data.middle = arr[(first + last) / 2].dist;
		data.i = first - 1;
		data.j = last + 1;
		while (1)
		{
			data.i++;
			while (arr[data.i].dist > data.middle && data.i < last)
				data.i++;
			data.j--;
			while (arr[data.j].dist < data.middle && data.j > 0)
				data.j--;
			if (data.i >= data.j)
				break ;
			tmp = arr[data.i];
			arr[data.i] = arr[data.j];
			arr[data.j] = tmp;
		}
		quicksort(arr, first, data.i - 1);
		quicksort(arr, data.j + 1, last);
	}
}
