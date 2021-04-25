/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:55:18 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 13:55:18 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		includes(const char *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*trim_bgn(char *src, char const *set)
{
	size_t	len;
	char	*res;

	len = ft_strlen(src);
	if (!(res = malloc(sizeof(char) * (len))))
		return (NULL);
	res = (char *)src;
	while (*res && includes(set, *res) && len)
	{
		res++;
		len--;
	}
	return (len > 0 ? res : ft_strdup(""));
}

char	*trim_end(char *res, char const *set)
{
	size_t	i;

	i = ft_strlen(res) - 1;
	while (i && includes(set, res[i]))
		i--;
	res = ft_substr(res, 0, i + 1);
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	char	*trimmed;
	char	*res;
	size_t	final_len;

	if (!s1)
		return (NULL);
	str = (char *)s1;
	if (!(trimmed = trim_bgn(str, set)))
		return (NULL);
	trimmed = trim_end(trimmed, set);
	final_len = ft_strlen(trimmed);
	res = trimmed;
	return (res);
}
