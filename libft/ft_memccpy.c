/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:54:31 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 13:54:31 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*new_dst;
	unsigned char	*new_src;
	size_t			i;

	i = 0;
	new_dst = (unsigned char *)dst;
	new_src = (unsigned char *)src;
	while (i < n)
	{
		new_dst[i] = new_src[i];
		if (new_src[i] == (unsigned char)c)
			return (&dst[i + 1]);
		i++;
	}
	return (NULL);
}
