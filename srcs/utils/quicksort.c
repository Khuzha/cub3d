#include "../../cub.h"

void	quicksort(t_sprite *arr, int first, int last)
{
	t_sprite	tmp;
	int			middle;
	int			i;
	int			j;

	if (first < last)
	{
		middle = arr[(first + last) / 2].dist;
		i = first - 1;
		j = last + 1;
		while (1)
		{
			i++;
			while (arr[i].dist > middle && i < last)
				i++;
			j--;
			while (arr[j].dist < middle && j > 0)
				j--;
			if (i >= j)
				break;
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
		quicksort(arr, first, i - 1);
		quicksort(arr, j + 1, last);
	}
}
