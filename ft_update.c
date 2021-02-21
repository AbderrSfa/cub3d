/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:40:44 by asfaihi           #+#    #+#             */
/*   Updated: 2021/02/18 11:28:58 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_update(t_mlx *mlx)
{
	mlx->img.img_ptr = mlx_new_image(mlx->window.mlx_ptr, mlx->window.scr_w,
		mlx->window.scr_h);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr,
		&mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx_clear_window(mlx->window.mlx_ptr, mlx->window.win_ptr);
	ft_movement(mlx);
	mlx->zbuffer = malloc(sizeof(double) * mlx->window.scr_w);
	ft_draw_ceiling_floor(mlx);
	ft_draw_walls(mlx);
	free(mlx->zbuffer);
	if (mlx->save_arg == 1)
		ft_screenshot(mlx);
	mlx_put_image_to_window(mlx->window.mlx_ptr, mlx->window.win_ptr,
		mlx->img.img_ptr, 0, 0);
	mlx_destroy_image(mlx->window.mlx_ptr, mlx->img.img_ptr);
	return (0);
}
