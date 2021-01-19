#include "cub3d.h"

void	ft_movement(t_mlx *mlx)
{
	if (mlx->keys.W == 1)
	{
		if (worldMap[(int)(mlx->player.posX + mlx->player.dirX * mlx->player.moveSpeed)][(int)mlx->player.posY] == 0)
			mlx->player.posX += mlx->player.dirX * mlx->player.moveSpeed * 0.5;
		if (worldMap[(int)mlx->player.posX][(int)(mlx->player.posY + mlx->player.dirY * mlx->player.moveSpeed)] == 0)
			mlx->player.posY += mlx->player.dirY * mlx->player.moveSpeed * 0.5;
	}
	if (mlx->keys.S == 1)
	{
		if (worldMap[(int)(mlx->player.posX - mlx->player.dirX * mlx->player.moveSpeed)][(int)mlx->player.posY] == 0)
			mlx->player.posX -= mlx->player.dirX * mlx->player.moveSpeed * 0.5;
		if (worldMap[(int)mlx->player.posX][(int)(mlx->player.posY - mlx->player.dirY * mlx->player.moveSpeed)] == 0)
			mlx->player.posY -= mlx->player.dirY * mlx->player.moveSpeed * 0.5;
	}
	if (mlx->keys.D == 1)
	{
		if (worldMap[(int)mlx->player.posX][(int)(mlx->player.posY - mlx->player.dirX * mlx->player.moveSpeed)] == 0)
			mlx->player.posY -= mlx->player.dirX * mlx->player.moveSpeed * 0.5;
		if (worldMap[(int)(mlx->player.posX + mlx->player.dirY * mlx->player.moveSpeed)][(int)mlx->player.posY] == 0)
			mlx->player.posX += mlx->player.dirY * mlx->player.moveSpeed * 0.5;
	}
	if (mlx->keys.A == 1)
	{
		if (worldMap[(int)mlx->player.posX][(int)(mlx->player.posY + mlx->player.dirX * mlx->player.moveSpeed)] == 0)
			mlx->player.posY += mlx->player.dirX * mlx->player.moveSpeed * 0.5;
		if (worldMap[(int)(mlx->player.posX - mlx->player.dirY * mlx->player.moveSpeed)][(int)mlx->player.posY] == 0)
			mlx->player.posX -= mlx->player.dirY * mlx->player.moveSpeed * 0.5;
	}
	//strafe to the right and left like in Lodev
/* 	if (mlx->keys.D == 1)
	{
		if (worldMap[(int)(mlx->player.posX + mlx->player.planeX * mlx->player.moveSpeed)][(int)mlx->player.posY] == 0)
			mlx->player.posX += mlx->player.planeX * mlx->player.moveSpeed * 0.5;
		if (worldMap[(int)mlx->player.posX][(int)(mlx->player.posY + mlx->player.planeY * mlx->player.moveSpeed)] == 0)
			mlx->player.posY += mlx->player.planeY * mlx->player.moveSpeed * 0.5;
	}
	if (mlx->keys.A == 1)
	{
		if (worldMap[(int)(mlx->player.posX - mlx->player.planeX * mlx->player.moveSpeed)][(int)mlx->player.posY] == 0)
			mlx->player.posX -= mlx->player.planeX * mlx->player.moveSpeed * 0.5;
		if (worldMap[(int)mlx->player.posX][(int)(mlx->player.posY - mlx->player.planeY * mlx->player.moveSpeed)] == 0)
			mlx->player.posY -= mlx->player.planeY * mlx->player.moveSpeed * 0.5;
	} */
	if (mlx->keys.right == 1 || mlx->keys.left == 1)
		ft_rotation(mlx);
}

void	ft_rotation(t_mlx *mlx)
{
	if (mlx->keys.right == 1)
	{
		double oldDirX = mlx->player.dirX;
		mlx->player.dirX = (mlx->player.dirX * cos(-mlx->player.rotSpeed)) - (mlx->player.dirY * sin(-mlx->player.rotSpeed));
		mlx->player.dirY = (oldDirX * sin(-mlx->player.rotSpeed)) + (mlx->player.dirY * cos(-mlx->player.rotSpeed));
		double oldPlaneX = mlx->player.planeX;
		mlx->player.planeX = (mlx->player.planeX * cos(-mlx->player.rotSpeed)) - (mlx->player.planeY * sin(-mlx->player.rotSpeed));
		mlx->player.planeY = (oldPlaneX * sin(-mlx->player.rotSpeed)) + (mlx->player.planeY * cos(-mlx->player.rotSpeed));
	}
	if (mlx->keys.left == 1)
	{
		double oldDirX = mlx->player.dirX;
		mlx->player.dirX = (mlx->player.dirX * cos(mlx->player.rotSpeed)) - (mlx->player.dirY * sin(mlx->player.rotSpeed));
		mlx->player.dirY = (oldDirX * sin(mlx->player.rotSpeed)) + (mlx->player.dirY * cos(mlx->player.rotSpeed));
		double oldPlaneX = mlx->player.planeX;
		mlx->player.planeX = (mlx->player.planeX * cos(mlx->player.rotSpeed)) - (mlx->player.planeY * sin(mlx->player.rotSpeed));
		mlx->player.planeY = (oldPlaneX * sin(mlx->player.rotSpeed)) + (mlx->player.planeY * cos(mlx->player.rotSpeed));
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
	if (key == 53)
		ft_close_game(mlx);
	return (0);
}