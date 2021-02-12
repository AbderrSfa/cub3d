#include "cub3d.h"

t_screenshot		*ft_init_shot(t_mlx *mlx)
{
	t_screenshot	*screenshot;

	screenshot = malloc(1 * sizeof(t_screenshot));
	screenshot->width = mlx->window.screen_width;
	screenshot->height = mlx->window.screen_height;
	screenshot->bitcount = 24;
	screenshot->blue = 255;
	screenshot->green = 0;
	screenshot->red = 0;
	screenshot->width_in_bytes = ((screenshot->width *
			screenshot->bitcount + 31) / 32) * 4;
	screenshot->imagesize = screenshot->width_in_bytes * screenshot->height;
	screenshot->buf = malloc(screenshot->imagesize);
	return (screenshot);
}

void				ft_screenshot(t_mlx *mlx)
{
	if (sizeof(t_bitmapfile) != 14 && sizeof(t_bitmapinfo) != 40)
		ft_put_error("Bitmap file metadata not setup properly\n", mlx);
	mlx->screenshot = ft_init_shot(mlx);
	ft_screen_meta(mlx);
	ft_putstr("Screenshot has been saved under the filename 'screenshot.bmp'.\n");
	ft_close_game(mlx, 0);
}

void				ft_fill_shot(t_mlx *mlx, unsigned char *buf)
{
	int x;
	int col;
	int row;

	row = mlx->screenshot->height;
	x = 0;
	while (--row >= 0)
	{
		col = -1;
		while (++col < mlx->screenshot->width)
		{
			mlx->screenshot->red = (mlx->img.data[x * mlx->window.screen_width + col] >> 16) & 0xFF;
			mlx->screenshot->green = (mlx->img.data[x * mlx->window.screen_width + col] >> 8) & 0xFF;
			mlx->screenshot->blue = mlx->img.data[x * mlx->window.screen_width + col] & 0xFF;
			buf[row * mlx->screenshot->width_in_bytes + col * 3 + 0] = mlx->screenshot->blue;
			buf[row * mlx->screenshot->width_in_bytes + col * 3 + 1] = mlx->screenshot->green;
			buf[row * mlx->screenshot->width_in_bytes + col * 3 + 2] = mlx->screenshot->red;
		}
		x++;
	}
}

void				ft_screen_meta(t_mlx *mlx)
{
	FILE			*image;
	t_bitmapfile	fileheader;
	t_bitmapinfo	infoheader;
	int				fd;

	fd = open("screenshot.bmp", O_CREAT | O_RDWR, S_IRWXU);

	fileheader = (t_bitmapfile){ 0 };
	infoheader = (t_bitmapinfo){ 0 };
	ft_memcpy(&fileheader, "BM", 2);
	fileheader.file_size = 54 + mlx->screenshot->imagesize;
	fileheader.pixel_offset = 54;
	infoheader.header_size = 40;
	infoheader.num_planes = 1;
	infoheader.bmp_width = mlx->screenshot->width;
	infoheader.bmp_height = mlx->screenshot->height;
	infoheader.bits_per_pixel = mlx->screenshot->bitcount;
	infoheader.image_size = mlx->screenshot->imagesize;
	ft_fill_shot(mlx, mlx->screenshot->buf);
	write(fd, &fileheader, sizeof(fileheader));
	write(fd, &infoheader, sizeof(infoheader));
	write(fd, (char *)mlx->screenshot->buf, mlx->screenshot->imagesize);
	close(fd);
	free(mlx->screenshot->buf);
}