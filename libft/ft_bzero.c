/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:53:46 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 13:53:46 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	if (n == 0)
		return ;
	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = (unsigned char)0;
		i++;
	}
}
