#include "../../cub.h"

void	fill_header_1(t_rc *rc, int fd)
{
	unsigned char	header[14];
	size_t			size;

	ft_bzero(header, 14);
	size = 54 + (rc->img.bpp / 8 * rc->data->res.y * rc->data->res.x);
	header[0] = 'B';
	header[1] = 'M';
	header[2] = (unsigned char)(size % 256);
	header[3] = (unsigned char)(size / 256 % 256);
	header[4] = (unsigned char)(size / 256 / 256 % 256);
	header[5] = (unsigned char)(size / 256 / 256 / 256);
	header[10] = 54;
	write(fd, header, 14);
}

void	fill_header_2(t_rc *rc, int fd)
{
	unsigned char	header[40];

	ft_bzero(header, 40);
	header[0] = 40;
	header[4] = (unsigned char)(rc->data->res.x % 256);
	header[5] = (unsigned char)(rc->data->res.x / 256 % 256);
	header[6] = (unsigned char)(rc->data->res.x / 256 / 256 % 256);
	header[7] = (unsigned char)(rc->data->res.x / 256 / 256 / 256);
	header[8] = (unsigned char)(rc->data->res.y % 256);
	header[9] = (unsigned char)(rc->data->res.y / 256 % 256);
	header[10] = (unsigned char)(rc->data->res.y / 256 / 256 % 256);
	header[11] = (unsigned char)(rc->data->res.y / 256 / 256 / 256);
	header[12] = 1;
	header[14] = 32;
	write(fd, header, 40);
}

void	fill_header(t_rc *rc, int fd)
{
	fill_header_1(rc, fd);
	fill_header_2(rc, fd);
}

void	fill_image(t_rc *rc, int fd)
{
	int	i;
	int	size;

	i = rc->data->res.y;
	size = rc->data->res.x * rc->img.bpp / 8;
	while (i >= 0)
	{
		write(fd, (unsigned char *)(rc->img.addr + i * rc->img.length), size);
		i--;
	}
	error("Screenshot is created.");
}

void	make_scrsht(t_rc *rc)
{
	int	fd;

	fd = open("scrnsht.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0655);
	fill_header(rc, fd);
	fill_image(rc, fd);
}
