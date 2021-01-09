#include "cub3d.h"

void	ft_draw_ceiling_floor(t_mlx *mlx)
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
			mlx->img.data[(y * SCREEN_WIDTH) + x] = mlx->window.ceiling_color;
			x++;
		}
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx->img.data[(y * SCREEN_WIDTH) + x] = mlx->window.floor_color;
			x++;
		}
		y++;
	}
/* 	int		y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		float rayDirX0 = mlx->player.dirX - mlx->player.planeX;
		float rayDirY0 = mlx->player.dirY - mlx->player.planeY;
		float rayDirX1 = mlx->player.dirX + mlx->player.planeX;
		float rayDirY1 = mlx->player.dirY + mlx->player.planeY;

		// Current y position compared to the center of the screen (the horizon)
		int p = y - SCREEN_HEIGHT / 2;

		// Vertical position of the camera.
		float posZ = 0.5 * SCREEN_HEIGHT;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = mlx->player.posX + rowDistance * rayDirX0;
		float floorY = mlx->player.posY + rowDistance * rayDirY0;
		int	x = 0;
		while (x < SCREEN_WIDTH)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)floorX;
			int cellY = (int)floorY;

			// get the texture coordinate from the fractional part
			int tx = (int)(TEXTURE_WIDTH * (floorX - cellX)) & (TEXTURE_WIDTH - 1);
			int ty = (int)(TEXTURE_HEIGHT * (floorY - cellY)) & (TEXTURE_HEIGHT - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			int	color = mlx->tex.texture_data[6][(TEXTURE_WIDTH * ty) + tx];
			color = (color >> 1) & 8355711; // make a bit darker
			mlx->img.data[(y * SCREEN_WIDTH) + x] = color;

			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			color = mlx->tex.texture_data[1][(TEXTURE_WIDTH * ty) + tx];
			color = (color >> 1) & 8355711; // make a bit darker
			//buffer[screenHeight - y - 1][x] = color;
			mlx->img.data[(SCREEN_HEIGHT - y - 1) * SCREEN_WIDTH + x] = color;
			x++;
		}
		y++;
	} */
}

void	ft_draw_walls(t_mlx *mlx)
{
	int			x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		//calculate ray position and direction
		double	cameraX = 2 * x / (double)SCREEN_WIDTH - 1;		//x coordinate in camera screen
		mlx->rayDirX = mlx->player.dirX + mlx->player.planeX * cameraX;
		mlx->rayDirY = mlx->player.dirY + mlx->player.planeY * cameraX;

		//which box in the map we're in
		mlx->mapX = (int)mlx->player.posX;
		mlx->mapY = (int)mlx->player.posY;

		//length of ray from current position to next or y-side
		double	sideDistX;
		double	sideDistY;
	
		//length of ray from one x or y-mlx->side to next x or y-side
		double	deltaDistX = fabs(1 / mlx->rayDirX);
		double	deltaDistY = fabs(1 / mlx->rayDirY);

		//direction to step in x and y direction (+1 or -1)
		int		stepX;
		int		stepY;

		int		hit = 0;	//was a wall hit?

		//calculate step and initial sideDist
		if (mlx->rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (mlx->player.posX - mlx->mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mlx->mapX + 1.0 - mlx->player.posX) * deltaDistX;
		}
		if (mlx->rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (mlx->player.posY - mlx->mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mlx->mapY + 1.0 - mlx->player.posY) * deltaDistY;
		}
		
		//DDA algorithm starts
		while (hit == 0)
		{
			//jump to next map square, OR in x direction, OR in y direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mlx->mapX += stepX;
				mlx->side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mlx->mapY += stepY;
				mlx->side = 1;
			}
			//checking if ray hit a wall
			if (worldMap[mlx->mapX][mlx->mapY] > 0)
				hit = 1;
		}

		//calculate distance projected on camera direction
		if (mlx->side == 0)
			mlx->perpWallDist = (mlx->mapX - mlx->player.posX + (1 - stepX) / 2) / mlx->rayDirX;
		else
			mlx->perpWallDist = (mlx->mapY - mlx->player.posY + (1 - stepY) / 2) / mlx->rayDirY;

		//calculate height of line to draw on screen
		mlx->lineHeight = (int)(SCREEN_HEIGHT / mlx->perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		mlx->drawStart = -mlx->lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (mlx->drawStart < 0)
			mlx->drawStart = 0;
		mlx->drawEnd = mlx->lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (mlx->drawEnd >= SCREEN_HEIGHT)
			mlx->drawEnd = SCREEN_HEIGHT - 1;

		ft_texture(mlx, x);
      	//SET THE ZBUFFER FOR THE SPRITE CASTING
      	ZBuffer[x] = mlx->perpWallDist; //perpendicular distance is used
		x++;
	}
	ft_sprites(mlx);
}

