/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 13:00:07 by asfaihi           #+#    #+#             */
/*   Updated: 2021/02/22 14:28:58 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_posx(t_mlx *mlx)
{
	if (mlx->side == 0)
		mlx->texture.wallx = mlx->player.posy + (mlx->perpwalldist *
			mlx->raydiry);
	else
		mlx->texture.wallx = mlx->player.posx + (mlx->perpwalldist *
			mlx->raydirx);
	mlx->texture.wallx -= floor((mlx->texture.wallx));
	mlx->texture.texx = (int)(mlx->texture.wallx *
		(double)mlx->tex_load.width_1);
	if (mlx->side == 0)
	{
		if (mlx->raydirx > 0)
			mlx->walldir = 'N';
		else
			mlx->walldir = 'S';
		mlx->texture.texx = mlx->tex_load.width_1 - mlx->texture.texx - 1;
	}
	else
	{
		if (mlx->raydiry > 0)
			mlx->walldir = 'W';
		else
			mlx->walldir = 'E';
		mlx->texture.texx = mlx->tex_load.width_1 - mlx->texture.texx - 1;
	}
}

void	load_right_tex(t_mlx *mlx)
{
	if (mlx->walldir == 'N')
	{
		mlx->tex_load.texture_data = mlx->tex_load.text_data_1;
		mlx->tex_load.height = mlx->tex_load.height_1;
		mlx->tex_load.width = mlx->tex_load.width_1;
	}
	else if (mlx->walldir == 'S')
	{
		mlx->tex_load.texture_data = mlx->tex_load.text_data_2;
		mlx->tex_load.height = mlx->tex_load.height_2;
		mlx->tex_load.width = mlx->tex_load.width_2;
	}
	else if (mlx->walldir == 'E')
	{
		mlx->tex_load.texture_data = mlx->tex_load.text_data_3;
		mlx->tex_load.height = mlx->tex_load.height_3;
		mlx->tex_load.width = mlx->tex_load.width_3;
	}
	else if (mlx->walldir == 'W')
	{
		mlx->tex_load.texture_data = mlx->tex_load.text_data_4;
		mlx->tex_load.height = mlx->tex_load.height_4;
		mlx->tex_load.width = mlx->tex_load.width_4;
	}
}

void	ft_texture(t_mlx *mlx, int x)
{
	texture_posx(mlx);
	mlx->texture.step = (1.0 * mlx->tex_load.height_1) / mlx->lineheight;
	mlx->texture.texpos = (mlx->drawstart - (mlx->window.scr_h / 2) +
		(mlx->lineheight / 2)) * mlx->texture.step;
	mlx->texture.y = mlx->drawstart;
	load_right_tex(mlx);
	while (mlx->texture.y < mlx->drawend)
	{
		mlx->texture.texy = (int)mlx->texture.texpos &
			(mlx->tex_load.height_1 - 1);
		mlx->texture.texpos += mlx->texture.step;
		mlx->texture.color = mlx->tex_load.texture_data[(mlx->tex_load.height_1
			* mlx->texture.texy) + mlx->texture.texx];
		mlx->img.data[(mlx->texture.y * mlx->window.scr_w) + x] =
			mlx->texture.color;
		mlx->texture.y++;
	}
}
