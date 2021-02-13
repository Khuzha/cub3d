#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ch;
	size_t			i;

	i = 0;
	ch = (unsigned char *)b;
	while (i < len)
	{
		ch[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
