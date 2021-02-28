#include "../../cub.h"

size_t	count_players(char **arr)
{
	size_t	counter;

	counter = 0;
	// while (*arr)
}

void	validate_map(char **arr, t_map *data)
{
	if (count_players(arr) != 1)
		error("Wrong players number");
	data++;
}