#include "../../cub.h"

void	quicksort(t_sprite *arr, int first, int last)
{
	int 	left;
	int 	right;
	double 	middle;
	double	tmp;
	left = first;
	right = last;
	// printf("1: dist = %f, ind = %d\n", arr[(left + right) / 2].dist, (left + right) / 2);
	// printf("2: dist = %f, ind = %d\n", arr[(first + last) / 2].dist, (first + last) / 2);
	// printf("szt: dist = %f, ind = %lu\n", arr[(size_t)(((size_t)first + (size_t)last) / 2)].dist, (size_t)((first + last) / 2));
	// size_t i = first;
	// while (i <= (size_t)last)
	// {
	// 	printf("IN: i = %lu, sprite: y = %f, x = %f, dist = %f\n", i, arr[i].y, arr[i].x, arr[i].dist);
	// 	i++;
	// }

	// printf("left = %d, right = %d\n", left, right);
	if (first >= last)
		return ;
	left = first;
	right = last;
	middle = arr[(left + right) / 2].dist;
	// printf("left = %d, right = %d, middle (pos %d) = %f\n", left, right, (left + right) / 2, middle);
	while (left <= right)
	{
		// printf("left = %d, l value = %f, middle = %f\n", left, arr[left].dist, middle);
		while (arr[left].dist < middle)
			left++;
		while (arr[right].dist > middle)
			right--;
		if (left <= right)
		{
			tmp = arr[left].dist;
			arr[left].dist = arr[right].dist;
			arr[right].dist = tmp;
			left++;
			right--;
		}
		quicksort(arr, first, right);
		quicksort(arr, left, last);
	}
}