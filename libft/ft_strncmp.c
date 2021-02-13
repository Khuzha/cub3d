#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		if (((unsigned char)s1[i] > (unsigned char)s2[i]) || s2[i] == '\0')
			return (1);
		if (((unsigned char)s1[i] < (unsigned char)s2[i]) || s1[i] == '\0')
			return (-1);
		i++;
	}
	return (0);
}
