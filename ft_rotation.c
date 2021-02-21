/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 12:26:58 by asfaihi           #+#    #+#             */
/*   Updated: 2021/02/18 11:26:37 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rotate_left(t_mlx *mlx)
{
	mlx->player.olddirx = mlx->player.dirx;
	mlx->player.dirx = (mlx->player.dirx * cos(mlx->player.rotspeed)) -
		(mlx->player.diry * sin(mlx->player.rotspeed));
	mlx->player.diry = (mlx->player.olddirx * sin(mlx->player.rotspeed)) +
		(mlx->player.diry * cos(mlx->player.rotspeed));
	mlx->player.oldplanex = mlx->player.planex;
	mlx->player.planex = (mlx->player.planex * cos(mlx->player.rotspeed)) -
		(mlx->player.planey * sin(mlx->player.rotspeed));
	mlx->player.planey = (mlx->player.oldplanex * sin(mlx->player.rotspeed))
	+ (mlx->player.planey * cos(mlx->player.rotspeed));
}

void	ft_rotation(t_mlx *mlx)
{
	if (mlx->keys.right == 1)
	{
		mlx->player.olddirx = mlx->player.dirx;
		mlx->player.dirx = (mlx->player.dirx * cos(-mlx->player.rotspeed)) -
			(mlx->player.diry * sin(-mlx->player.rotspeed));
		mlx->player.diry = (mlx->player.olddirx * sin(-mlx->player.rotspeed)) +
			(mlx->player.diry * cos(-mlx->player.rotspeed));
		mlx->player.oldplanex = mlx->player.planex;
		mlx->player.planex = (mlx->player.planex * cos(-mlx->player.rotspeed)) -
			(mlx->player.planey * sin(-mlx->player.rotspeed));
		mlx->player.planey = (mlx->player.oldplanex *
			sin(-mlx->player.rotspeed)) + (mlx->player.planey *
			cos(-mlx->player.rotspeed));
	}
	if (mlx->keys.left == 1)
		ft_rotate_left(mlx);
}
