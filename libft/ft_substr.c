/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:55:20 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 13:55:21 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	i = 0;
	if (!s || !(res = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (start >= ft_strlen(s))
		return (res);
	while (s[start] && len)
	{
		res[i] = s[start];
		i++;
		start++;
		len--;
	}
	res[i] = '\0';
	return (res);
}
