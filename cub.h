#ifndef CUB_H
# define CUB_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "minilibx/mlx.h"

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

typedef struct	s_res
{
	int x_max;
	int y_max;
	int	x;
	int	y;
}				t_res;

typedef struct	s_pos
{
	double x;
	double y;
}				t_pos;

typedef struct	s_map
{
	t_list		*list;
	t_colors	c_colors;
	t_colors	f_colors;
	t_res		res;
	t_pos		pos;
	char		*we;
	char		*ea;
	char		*so;
	char		*no;
	char		*s;
}				t_map;

typedef struct	s_img
{
	void	*ptr;
    char	*addr;
    int		bpp;
    int		length;
    int		endian;
}				t_img;

/*
 *	Kinda general functions
 */
void	error(char *err);
void	init_str_and_map(char **str, t_map *map);

/*
 *	List validation functions
 */
void	iterate_list(t_map *map);
int		is_map_line(char *str);
int		is_wside(char *str);
int		is_xpm_file(char *str);
void	fill_resolution(t_map *map, char *res_x, char *res_y);
void	define_file(t_map *map, char *type, char *file);
void	fill_s_c_f(t_map *map, char c, char *file);
int		is_colors_set(char *str);
void	store_colors(t_map *map, char type, char *str);
int		is_param(char *str);

/*
 *	Map validation functions
 */
void	convert_to_array(t_list *map_list, t_map *data);
void	validate_map(char **arr, t_map *data);

/*
 *	GUI functions
 */
void	init_windows(char **arr, t_map *data);

/*
 *	Additional utils
 */
int		ft_isnumber(char *str);
size_t	get_max(size_t a, size_t b);

#endif
