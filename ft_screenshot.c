/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screenshot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:11:46 by asfaihi           #+#    #+#             */
/*   Updated: 2021/02/22 15:22:47 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_screenshot		*ft_init_shot(t_mlx *mlx)
{
	t_screenshot	*screenshot;

	screenshot = malloc(1 * sizeof(t_screenshot));
	screenshot->width = mlx->window.scr_w;
	screenshot->height = mlx->window.scr_h;
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
	mlx->shot = ft_init_shot(mlx);
	ft_screen_meta(mlx);
	ft_putstr("Screenshot saved under the filename 'screenshot.bmp'.\n");
	ft_close_game(mlx, 0);
}

void				ft_fill_shot(t_mlx *mlx, unsigned char *buf)
{
	int x;
	int col;
	int row;

	row = mlx->shot->height;
	x = 0;
	while (--row >= 0)
	{
		col = -1;
		while (++col < mlx->shot->width)
		{
			mlx->shot->red = (mlx->img.data[x * mlx->window.scr_w +
				col] >> 16) & 0xFF;
			mlx->shot->green = (mlx->img.data[x * mlx->window.scr_w +
				col] >> 8) & 0xFF;
			mlx->shot->blue = mlx->img.data[x * mlx->window.scr_w +
				col] & 0xFF;
			buf[row * mlx->shot->width_in_bytes + col * 3 + 0] =
				mlx->shot->blue;
			buf[row * mlx->shot->width_in_bytes + col * 3 + 1] =
				mlx->shot->green;
			buf[row * mlx->shot->width_in_bytes + col * 3 + 2] = mlx->shot->red;
		}
		x++;
	}
}

void				ft_screen_meta(t_mlx *mlx)
{
	t_bitmapfile	fileheader;
	t_bitmapinfo	infoheader;
	int				fd;

	fd = open("screenshot.bmp", O_CREAT | O_RDWR, S_IRWXU);
	fileheader = (t_bitmapfile){ 0 };
	infoheader = (t_bitmapinfo){ 0 };
	ft_memcpy(&fileheader, "BM", 2);
	fileheader.file_size = 54 + mlx->shot->imagesize;
	fileheader.pixel_offset = 54;
	infoheader.header_size = 40;
	infoheader.num_planes = 1;
	infoheader.bmp_width = mlx->shot->width;
	infoheader.bmp_height = mlx->shot->height;
	infoheader.bits_per_pixel = mlx->shot->bitcount;
	infoheader.image_size = mlx->shot->imagesize;
	ft_fill_shot(mlx, mlx->shot->buf);
	write(fd, &fileheader, sizeof(fileheader));
	write(fd, &infoheader, sizeof(infoheader));
	write(fd, (char *)mlx->shot->buf, mlx->shot->imagesize);
	close(fd);
	free(mlx->shot->buf);
}
