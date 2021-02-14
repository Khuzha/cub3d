#ifndef CUB_H
# define CUB_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"

# include <stdio.h>

/*
 *	Structures
 */
typedef struct	s_map
{
	t_list	*list;
	int		res_x;
	int		res_y;
	char	*we;
	char	*ea;
	char	*so;
	char	*no;
}				t_map;


/*
 *	Kinda general functions
 */
void	init_str_and_map(char **str, t_map *map);

/*
 *	Map validating functions
 */
int		validate_map(t_map *map);
int		is_wside(char *str);
int		is_xpm_file(char *str);
void	fill_resolution(t_map *map, int res_y, int res_x);
void	fill_wside(t_map *map, char *wside, char *file);

/*
 *	Additional utils
 */
int		ft_isnumber(char *str);


#endif
