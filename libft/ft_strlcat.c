/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:55:04 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 13:55:04 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_real_size;
	size_t	src_real_size;
	size_t	dst_size_for_return;

	dst_real_size = ft_strlen(dst);
	src_real_size = ft_strlen(src);
	if (dstsize > dst_real_size)
	{
		i = dst_real_size;
		while (i < dstsize - 1 && *src)
		{
			dst[i] = *src;
			src++;
			i++;
		}
		if (i >= dst_real_size)
			dst[i] = '\0';
	}
	dst_size_for_return = dstsize < dst_real_size ? dstsize : dst_real_size;
	return (dst_size_for_return + src_real_size);
}
