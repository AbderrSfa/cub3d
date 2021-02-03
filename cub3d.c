#include "cub3d.h"

void  load_textures(t_mlx *mlx)
{
	mlx->tex.texture_1 = mlx_xpm_file_to_image(mlx->window.mlx_ptr, mlx->path.east_path, &mlx->tex.width_1, &mlx->tex.height_1);
	mlx->tex.texture_data_1 = (int *)mlx_get_data_addr(mlx->tex.texture_1, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx->tex.texture_2 = mlx_xpm_file_to_image(mlx->window.mlx_ptr, mlx->path.north_path, &mlx->tex.width_2, &mlx->tex.height_2);
	mlx->tex.texture_data_2 = (int *)mlx_get_data_addr(mlx->tex.texture_2, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx->tex.texture_3 = mlx_xpm_file_to_image(mlx->window.mlx_ptr, mlx->path.south_path, &mlx->tex.width_3, &mlx->tex.height_3);
	mlx->tex.texture_data_3 = (int *)mlx_get_data_addr(mlx->tex.texture_3, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx->tex.texture_4 = mlx_xpm_file_to_image(mlx->window.mlx_ptr, mlx->path.west_path, &mlx->tex.width_4, &mlx->tex.height_4);
	mlx->tex.texture_data_4 = (int *)mlx_get_data_addr(mlx->tex.texture_4, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);

	mlx->tex.sp_texture = mlx_xpm_file_to_image(mlx->window.mlx_ptr, mlx->path.sprite_path, &mlx->tex.sp_width, &mlx->tex.sp_height);
	mlx->tex.sp_texture_data = (int *)mlx_get_data_addr(mlx->tex.sp_texture, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
}

void	ft_initialize(t_mlx *mlx)
{
	mlx->player.moveSpeed = 0.15;
	mlx->player.rotSpeed = 0.05;
	mlx->window.mlx_ptr = mlx_init();
	mlx->window.win_ptr = mlx_new_window(mlx->window.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
  	load_textures(mlx);
}

void	ft_start_game(t_mlx *mlx)
{
	ft_initialize(mlx);
	mlx_hook(mlx->window.win_ptr, 2, (1L<<0), ft_key_pressed, mlx);
	mlx_hook(mlx->window.win_ptr, 3, (1L<<1), ft_key_released, mlx);
  mlx_hook(mlx->window.win_ptr, 17, (1L<<5), ft_close_game, mlx);
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
    ft_printf("Game Map:\n");
		for (int i = 0; i < mlx.map_width; i++)
		{
			for (int j = 0; j < mlx.map_height; j++)
				ft_printf("%c,", mlx.world_map[i][j]);
			ft_printf("\n");
		}
	  ft_start_game(&mlx);
	}
	else
		ft_put_error("Invalid arguments!", &mlx);
	return (0);
}