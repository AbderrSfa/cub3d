/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:42:03 by asfaihi           #+#    #+#             */
/*   Updated: 2021/02/22 11:03:51 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_camera_ew(char spot, t_mlx *mlx)
{
	if (spot == 'W')
	{
		mlx->player.dirx = 0;
		mlx->player.diry = -1;
		mlx->player.planex = -0.66;
		mlx->player.planey = 0;
	}
	else if (spot == 'E')
	{
		mlx->player.dirx = 0;
		mlx->player.diry = 1;
		mlx->player.planex = 0.66;
		mlx->player.planey = 0;
	}
}

void	set_camera_ns(char dir, t_mlx *mlx)
{
	if (dir == 'N')
	{
		mlx->player.dirx = -1;
		mlx->player.diry = 0;
		mlx->player.planex = 0;
		mlx->player.planey = 0.66;
	}
	else if (dir == 'S')
	{
		mlx->player.dirx = 1;
		mlx->player.diry = 0;
		mlx->player.planex = 0;
		mlx->player.planey = -0.66;
	}
}

void	get_player_details(char spot, int x, int y, t_mlx *mlx)
{
	if (mlx->status.player_done == 1)
		ft_put_error("Multiple spawnpoints!", mlx);
	if (spot != 'N' && spot != 'S' && spot != 'W' && spot != 'E')
		ft_put_error("Invalid map character!", mlx);
	mlx->player.posx = x + 0.5;
	mlx->player.posy = y + 0.5;
	if (spot == 'N' || spot == 'S')
		set_camera_ns(spot, mlx);
	else
		set_camera_ew(spot, mlx);
}

int		check_for_player(int x, int y, t_mlx *mlx)
{
	char	spot;

	spot = mlx->world_map[x][y];
	if (spot != '0' && spot != '1' && spot != '2' && spot != 'x')
	{
		get_player_details(spot, x, y, mlx);
		return (1);
	}
	return (0);
}

void	player_position(t_mlx *mlx)
{
	int		i;
	int		j;

	i = 0;
	mlx->status.player_done = 0;
	while (i <= mlx->map_width)
	{
		j = 0;
		while (j <= mlx->map_height)
		{
			if (check_for_player(i, j, mlx))
				mlx->status.player_done = 1;
			j++;
		}
		i++;
	}
	if (mlx->status.player_done == 0)
		ft_put_error("No player spawnpoint!", mlx);
}
