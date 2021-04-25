/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zskeeter <zskeeter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:37:02 by zskeeter          #+#    #+#             */
/*   Updated: 2021/04/25 14:59:39 by zskeeter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

size_t	get_width(t_list *list, size_t height)
{
	size_t	width;

	width = 0;
	while (height)
	{
		width = get_max(width, ft_strlen(list->content));
		list = list->next;
		height--;
	}
	return (width);
}

size_t	get_height(t_list *list)
{
	size_t	counter;

	counter = 1;
	while (list->next)
	{
		list = list->next;
		counter++;
	}
	return (counter);
}

void	check_line(char *str)
{
	while (*str)
	{
		if (!ft_strchr("012WESN ", *str))
			error("Wrong map: extra sybmols");
		str++;
	}
}

void	fill_lines(char **arr, t_list *list, size_t height)
{
	size_t	i;

	i = 0;
	while (i < height)
	{
		if (!ft_strlen(list->content))
			error("Wrong map: it has empty lines");
		check_line(list->content);
		arr[i] = list->content;
		i++;
		list = list->next;
	}
	list++;
}

void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list->next)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

void	convert_to_array(t_list *list, t_map *data)
{
	size_t	height;
	char	**arr;

	height = get_height(list);
	data->l_width = get_width(list, height);
	if (!(arr = ft_calloc(sizeof(char *) * (height + 1), height + 1)))
		error("Malloc error");
	init_lines(arr, data->l_width);
	fill_lines(arr, list, height);
	free_list(data->backup);
	validate_map(arr, data);
}