void	ft_texture(t_mlx *mlx, int x)
{
/* 	//texturing calculations
	int texNum = worldMap[mlx->mapX][mlx->mapY] - 1; //1 subtracted from it so that texture 0 can be used! */

	//Calculate value of wallX where exactly the wall was hit
	double	wallX;
	if (mlx->side == 0)
		wallX = mlx->player.posY + (mlx->perpWallDist * mlx->rayDirY);
	else
		wallX = mlx->player.posX + (mlx->perpWallDist * mlx->rayDirX);
	wallX -= floor((wallX));

	//x coordinate on the texture
	int		texX = (int)(wallX * (double)TEXTURE_WIDTH);
	if (mlx->side == 0 && mlx->rayDirX > 0)
		texX = TEXTURE_WIDTH - texX - 1;
	else if (mlx->side == 1 && mlx->rayDirY < 0)
		texX = TEXTURE_WIDTH - texX - 1;
	
	//How much to increase the texture coordinate per screen pixel
	double	step = (1.0 * TEXTURE_HEIGHT) / mlx->lineHeight;
	//Starting texture coordinate
	double	texPos = (mlx->drawStart - (SCREEN_HEIGHT / 2) + (mlx->lineHeight / 2)) * step;
	int		y = mlx->drawStart;
	while (y < mlx->drawEnd)
	{
		//Cast the texture coordinate to integer, and mask with (TEXTURE_HEIGHT - 1) in case of overflow
		int		texY = (int)texPos & (TEXTURE_HEIGHT - 1);
		texPos += step;
		int		color;
		if (mlx->side == 0)
			color = mlx->tex.texture_data[0][(TEXTURE_HEIGHT * texY) + texX];
		//make color darker for y-sides: R, G, and B byte each divided through two with a "shift" and an "and"
		else
			color = mlx->tex.texture_data[1][(TEXTURE_HEIGHT * texY) + texX];
/* 		if (mlx->side == 1)
			color = (color >> 1) & 8355711; */
		mlx->img.data[(y * SCREEN_WIDTH) + x] = color;
		y++;
	}
}

void	ft_sprites(t_mlx *mlx)
{
	//SPRITE CASTING
    //sort sprites from far to close
	int		i = 0;
	while (i < NUM_SPRITES)
	{
 		spriteOrder[i] = i;
    	spriteDistance[i] = ((mlx->player.posX - sprite[i].x) * (mlx->player.posX - sprite[i].x) + (mlx->player.posY - sprite[i].y) * (mlx->player.posY - sprite[i].y)); //sqrt not taken, unneeded
		i++;
	}
    //sortSprites(spriteOrder, spriteDistance, NUM_SPRITES);

	//after sorting the sprites, do the projection and draw them
	i = 0;
	while (i < NUM_SPRITES)
	{
		//translate sprite position to relative to camera
    	double spriteX = sprite[spriteOrder[i]].x - mlx->player.posX;
    	double spriteY = sprite[spriteOrder[i]].y - mlx->player.posY;

    	//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
    	// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
    	// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (mlx->player.planeX * mlx->player.dirY - mlx->player.dirX * mlx->player.planeY); //required for correct matrix multiplication

		double transformX = invDet * (mlx->player.dirY * spriteX - mlx->player.dirX * spriteY);
		double transformY = invDet * (-mlx->player.planeY * spriteX + mlx->player.planeX * spriteY); //this is actually the depth inmlx->side the screen, that what Z is in 3D

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
					int	color = mlx->tex.sp_texture_data[(TEXTURE_WIDTH * texY) + texX]; //get current color from the texture
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