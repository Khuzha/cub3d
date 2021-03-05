#include "../../cub.h"

void	init_windows(char **arr, t_map *data)
{
	void	*mlx;
	void	*window;

	mlx = mlx_init();
	window = mlx_new_window(mlx, 1920, 1080, "first");
	data++;
	arr++;
}