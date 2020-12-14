#include "cub3d.h"

int		main_function(void *mlx_ptr, void *win_ptr, t_player *player)
{
	int			x;
	int			i;
	int			j;

	x = 0;
	j = -1;
	player->moveSpeed = 0.1;
	player->rotSpeed = 0.1;
/* 	while (j++ < (SCREEN_HEIGHT / 2))
	{
		i = 0;
		while (i < SCREEN_WIDTH)
			mlx_pixel_put(mlx_ptr, win_ptr, i++, j, 0x3FBDD9);
	}
	while (j++ < SCREEN_HEIGHT)
	{
		i = 0;
		while (i < SCREEN_WIDTH)
			mlx_pixel_put(mlx_ptr, win_ptr, i++, j, 0x8A3D07);
	} */
	while (x < SCREEN_WIDTH)
	{
		//calculate ray position and direction
		double	cameraX = 2 * x / (double)SCREEN_WIDTH - 1;		//x coordinate in camera screen
		double	rayDirX = player->dirX + player->planeX * cameraX;
		double	rayDirY = player->dirY + player->planeY * cameraX;

		//which box in the map we're in
		int		mapX = (int)player->posX;
		int		mapY = (int)player->posY;

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
			sideDistX = (player->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player->posY) * deltaDistY;
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
			perpWallDist = (mapX - player->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - player->posY + (1 - stepY) / 2) / rayDirY;

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
			mlx_pixel_put(mlx_ptr, win_ptr, x, pixel_y++, color);
		x++;
	}
	return (0);
}

void	ft_mover(t_player *player)
{
	if (player->t_keys.W == 1)
	{
		if (worldMap[(int)(player->posX + player->dirX * player->moveSpeed)][(int)player->posY] == 0)
			player->posX += player->dirX * player->moveSpeed;
		if (worldMap[(int)player->posX][(int)(player->posY + player->dirY * player->moveSpeed)] == 0)
			player->posY += player->dirY * player->moveSpeed;
	}
	if (player->t_keys.S == 1)
	{
		if (worldMap[(int)(player->posX - player->dirX * player->moveSpeed)][(int)player->posY] == 0)
			player->posX -= player->dirX * player->moveSpeed;
		if (worldMap[(int)player->posX][(int)(player->posY - player->dirY * player->moveSpeed)] == 0)
			player->posY -= player->dirY * player->moveSpeed;
	}
	if (player->t_keys.D == 1)
	{
		if (worldMap[(int)player->posX][(int)(player->posY - player->dirX * player->moveSpeed)] == 0)
			player->posY -= player->dirX * player->moveSpeed;
		if (worldMap[(int)(player->posX + player->dirY * player->moveSpeed)][(int)player->posY] == 0)
			player->posX += player->dirY * player->moveSpeed;
	}
	if (player->t_keys.A == 1)
	{
		if (worldMap[(int)player->posX][(int)(player->posY + player->dirX * player->moveSpeed)] == 0)
			player->posY += player->dirX * player->moveSpeed;
		if (worldMap[(int)(player->posX - player->dirY * player->moveSpeed)][(int)player->posY] == 0)
			player->posX -= player->dirY * player->moveSpeed;
	}
	if (player->t_keys.right == 1)
	{
		double oldDirX = player->dirX;
		player->dirX = (player->dirX * cos(-player->rotSpeed)) - (player->dirY * sin(-player->rotSpeed));
		player->dirY = (oldDirX * sin(-player->rotSpeed)) + (player->dirY * cos(-player->rotSpeed));
		double oldPlaneX = player->planeX;
		player->planeX = (player->planeX * cos(-player->rotSpeed)) - (player->planeY * sin(-player->rotSpeed));
		player->planeY = (oldPlaneX * sin(-player->rotSpeed)) + (player->planeY * cos(-player->rotSpeed));
	}
	if (player->t_keys.left == 1)
	{
		double oldDirX = player->dirX;
		player->dirX = (player->dirX * cos(player->rotSpeed)) - (player->dirY * sin(player->rotSpeed));
		player->dirY = (oldDirX * sin(player->rotSpeed)) + (player->dirY * cos(player->rotSpeed));
		double oldPlaneX = player->planeX;
		player->planeX = (player->planeX * cos(player->rotSpeed)) - (player->planeY * sin(player->rotSpeed));
		player->planeY = (oldPlaneX * sin(player->rotSpeed)) + (player->planeY * cos(player->rotSpeed));
	}
}

int		update(t_player *player)
{
	ft_mover(player);
	mlx_clear_window(player->mlx_ptr, player->win_ptr);
	main_function(player->mlx_ptr, player->win_ptr, player);
	return (0);
}

int		key_pressed(int key, t_player *player)
{
	if (key == 13)
		player->t_keys.W = 1;
	if (key == 1)
		player->t_keys.S = 1;
	if (key == 0)
		player->t_keys.A = 1;
	if (key == 2)
		player->t_keys.D = 1;
	if (key == 123)
		player->t_keys.left = 1;
	if (key == 124)
		player->t_keys.right = 1;
	return (0);
}

int		key_released(int key, t_player *player)
{
	if (key == 13)
		player->t_keys.W = 0;
	if (key == 1)
		player->t_keys.S = 0;
	if (key == 0)
		player->t_keys.A = 0;
	if (key == 2)
		player->t_keys.D = 0;
	if (key == 123)
		player->t_keys.left = 0;
	if (key == 124)
		player->t_keys.right = 0;
	return (0);
}

int		main()
{
	t_player	player;

	player.posX = 22;
	player.posY = 12;
	player.dirX = -1;
	player.dirY = 0;
	player.planeX = 0;
	player.planeY = 0.66;
	player.mlx_ptr = mlx_init();
	player.win_ptr = mlx_new_window(player.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	mlx_hook(player.win_ptr, 2, (1L<<0), key_pressed, &player);
	mlx_hook(player.win_ptr, 3, (1L<<1), key_released, &player);
	mlx_loop_hook(player.mlx_ptr, update, &player);
	mlx_loop(player.mlx_ptr);
	return (0);
}