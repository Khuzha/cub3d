/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:36:57 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 16:52:00 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	init_lines(char **arr, size_t width)
{
	while (*arr)
	{
		if (!(*arr = ft_calloc(sizeof(char) * width, width)))
			error("Malloc error");
		arr++;
	}
}

void	check_char(char c)
{
	if (!c || !ft_strchr("WENS", c))
		error("Map validation failed");
}

void	free_list(t_list *list)
{
	t_list	*backup;
	t_list	*tmp;

	backup = list;
	while (list->next)
	{
		tmp = list;
		list = list->next;
		free(tmp->content);
		free(tmp);
	}
	free(list->content);
	free(list);
}
