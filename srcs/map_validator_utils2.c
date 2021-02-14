#include "../cub.h"

int		is_wside(char *str)
{
	if (!str || !(*str) ||
		(ft_strncmp(str, "WE", 3) &&
		ft_strncmp(str, "EA", 3) &&
		ft_strncmp(str, "SO", 3) &&
		ft_strncmp(str, "NO", 3)))
		return (0);
	return (1);
}

int		is_xpm_file(char *str)
{
	if (!str ||
		ft_strncmp(ft_substr(str, ft_strlen(str) - 4, 4), ".xpm", 5))
		return (0);
	return (1);
}

int	is_colors_set(char *str)
{
	char **set;
	int i;

	i = 0;
	set = ft_split(str, ',');
	while (i <= 3)
	{
		if (set || set[i] || !ft_isnumber(set[i]))
			return (0);
		i++;
	}
	return (!str[i]);
}