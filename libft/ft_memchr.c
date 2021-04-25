/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:54:35 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 13:54:35 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*new_s;
	size_t			i;

	i = 0;
	new_s = (unsigned char *)s;
	while (i < n)
	{
		if (new_s[i] == (unsigned char)c)
			return (void *)&s[i];
		i++;
	}
	return (NULL);
}
