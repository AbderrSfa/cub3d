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
			mlx->img.data[(y * SCREEN_WIDTH) + x] = 0x1A1A1A;
			x++;
		}
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx->img.data[(y * SCREEN_WIDTH) + x] = 0x555555;
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

		//texturing calculations
      	int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

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
		else if (side == 1 && rayDirY < 0)
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
			int		color = mlx->tex.texture_data[texNum][(TEXTURE_HEIGHT * texY) + texX];
			//make color darker for y-sides: R, G, and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			mlx->img.data[(y * SCREEN_WIDTH) + x] = color;
			y++;
		}
      	//SET THE ZBUFFER FOR THE SPRITE CASTING
      	ZBuffer[x] = perpWallDist; //perpendicular distance is used
		x++;
	}
	ft_sprites(mlx);
}

void	ft_sprites(t_mlx *mlx)
{
//SPRITE CASTING
    //sort sprites from far to close
	int		i = 0;
	while (i < NUM_SPRITES)
	{
 		spriteOrder[i] = i;
    	spriteDistance[i] = ((mlx->posX - sprite[i].x) * (mlx->posX - sprite[i].x) + (mlx->posY - sprite[i].y) * (mlx->posY - sprite[i].y)); //sqrt not taken, unneeded
		i++;
	}
    //sortSprites(spriteOrder, spriteDistance, NUM_SPRITES);

	//after sorting the sprites, do the projection and draw them
	i = 0;
	while (i < NUM_SPRITES)
	{
		//translate sprite position to relative to camera
    	double spriteX = sprite[spriteOrder[i]].x - mlx->posX;
    	double spriteY = sprite[spriteOrder[i]].y - mlx->posY;

    	//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
    	// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
    	// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (mlx->planeX * mlx->dirY - mlx->dirX * mlx->planeY); //required for correct matrix multiplication

		double transformX = invDet * (mlx->dirY * spriteX - mlx->dirX * spriteY);
		double transformY = invDet * (-mlx->planeY * spriteX + mlx->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)(SCREEN_WIDTH / 2) * (1 + transformX / transformY);

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(SCREEN_HEIGHT / (transformY))); //using 'transformY' instead of the real distance prevents fisheye

		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + SCREEN_HEIGHT / 2;
		if(drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + SCREEN_HEIGHT / 2;
		if(drawEndY >= SCREEN_HEIGHT)
			drawEndY = SCREEN_HEIGHT - 1;

		//calculate width of the sprite
		int spriteWidth = abs((int)(SCREEN_HEIGHT / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= SCREEN_WIDTH)
			drawEndX = SCREEN_WIDTH - 1;
		
      	//loop through every vertical stripe of the sprite on screen
		int	stripe = drawStartX;
		while (stripe < drawEndX)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEXTURE_WIDTH / spriteWidth) / 256;
        	//the conditions in the if are:
        	//1) it's in front of camera plane so you don't see things behind you
        	//2) it's on the screen (left)
        	//3) it's on the screen (right)
        	//4) ZBuffer, with perpendicular distance
        	if(transformY > 0 && stripe > 0 && stripe < SCREEN_WIDTH && transformY < ZBuffer[stripe])
			{
				int	y = drawStartY;
				while (y < drawEndY)
				{
			        int d = (y) * 256 - SCREEN_HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
        			int texY = ((d * TEXTURE_HEIGHT) / spriteHeight) / 256;
					int	color = mlx->tex.texture_data[8][(TEXTURE_WIDTH * texY) + texX]; //get current color from the texture
					if (color != 0) //paint pixel if it isn't black, black is the invisible color
						mlx->img.data[(y * SCREEN_WIDTH) + stripe] = color;					
					y++;
				}
			}
			stripe++;
		}
		i++;
	}
}