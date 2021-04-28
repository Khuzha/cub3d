/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:16:49 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/28 21:31:52 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

int		get_pixel(t_txtr txtr, t_txtr_data *data)
{
	char			*pos;
	int	color;

	data->tex_y = (int)data->tex_pos % (txtr.h - 1);
	data->tex_pos += data->step;
	pos = txtr.img.addr + (int)(data->tex_y * txtr.img.length +
		data->tex_x * (txtr.img.bpp / 8));
	color = *((int	*)pos);
	return (color >= 0 ? color : 0);
}

void	put_pixel(t_img img, int x, int y, int color)
{
	char	*pos;

	pos = img.addr + (y * img.length + x * (img.bpp / 8));
	*((unsigned int	*)pos) = color;
}
