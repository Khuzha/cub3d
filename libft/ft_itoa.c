/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:54:05 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 13:54:05 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		count_digits(long n)
{
	int counter;

	if (n == 0)
		return (1);
	counter = 0;
	while (n != 0)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	int		pos;
	long	num;

	num = n;
	pos = num >= 0;
	len = count_digits(num) + (!pos ? 1 : 0);
	num *= pos ? 1 : -1;
	if (!(res = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	res[len] = '\0';
	while (len >= 0)
	{
		res[len - 1] = num % 10 + 48;
		num /= 10;
		len--;
	}
	if (!pos)
		res[0] = '-';
	return (res);
}
