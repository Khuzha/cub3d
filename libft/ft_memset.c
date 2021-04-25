/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:54:46 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 13:54:46 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ch;
	size_t			i;

	i = 0;
	ch = (unsigned char *)b;
	while (i < len)
	{
		ch[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
