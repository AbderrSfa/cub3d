#include "cub3d.h"

int		ft_draw(void *mlx_ptr, void *win_ptr, t_mlx *mlx)
{
	int			x;
	int			i;

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
		
		//set wall color
		int	color;
		if (worldMap[mapX][mapY] == 1)
				color = 0xCC0044;
		else if (worldMap[mapX][mapY] == 2)
				color = 0x3B8E85;
		else if (worldMap[mapX][mapY] == 3)
				color = 0x05289D;
		else if (worldMap[mapX][mapY] == 4)
				color = 0xA3A3A3;
		else
				color = 0xFFDE5C;
		//x and y sides have different brightness
		if (side == 1)
			color = color / 2;
		
		//draw the pixels as a vertical line
		int	pixel_y = drawStart;
		while (pixel_y < drawEnd)
		{
			mlx->img.data[(pixel_y * SCREEN_WIDTH) + x] = color;
			pixel_y++;
		}
		x++;
	}
	return (0);
}