#ifndef CUB_H
# define CUB_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"

# include <stdio.h>

/*
 *	Structures
 */
typedef struct	s_colors
{
	int defined;
	int	r;
	int	g;
	int	b;
}				t_colors;

typedef struct	s_map
{
	t_list		*list;
	t_colors	c_colors;
	t_colors	f_colors;
	int			res_x;
	int			res_y;
	char		*we;
	char		*ea;
	char		*so;
	char		*no;
	char		*s;
}				t_map;


/*
 *	Kinda general functions
 */
void	error(char *err);
void	init_str_and_map(char **str, t_map *map);

/*
 *	Map validating functions
 */
int		validate_map(t_map *map);
int		is_wside(char *str);
int		is_xpm_file(char *str);
void	fill_resolution(t_map *map, int res_y, int res_x);
void	define_file(t_map *map, char *type, char *file);
void	fill_s_c_f(t_map *map, char c, char *file);
int		is_colors_set(char *str);
void	store_colors(t_map *map, char type, char *str);
int		is_param(char *str);

/*
 *	Additional utils
 */
int		ft_isnumber(char *str);


#endif
