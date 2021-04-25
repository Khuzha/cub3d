/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:54:56 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 13:54:56 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_strs(char const *s, char c)
{
	size_t	res;
	int		is_target;

	res = 0;
	is_target = 0;
	while (*s)
	{
		if (!is_target && *s != c)
		{
			res++;
			is_target = 1;
		}
		if (is_target && *s == c)
			is_target = 0;
		s++;
	}
	return (res);
}

size_t	find_size(char const *src, int c)
{
	size_t	res;

	res = 0;
	while (*src && *src != c)
	{
		res++;
		src++;
	}
	return (res);
}

void	fill_str(char *target, char const *src, char c)
{
	while (*src && *src != c)
	{
		*target = *src;
		target++;
		src++;
	}
	*target = '\0';
}

int		fill_arr(char **arr, char const *src, char c)
{
	size_t	num;
	size_t	str_size;
	int		is_target;

	num = 0;
	is_target = 0;
	while (*src)
	{
		if (!is_target && *src != c)
		{
			str_size = find_size(src, c);
			if (!(arr[num] = malloc(sizeof(char) * (str_size + 1))))
				return (0);
			fill_str(arr[num], src, c);
			is_target = 1;
			num++;
		}
		if (is_target && *src == c)
			is_target = 0;
		src++;
	}
	arr[num] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	size;
	char	**res;

	if (!s)
		return (NULL);
	size = count_strs(s, c);
	if (!(res = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	if (!fill_arr(res, s, c))
	{
		while (size)
		{
			free(res[size]);
			size--;
		}
		free(res);
		return (NULL);
	}
	return (res);
}
