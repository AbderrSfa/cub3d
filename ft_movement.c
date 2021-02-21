/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:25:37 by asfaihi           #+#    #+#             */
/*   Updated: 2021/02/18 11:28:18 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_movement(int x, int y, t_mlx *mlx)
{
	if (mlx->world_map[x][y] != '1' && mlx->world_map[x][y] != '2')
		return (1);
	return (0);
}

void	ft_move_left_right(t_mlx *mlx)
{
	if (mlx->keys.d == 1)
	{
		if (check_movement((int)mlx->player.posx, (int)(mlx->player.posy -
			mlx->player.dirx * mlx->player.movespeed), mlx))
			mlx->player.posy -= mlx->player.dirx * mlx->player.movespeed * 0.5;
		if (check_movement((int)(mlx->player.posx + mlx->player.diry *
			mlx->player.movespeed), (int)mlx->player.posy, mlx))
			mlx->player.posx += mlx->player.diry * mlx->player.movespeed * 0.5;
	}
	if (mlx->keys.a == 1)
	{
		if (check_movement((int)mlx->player.posx, (int)(mlx->player.posy +
			mlx->player.dirx * mlx->player.movespeed), mlx))
			mlx->player.posy += mlx->player.dirx * mlx->player.movespeed * 0.5;
		if (check_movement((int)(mlx->player.posx - mlx->player.diry *
			mlx->player.movespeed), (int)mlx->player.posy, mlx))
			mlx->player.posx -= mlx->player.diry * mlx->player.movespeed * 0.5;
	}
	//strafe to the right and left like in Lodev
/* 	if (mlx->keys.d == 1)
	{
		if (check_movement((int)(mlx->player.posx + mlx->player.planeX *
			mlx->player.movespeed), (int)mlx->player.posy, mlx))
			mlx->player.posx += mlx->player.planeX * mlx->player.moveSpd * 0.5;
		if (check_movement((int)mlx->player.posx, (int)(mlx->player.posy +
			mlx->player.planeY * mlx->player.movespeed), mlx))
			mlx->player.posy += mlx->player.planeY * mlx->player.moveSpd * 0.5;
	}
	if (mlx->keys.a == 1)
	{
		if (check_movement((int)(mlx->player.posx - mlx->player.planeX *
			mlx->player.movespeed), (int)mlx->player.posy, mlx))
			mlx->player.posx -= mlx->player.planeX * mlx->player.moveSpd * 0.5;
		if (check_movement((int)mlx->player.posx, (int)(mlx->player.posy -
			mlx->player.planeY * mlx->player.movespeed), mlx))
			mlx->player.posy -= mlx->player.planeY * mlx->player.moveSpd * 0.5;
	} */
}

void	ft_movement(t_mlx *mlx)
{
	if (mlx->keys.w == 1)
	{
		if (check_movement((int)(mlx->player.posx + mlx->player.dirx *
			mlx->player.movespeed), (int)mlx->player.posy, mlx))
			mlx->player.posx += mlx->player.dirx * mlx->player.movespeed * 0.5;
		if (check_movement((int)mlx->player.posx, (int)(mlx->player.posy +
			mlx->player.diry * mlx->player.movespeed), mlx))
			mlx->player.posy += mlx->player.diry * mlx->player.movespeed * 0.5;
	}
	if (mlx->keys.s == 1)
	{
		if (check_movement((int)(mlx->player.posx - mlx->player.dirx *
			mlx->player.movespeed), (int)mlx->player.posy, mlx))
			mlx->player.posx -= mlx->player.dirx * mlx->player.movespeed * 0.5;
		if (check_movement((int)mlx->player.posx, (int)(mlx->player.posy -
			mlx->player.diry * mlx->player.movespeed), mlx))
			mlx->player.posy -= mlx->player.diry * mlx->player.movespeed * 0.5;
	}
	if (mlx->keys.d == 1 || mlx->keys.a == 1)
		ft_move_left_right(mlx);
	if (mlx->keys.right == 1 || mlx->keys.left == 1)
		ft_rotation(mlx);
}

int		ft_key_pressed(int key, t_mlx *mlx)
{
	if (key == 13)
		mlx->keys.w = 1;
	if (key == 1)
		mlx->keys.s = 1;
	if (key == 0)
		mlx->keys.a = 1;
	if (key == 2)
		mlx->keys.d = 1;
	if (key == 123)
		mlx->keys.left = 1;
	if (key == 124)
		mlx->keys.right = 1;
	return (0);
}

int		ft_key_released(int key, t_mlx *mlx)
{
	if (key == 13)
		mlx->keys.w = 0;
	if (key == 1)
		mlx->keys.s = 0;
	if (key == 0)
		mlx->keys.a = 0;
	if (key == 2)
		mlx->keys.d = 0;
	if (key == 123)
		mlx->keys.left = 0;
	if (key == 124)
		mlx->keys.right = 0;
	if (key == 53)
		ft_close_game(mlx, 0);
	return (0);
}
