#include "cub3d.h"

void	ft_movement(t_mlx *mlx)
{
	if (mlx->keys.W == 1)
	{
		if (worldMap[(int)(mlx->posX + mlx->dirX * mlx->moveSpeed)][(int)mlx->posY] == 0)
			mlx->posX += mlx->dirX * mlx->moveSpeed * 0.5;
		if (worldMap[(int)mlx->posX][(int)(mlx->posY + mlx->dirY * mlx->moveSpeed)] == 0)
			mlx->posY += mlx->dirY * mlx->moveSpeed * 0.5;
	}
	if (mlx->keys.S == 1)
	{
		if (worldMap[(int)(mlx->posX - mlx->dirX * mlx->moveSpeed)][(int)mlx->posY] == 0)
			mlx->posX -= mlx->dirX * mlx->moveSpeed * 0.5;
		if (worldMap[(int)mlx->posX][(int)(mlx->posY - mlx->dirY * mlx->moveSpeed)] == 0)
			mlx->posY -= mlx->dirY * mlx->moveSpeed * 0.5;
	}
	if (mlx->keys.D == 1)
	{
		if (worldMap[(int)mlx->posX][(int)(mlx->posY - mlx->dirX * mlx->moveSpeed)] == 0)
			mlx->posY -= mlx->dirX * mlx->moveSpeed * 0.5;
		if (worldMap[(int)(mlx->posX + mlx->dirY * mlx->moveSpeed)][(int)mlx->posY] == 0)
			mlx->posX += mlx->dirY * mlx->moveSpeed * 0.5;
	}
	if (mlx->keys.A == 1)
	{
		if (worldMap[(int)mlx->posX][(int)(mlx->posY + mlx->dirX * mlx->moveSpeed)] == 0)
			mlx->posY += mlx->dirX * mlx->moveSpeed * 0.5;
		if (worldMap[(int)(mlx->posX - mlx->dirY * mlx->moveSpeed)][(int)mlx->posY] == 0)
			mlx->posX -= mlx->dirY * mlx->moveSpeed * 0.5;
	}
	//strafe to the right and left like in Lodev
/* 	if (mlx->keys.D == 1)
	{
		if (worldMap[(int)(mlx->posX + mlx->planeX * mlx->moveSpeed)][(int)mlx->posY] == 0)
			mlx->posX += mlx->planeX * mlx->moveSpeed * 0.5;
		if (worldMap[(int)mlx->posX][(int)(mlx->posY + mlx->planeY * mlx->moveSpeed)] == 0)
			mlx->posY += mlx->planeY * mlx->moveSpeed * 0.5;
	}
	if (mlx->keys.A == 1)
	{
		if (worldMap[(int)(mlx->posX - mlx->planeX * mlx->moveSpeed)][(int)mlx->posY] == 0)
			mlx->posX -= mlx->planeX * mlx->moveSpeed * 0.5;
		if (worldMap[(int)mlx->posX][(int)(mlx->posY - mlx->planeY * mlx->moveSpeed)] == 0)
			mlx->posY -= mlx->planeY * mlx->moveSpeed * 0.5;
	} */
	if (mlx->keys.right == 1 || mlx->keys.left)
		ft_rotation(mlx);
}

void	ft_rotation(t_mlx *mlx)
{
	if (mlx->keys.right == 1)
	{
		double oldDirX = mlx->dirX;
		mlx->dirX = (mlx->dirX * cos(-mlx->rotSpeed)) - (mlx->dirY * sin(-mlx->rotSpeed));
		mlx->dirY = (oldDirX * sin(-mlx->rotSpeed)) + (mlx->dirY * cos(-mlx->rotSpeed));
		double oldPlaneX = mlx->planeX;
		mlx->planeX = (mlx->planeX * cos(-mlx->rotSpeed)) - (mlx->planeY * sin(-mlx->rotSpeed));
		mlx->planeY = (oldPlaneX * sin(-mlx->rotSpeed)) + (mlx->planeY * cos(-mlx->rotSpeed));
	}
	if (mlx->keys.left == 1)
	{
		double oldDirX = mlx->dirX;
		mlx->dirX = (mlx->dirX * cos(mlx->rotSpeed)) - (mlx->dirY * sin(mlx->rotSpeed));
		mlx->dirY = (oldDirX * sin(mlx->rotSpeed)) + (mlx->dirY * cos(mlx->rotSpeed));
		double oldPlaneX = mlx->planeX;
		mlx->planeX = (mlx->planeX * cos(mlx->rotSpeed)) - (mlx->planeY * sin(mlx->rotSpeed));
		mlx->planeY = (oldPlaneX * sin(mlx->rotSpeed)) + (mlx->planeY * cos(mlx->rotSpeed));
	}
}

int		ft_key_pressed(int key, t_mlx *mlx)
{
	if (key == 13)
		mlx->keys.W = 1;
	if (key == 1)
		mlx->keys.S = 1;
	if (key == 0)
		mlx->keys.A = 1;
	if (key == 2)
		mlx->keys.D = 1;
	if (key == 123)
		mlx->keys.left = 1;
	if (key == 124)
		mlx->keys.right = 1;
	return (0);
}

int		ft_key_released(int key, t_mlx *mlx)
{
	if (key == 13)
		mlx->keys.W = 0;
	if (key == 1)
		mlx->keys.S = 0;
	if (key == 0)
		mlx->keys.A = 0;
	if (key == 2)
		mlx->keys.D = 0;
	if (key == 123)
		mlx->keys.left = 0;
	if (key == 124)
		mlx->keys.right = 0;
	ft_putchar('-');
	ft_putnbr(key);
	ft_putchar('-');
	return (0);
}