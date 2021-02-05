#include "get_next_line.h"

int	fill_line(int fd, char **line, char **rem, int reached_eol)
{
	char	buf[BUFFER_SIZE + 1];
	char	*eol_ptr;
	char	*backup;
	size_t	read_count;

	while (!reached_eol && (read_count = read(fd, buf, BUFFER_SIZE)))
	{
		buf[read_count] = '\0';
		if ((eol_ptr = ft_strchr(buf, '\n')))
		{
			reached_eol = 1;
			*eol_ptr = '\0';
			free(*rem);
			*rem = ft_strdup(++eol_ptr);
		}
		backup = *line;
		*line = ft_strjoin(*line, buf);
		free(backup);
	}
	return (reached_eol);
}

int	prepare_rem(char **rem, char **line)
{
	char	*eol_ptr;
	char	*backup;

	eol_ptr = NULL;
	if (*rem)
	{
		if ((eol_ptr = ft_strchr(*rem, '\n')))
		{
			*eol_ptr = '\0';
			*line = ft_strdup(*rem);
			backup = *rem;
			*rem = ft_strdup(++eol_ptr);
			free(backup);
		}
		else
		{
			*line = ft_strdup(*rem);
			free(*rem);
			*rem = NULL;
		}
	}
	return (eol_ptr ? 1 : 0);
}

int	get_next_line(int fd, char **line)
{
	static char	*rem;
	int			reached_eol;
	int			res;

	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, "", 0) < 0 || !line)
		return (-1);
	*line = NULL;
	if (!rem)
		rem = ft_strdup("");
	reached_eol = prepare_rem(&rem, line);
	res = fill_line(fd, line, &rem, reached_eol);
	if (!*line)
		*line = ft_strdup("");
	return (res);
}
