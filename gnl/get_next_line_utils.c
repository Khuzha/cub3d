#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (*s == c ? (char *)s : NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;

	i = 0;
	if (!s2)
		return (NULL);
	if (!(res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		res[i] = *s2;
		s2++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strdup(const char *s1)
{
	char	*res;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	if (!(res = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
