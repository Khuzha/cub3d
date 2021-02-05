#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;

	res = NULL;
	if (!(res = malloc(size * count)))
		return (NULL);
	ft_bzero(res, count * size);
	return (res);
}
