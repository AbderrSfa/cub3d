/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:07:24 by asfaihi           #+#    #+#             */
/*   Updated: 2021/03/03 16:33:03 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_mlx *mlx)
{
	mlx->tex_load.text_1 = mlx_xpm_file_to_image(mlx->window.mlx_ptr,
		mlx->path.south_path, &mlx->tex_load.width_1, &mlx->tex_load.height_1);
	mlx->tex_load.text_data_1 = (int *)mlx_get_data_addr(mlx->tex_load.text_1,
		&mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx->tex_load.text_2 = mlx_xpm_file_to_image(mlx->window.mlx_ptr,
		mlx->path.north_path, &mlx->tex_load.width_2, &mlx->tex_load.height_2);
	mlx->tex_load.text_data_2 = (int *)mlx_get_data_addr(mlx->tex_load.text_2,
		&mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx->tex_load.text_3 = mlx_xpm_file_to_image(mlx->window.mlx_ptr,
		mlx->path.west_path, &mlx->tex_load.width_3, &mlx->tex_load.height_3);
	mlx->tex_load.text_data_3 = (int *)mlx_get_data_addr(mlx->tex_load.text_3,
		&mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx->tex_load.text_4 = mlx_xpm_file_to_image(mlx->window.mlx_ptr,
		mlx->path.east_path, &mlx->tex_load.width_4, &mlx->tex_load.height_4);
	mlx->tex_load.text_data_4 = (int *)mlx_get_data_addr(mlx->tex_load.text_4,
		&mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx->tex_load.text_5 = mlx_xpm_file_to_image(mlx->window.mlx_ptr, "textures/light_tiles.XPM",
		&mlx->tex_load.width_5, &mlx->tex_load.height_5);
	mlx->tex_load.text_data_5 = (int *)mlx_get_data_addr(mlx->tex_load.text_5,
		&mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx->tex_load.text_6 = mlx_xpm_file_to_image(mlx->window.mlx_ptr, "textures/dark_tiles.XPM",
		&mlx->tex_load.width_6, &mlx->tex_load.height_6);
	mlx->tex_load.text_data_6 = (int *)mlx_get_data_addr(mlx->tex_load.text_6,
		&mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx->tex_load.sp_text = mlx_xpm_file_to_image(mlx->window.mlx_ptr,
		mlx->path.spr_path, &mlx->tex_load.sp_width, &mlx->tex_load.sp_height);
	mlx->tex_load.sp_text_data = (int *)mlx_get_data_addr(mlx->tex_load.sp_text,
		&mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
}

void	ft_initialize(t_mlx *mlx)
{
	mlx->player.movespeed = 0.1;
	mlx->player.rotspeed = 0.04;
	mlx->window.mlx_ptr = mlx_init();
	mlx->window.win_ptr = mlx_new_window(mlx->window.mlx_ptr, mlx->window.scr_w,
	mlx->window.scr_h, "cub3d");
	load_textures(mlx);
}

void	ft_start_game(t_mlx *mlx, int save)
{
	ft_initialize(mlx);
	mlx->save_arg = save;
	mlx_hook(mlx->window.win_ptr, 2, (1L << 0), ft_key_pressed, mlx);
	mlx_hook(mlx->window.win_ptr, 3, (1L << 1), ft_key_released, mlx);
	mlx_hook(mlx->window.win_ptr, 17, (1L << 5), ft_close_game, mlx);
	mlx_loop_hook(mlx->window.mlx_ptr, ft_update, mlx);
	mlx_loop(mlx->window.mlx_ptr);
}

int		main(int argc, char **argv)
{
	t_mlx	mlx;

	mlx.lines = NULL;
	ft_init_vars(&mlx);
	if (argc == 2 && name_checker(argv[1]))
	{
		ft_read_map(&mlx, argv[1]);
		ft_start_game(&mlx, 0);
	}
	else if (argc == 3 && name_checker(argv[1]) && save_checker(argv[2]))
	{
		ft_read_map(&mlx, argv[1]);
		ft_start_game(&mlx, 1);
	}
	else
		ft_put_error("Invalid arguments!", &mlx);
	return (0);
}
