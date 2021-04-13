#include "../../cub.h"

void	quicksort(t_sprite *arr, int first, int last)
{
	int 	left;
	int 	right;
	double 	middle;
	double	tmp;
	left = first;
	right = last;

	if (first >= last)
		return ;
	left = first;
	right = last;
	middle = arr[(left + right) / 2].dist;
	while (left <= right)
	{
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
