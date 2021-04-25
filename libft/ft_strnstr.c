/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:55:15 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 13:55:15 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *dst, const char *trg, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(trg) == 0)
		return ((char *)dst);
	while (dst[i] && len != 0 && i < len)
	{
		if (dst[i] == *trg)
		{
			j = 0;
			while (dst[i + j] == trg[j] && dst[i + j] && trg[j])
				j++;
			if (!trg[j] && i + j <= len)
				return ((char *)&dst[i]);
		}
		i++;
	}
	return (NULL);
}
