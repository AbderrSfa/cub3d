#include "cub3d.h"

void	ft_draw_sky_floor(t_mlx *mlx)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < (SCREEN_HEIGHT / 2))
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx->img.data[(y * SCREEN_WIDTH) + x] = 0x44C9D4;
			x++;
		}
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx->img.data[(y * SCREEN_WIDTH) + x] = 0x985A0C;
			x++;
		}
		y++;
	}
}

void	ft_draw_walls(t_mlx *mlx)
{
	int			x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		//calculate ray position and direction
		double	cameraX = 2 * x / (double)SCREEN_WIDTH - 1;		//x coordinate in camera screen
		double	rayDirX = mlx->dirX + mlx->planeX * cameraX;
		double	rayDirY = mlx->dirY + mlx->planeY * cameraX;

		//which box in the map we're in
		int		mapX = (int)mlx->posX;
		int		mapY = (int)mlx->posY;

		//length of ray from current position to next or y-side
		double	sideDistX;
		double	sideDistY;
	
		//length of ray from one x or y-side to next x or y-side
		double	deltaDistX = fabs(1 / rayDirX);
		double	deltaDistY = fabs(1 / rayDirY);
		double	perpWallDist;

		//direction to step in x and y direction (+1 or -1)
		int		stepX;
		int		stepY;

		int		hit = 0;	//was a wall hit?
		int		side;		//was it a NS or a EW wall hit;

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (mlx->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - mlx->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (mlx->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - mlx->posY) * deltaDistY;
		}
		
		//DDA algorithm starts
		while (hit == 0)
		{
			//jump to next map square, OR in x direction, OR in y direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//checking if ray hit a wall
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}

		//calculate distance projected on camera direction
		if (side == 0)
			perpWallDist = (mapX - mlx->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - mlx->posY + (1 - stepY) / 2) / rayDirY;

		//calculate height of line to draw on screen
		int	lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int	drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int	drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;

		//Calculate value of wallX where exactly the wall was hit
		double	wallX;
		if (side == 0)
			wallX = mlx->posY + (perpWallDist * rayDirY);
		else
			wallX = mlx->posX + (perpWallDist * rayDirX);
		wallX -= floor((wallX));

		//x coordinate on the texture
		int		texX = (int)(wallX * (double)TEXTURE_WIDTH);
		if (side == 0 && rayDirX > 0)
			texX = TEXTURE_WIDTH - texX - 1;
		if (side == 0 && rayDirY < 0)
			texX = TEXTURE_WIDTH - texX - 1;
		
		//How much to increase the texture coordinate per screen pixel
		double	step = (1.0 * TEXTURE_HEIGHT) / lineHeight;
		//Starting texture coordinate
		double	texPos = (drawStart - (SCREEN_HEIGHT / 2) + (lineHeight / 2)) * step;
		int		y = drawStart;
		while (y < drawEnd)
		{
			//Cast the texture coordinate to integer, and mask with (TEXTURE_HEIGHT - 1) in case of overflow
			int		texY = (int)texPos & (TEXTURE_HEIGHT - 1);
			texPos += step;
			int		color = mlx->img.load_data[(TEXTURE_HEIGHT * texY) + texX];
			//make color darker for y-sides: R, G, and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			mlx->img.data[(y * SCREEN_WIDTH) + x] = color;
			y++;
		}
		x++;
	}
}