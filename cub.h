#ifndef CUB_H
# define CUB_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"

# include <stdio.h>

typedef struct	s_map
{
	t_list	*list;
	int		res_x;
	int		res_y;
}				t_map;

void	init_str_and_map(char **str, t_map **map);
int		validate_map(t_map *map);


/*
 *	Additional utils
 */
void	fill_resolution(t_map *map, int res_y, int res_x);
int		ft_isnumber(char *str);

#endif
