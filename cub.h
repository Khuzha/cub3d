#ifndef CUB_H
# define CUB_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "minilibx/mlx.h"

# include <stdio.h>
# include <math.h>

typedef enum {
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_W = 13,
	KEY_AL = 123,
	KEY_AR = 124,
	KEY_AD = 125,
	KEY_AT = 126,
	KEY_SHIFT_L = 257,
	KEY_SHIFT_R = 258,
	KEY_ESC = 53
}	t_buttons;

typedef struct	s_keys
{
	char	a;
	char	d;
	char	s;
	char	w;
	char	arr_l;
	char	arr_r;
	char	arr_t;
	char	arr_d;
}				t_keys;


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
	int	x;
	int	y;
	int	defined;
}				t_res;

typedef struct	s_pos
{
	double x;
	double y;
}				t_pos;

typedef struct	s_sprite
{
	double	y;
	double	x;
	double	dist;
}				t_sprite;

typedef struct	s_map
{
	t_list		*list;
	t_colors	c_colors;
	t_colors	f_colors;
	t_res		res;
	t_pos		pos;
	int			s_count;
	char		player;
	char		*we;
	char		*ea;
	char		*so;
	char		*no;
	char		*s;
	t_sprite	*sprites;
	int			is_scnsht;
	size_t		l_width;
}				t_map;

typedef struct	s_img
{
	void	*ptr;
    char	*addr;
    int		bpp;
    int		length;
    int		endian;
}				t_img;

typedef struct	s_dxy
{
	double	x;
	double	y;
}				t_dxy;

typedef struct	s_ixy
{
	int	x;
	int	y;
}				t_ixy;


typedef struct	s_speed
{
	double	forward;
	double	rot;
}				t_speed;

typedef struct	s_wall
{
	int	height;
	int start;
	int	finish;
	int	color;
}				t_wall;

typedef struct s_txtr
{
	t_img	img;
	int		h;
	int		w;
}				t_txtr;

typedef struct	s_all_txtrs
{
	t_txtr	so;
	t_txtr	no;
	t_txtr	ea;
	t_txtr	we;
	t_txtr	s;
}				t_all_txtrs;

typedef struct	s_txtr_rc
{
	double	s;
	double	p;
}				t_txtr_rc;

typedef struct	s_rc
{
	char		**arr;
	t_map		*data;
	t_dxy		player_pos;
	t_dxy		ray_dir;
	t_dxy		wens;
	t_ixy		ray_square;
	t_dxy		closest_line;
	t_dxy	next_line;
	t_dxy	plane;
	t_ixy	ray_step;
	t_img	img;
	t_wall	wall;
	t_speed	speed;
	t_keys	keys;
	t_all_txtrs	t;
	t_txtr	cur_side;
	t_sprite *sprites;
	double	*zb;
	double	dist_to_wall;
	double	cam;
	void	*mlx;
	void	*win;
	int		was_hit;
	int		side;
	int		wens_defined;
}				t_rc;

typedef struct	s_txtr_data
{
	double	wall_x;
	double	tex_y;
	double	tex_x;
	double	step;
	double	tex_pos;
}				t_txtr_data;

typedef struct	s_s_rc
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_y;
	double	transform_x;
	int		sprite_screen_x;
	int		sprite_height;
	int		draw_start_y;
	int		draw_end_y;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	int		mv_scr;
	int		d;
	int		tex_y;
	int		tex_x;
}				t_s_rc;

typedef struct	s_qs
{
	int			middle;
	int			i;
	int			j;
}				t_qs;

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
 *	Sprites
 */
void	init_sprites(char **arr, t_map *data);
void	recalc_sprites(t_rc *rc);

/*
 *	GUI functions
 */
void	init_windows(char **arr, t_map *data);
void	draw_sprites(t_rc *rc);
void	put_pixel(t_img img, int x, int y, int color);
int		make_trgb(int t, int r, int g, int b);
int		drawer(t_rc *rc);
void	handle_player_dir(t_rc *rc, t_map *data);
void	handle_rc(t_rc *rc, t_map *data, int x);
void	init_keys(t_rc *rc);
void	init_rc(t_rc *rc, t_map *data);
void	init_mlx(t_rc *rc);
int		key_press(int code, t_rc *rc);
int		key_unpress(int code, t_rc *rc);
int		handle_loop(t_rc *rc);
int		get_pixel(t_txtr txtr, t_txtr_data *data);
void	put_pixel(t_img img, int x, int y, int color);
void	rot_right(t_rc *rc);
void	rot_left(t_rc *rc);
void	step_forward(t_rc *rc);
void	step_back(t_rc *rc);
void	step_right(t_rc *rc);
void	step_left(t_rc *rc);
void	calc_wall(t_rc *rc, t_map *data);
void	define_color(t_rc *rc);
void	calcs_for_txtr(t_rc *rc, t_txtr_data *data);
void	prepare_rc(t_rc *rc);
void	run_dda(t_rc *rc, char **arr);
void	define_side(t_rc *rc);

/*
 *	Screenshots
 */
void	make_scrsht(t_rc *rc);

/*
 *	Additional utils
 */
int		ft_isnumber(char *str);
size_t	get_max(size_t a, size_t b);
double	ft_abs_dbl(double num);
void	quicksort(t_sprite *arr, int first, int last);
void	print_sprites(t_map *data, t_dxy player_pos);
double	get_decimal(double num);
double	get_floor(double num);
double	get_up(double num);
int		make_trgb(int t, int r, int g, int b);
int		finish(t_rc *rc);
void	miss_zeros(char **res_x, char **res_y);
int		get_min(int a, int b);
int		count_commas(char *str);
size_t	ft_strlen_without_spaces(char *str);
void	init_lines(char **arr, size_t width);
void	check_char(char c);

#endif
