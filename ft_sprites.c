/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:53:31 by asfaihi           #+#    #+#             */
/*   Updated: 2021/02/22 12:37:37 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_sort_sprites(t_mlx *mlx)
{
	double	distance[mlx->sprite_num];
	int		tmp;
	int		disttmp;
	int		i;

	i = -1;
	while (++i < mlx->sprite_num)
	{
		distance[i] = ((mlx->player.posx - mlx->sprite[i].x) * (mlx->player.posx
		- mlx->sprite[i].x) + (mlx->player.posy - mlx->sprite[i].y) *
		(mlx->player.posy - mlx->sprite[i].y));
		mlx->sprite_order[i] = i;
	}
	i = -1;
	while (++i < mlx->sprite_num - 1)
		if (distance[i] < distance[i + 1])
		{
			disttmp = distance[i];
			distance[i] = distance[i + 1];
			distance[i + 1] = disttmp;
			tmp = mlx->sprite_order[i];
			mlx->sprite_order[i] = mlx->sprite_order[i + 1];
			mlx->sprite_order[i + 1] = tmp;
			i = -1;
		}
}

t_sprite	*ft_get_sprites(t_mlx *mlx)
{
	int			x;
	int			y;
	int			i;
	t_sprite	*sprites;

	x = 0;
	i = 0;
	mlx->sprite_num = ft_count_sprites(mlx);
	sprites = malloc(sizeof(t_sprite) * mlx->sprite_num);
	mlx->sprite_order = malloc(sizeof(int) * mlx->sprite_num);
	while (x < mlx->map_width)
	{
		y = 0;
		while (y < mlx->map_height)
		{
			if (mlx->world_map[x][y] == '2')
			{
				sprites[i].x = x + 0.5;
				sprites[i++].y = y + 0.5;
			}
			y++;
		}
		x++;
	}
	return (sprites);
}

void		draw_sprite(t_mlx *mlx)
{
	mlx->draw_sp.texx = (int)(256 * (mlx->draw_sp.stripe -
		(-mlx->draw_sp.spritewidth / 2 + mlx->draw_sp.spritescreenx)) *
		mlx->tex_load.width_1 / mlx->draw_sp.spritewidth) / 256;
	if (mlx->draw_sp.transformy > 0 && mlx->draw_sp.stripe > 0 &&
		mlx->draw_sp.stripe < mlx->window.scr_w &&
		mlx->draw_sp.transformy < mlx->zbuffer[mlx->draw_sp.stripe])
	{
		mlx->draw_sp.y = mlx->draw_sp.drawstarty;
		while (mlx->draw_sp.y < mlx->draw_sp.drawendy)
		{
			mlx->draw_sp.d = (mlx->draw_sp.y) * 256 - mlx->window.scr_h
				* 128 + mlx->draw_sp.spriteheight * 128;
			mlx->draw_sp.texy =
				((mlx->draw_sp.d * mlx->tex_load.height_1) /
				mlx->draw_sp.spriteheight) / 256;
			mlx->draw_sp.color =
				mlx->tex_load.sp_text_data[(mlx->tex_load.width_1 *
				mlx->draw_sp.texy) + mlx->draw_sp.texx];
			if (mlx->draw_sp.color != 0)
				mlx->img.data[(mlx->draw_sp.y * mlx->window.scr_w) +
					mlx->draw_sp.stripe] = mlx->draw_sp.color;
			mlx->draw_sp.y++;
		}
	}
}

void		cal_sprite_size(t_mlx *mlx)
{
	mlx->draw_sp.spritescreenx = (int)(mlx->window.scr_w / 2) *
		(1 + mlx->draw_sp.transformx / mlx->draw_sp.transformy);
	mlx->draw_sp.spriteheight = abs((int)(mlx->window.scr_h /
		(mlx->draw_sp.transformy)));
	mlx->draw_sp.drawstarty = -mlx->draw_sp.spriteheight / 2 +
		mlx->window.scr_h / 2;
	if (mlx->draw_sp.drawstarty < 0)
		mlx->draw_sp.drawstarty = 0;
	mlx->draw_sp.drawendy = mlx->draw_sp.spriteheight / 2 +
		mlx->window.scr_h / 2;
	if (mlx->draw_sp.drawendy >= mlx->window.scr_h)
		mlx->draw_sp.drawendy = mlx->window.scr_h - 1;
	mlx->draw_sp.spritewidth = abs((int)(mlx->window.scr_h /
		(mlx->draw_sp.transformy)));
	mlx->draw_sp.drawstartx = -mlx->draw_sp.spritewidth /
		2 + mlx->draw_sp.spritescreenx;
	if (mlx->draw_sp.drawstartx < 0)
		mlx->draw_sp.drawstartx = 0;
	mlx->draw_sp.drawendx = mlx->draw_sp.spritewidth /
		2 + mlx->draw_sp.spritescreenx;
	if (mlx->draw_sp.drawendx >= mlx->window.scr_w)
		mlx->draw_sp.drawendx = mlx->window.scr_w - 1;
	mlx->draw_sp.stripe = mlx->draw_sp.drawstartx;
}

void		ft_sprites(t_mlx *mlx)
{
	int		i;

	i = 0;
	ft_sort_sprites(mlx);
	while (i < mlx->sprite_num)
	{
		mlx->draw_sp.spritex = mlx->sprite[mlx->sprite_order[i]].x -
			mlx->player.posx;
		mlx->draw_sp.spritey = mlx->sprite[mlx->sprite_order[i]].y -
			mlx->player.posy;
		mlx->draw_sp.invdet = 1.0 / (mlx->player.planex * mlx->player.diry -
			mlx->player.dirx * mlx->player.planey);
		mlx->draw_sp.transformx = mlx->draw_sp.invdet * (mlx->player.diry *
			mlx->draw_sp.spritex - mlx->player.dirx * mlx->draw_sp.spritey);
		mlx->draw_sp.transformy = mlx->draw_sp.invdet * (-mlx->player.planey *
			mlx->draw_sp.spritex + mlx->player.planex * mlx->draw_sp.spritey);
		cal_sprite_size(mlx);
		while (mlx->draw_sp.stripe < mlx->draw_sp.drawendx)
		{
			draw_sprite(mlx);
			mlx->draw_sp.stripe++;
		}
		i++;
	}
}
