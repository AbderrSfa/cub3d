/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:54:54 by asfaihi           #+#    #+#             */
/*   Updated: 2021/02/21 13:02:01 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_ceiling_floor(t_mlx *mlx)
{
	int		x;
	int		y;

	y = -1;
	while (++y < (mlx->window.scr_h / 2))
	{
		x = 0;
		while (x < mlx->window.scr_w)
		{
			mlx->img.data[(y * mlx->window.scr_w) + x] =
				mlx->window.ceiling_color;
			x++;
		}
	}
	while (y < mlx->window.scr_h)
	{
		x = 0;
		while (x < mlx->window.scr_w)
		{
			mlx->img.data[(y * mlx->window.scr_w) + x] =
				mlx->window.floor_color;
			x++;
		}
		y++;
	}
}

void	ray_step_dir(t_mlx *mlx)
{
	if (mlx->raydirx < 0)
	{
		mlx->ray.stepx = -1;
		mlx->ray.sidedistx = (mlx->player.posx - mlx->mapx) *
			mlx->ray.deltadistx;
	}
	else
	{
		mlx->ray.stepx = 1;
		mlx->ray.sidedistx = (mlx->mapx + 1.0 - mlx->player.posx) *
			mlx->ray.deltadistx;
	}
	if (mlx->raydiry < 0)
	{
		mlx->ray.stepy = -1;
		mlx->ray.sidedisty = (mlx->player.posy - mlx->mapy) *
			mlx->ray.deltadisty;
	}
	else
	{
		mlx->ray.stepy = 1;
		mlx->ray.sidedisty = (mlx->mapy + 1.0 - mlx->player.posy) *
			mlx->ray.deltadisty;
	}
}

void	cal_wall_distance(t_mlx *mlx)
{
	mlx->ray.hit = 0;
	while (mlx->ray.hit == 0)
	{
		if (mlx->ray.sidedistx < mlx->ray.sidedisty)
		{
			mlx->ray.sidedistx += mlx->ray.deltadistx;
			mlx->mapx += mlx->ray.stepx;
			mlx->side = 0;
		}
		else
		{
			mlx->ray.sidedisty += mlx->ray.deltadisty;
			mlx->mapy += mlx->ray.stepy;
			mlx->side = 1;
		}
		if (mlx->world_map[mlx->mapx][mlx->mapy] == '1')
			mlx->ray.hit = 1;
	}
	if (mlx->side == 0)
		mlx->perpwalldist = (mlx->mapx - mlx->player.posx +
			(1 - mlx->ray.stepx) / 2) / mlx->raydirx;
	else
		mlx->perpwalldist = (mlx->mapy - mlx->player.posy +
			(1 - mlx->ray.stepy) / 2) / mlx->raydiry;
}

void	ft_draw_walls(t_mlx *mlx)
{
	int			x;

	x = -1;
	while (++x < mlx->window.scr_w)
	{
		mlx->ray.camerax = 2 * x / (double)mlx->window.scr_w - 1;
		mlx->raydirx = mlx->player.dirx + mlx->player.planex * mlx->ray.camerax;
		mlx->raydiry = mlx->player.diry + mlx->player.planey * mlx->ray.camerax;
		mlx->mapx = (int)mlx->player.posx;
		mlx->mapy = (int)mlx->player.posy;
		mlx->ray.deltadistx = fabs(1 / mlx->raydirx);
		mlx->ray.deltadisty = fabs(1 / mlx->raydiry);
		ray_step_dir(mlx);
		cal_wall_distance(mlx);
		mlx->lineheight = (int)(mlx->window.scr_h / mlx->perpwalldist);
		mlx->drawstart = -mlx->lineheight / 2 + mlx->window.scr_h / 2;
		if (mlx->drawstart < 0)
			mlx->drawstart = 0;
		mlx->drawend = mlx->lineheight / 2 + mlx->window.scr_h / 2;
		if (mlx->drawend >= mlx->window.scr_h)
			mlx->drawend = mlx->window.scr_h - 1;
		ft_texture(mlx, x);
		mlx->zbuffer[x] = mlx->perpwalldist;
	}
	ft_sprites(mlx);
}
