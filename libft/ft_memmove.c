#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*new_dst;
	unsigned char	*new_src;

	if (!dst && !src)
		return (NULL);
	new_dst = (unsigned char *)dst;
	new_src = (unsigned char *)src;
	while (src > dst && n)
	{
		*new_dst = *new_src;
		new_src++;
		new_dst++;
		n--;
	}
	while (src <= dst && n)
	{
		new_dst[n - 1] = new_src[n - 1];
		n--;
	}
	return (dst);
}
