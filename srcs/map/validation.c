#include "../../cub.h"

void	check_players_count(char **arr)
{
	char	counter;

	counter = 0;
	while (*arr)
	{
		while (**arr)
		{
			if (ft_strchr("WENS", **arr))
				counter++;
			if (counter > 1)
				error("Wrong players count");
			(*arr)++;
		}
		arr++;
	}
	printf("found %d players\n", (int)counter);
}

void	validate_map(char **arr, t_map *data)
{
	check_players_count(arr);
	data++;
}