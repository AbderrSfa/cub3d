#include "cub3d.h"

int worldMap[MAP_WIDTH][MAP_HEIGHT] =
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

t_sprite	sprite[NUM_SPRITES] =
{
  {20.5, 11.5}, //green light in front of playerstart
  //green lights in every room
  {18.5, 4.5},
  {10.0, 4.5},
  {10.0, 12.5},
  {3.5, 6.5},
  {3.5, 20.5},
  {3.5, 14.5},
  {14.5, 20.5},

  //row of pillars in front of wall: fisheye test
  {18.5, 10.5},
  {18.5, 11.5},
  {18.5, 12.5},

  //some barrels around the map
  {21.5, 1.5},
  {15.5, 1.5},
  {16.0, 1.8},
  {16.2, 1.2},
  {3.5, 2.5},
  {9.5, 15.5},
  {10.0, 15.1},
  {10.5, 15.8},
};

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
	mlx->player.posX = 22;
	mlx->player.posY = 11.5;
	mlx->player.dirX = -1.0;
	mlx->player.dirY = 0.0;
	mlx->player.planeX = 0.0;
	mlx->player.planeY = 0.66;
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

int   main()
{
	t_mlx	mlx;

	ft_read_map(&mlx);
	ft_start_game(&mlx);

  ft_printf("Resolution:\t-%d-\t-%d-\n", mlx.window.screen_width, mlx.window.screen_height);
	ft_printf("North:\t\t-%s-\n", mlx.path.north_path);
	ft_printf("South:\t\t-%s-\n", mlx.path.south_path);
	ft_printf("West:\t\t-%s-\n", mlx.path.west_path);
	ft_printf("East:\t\t-%s-\n", mlx.path.east_path);
	ft_printf("Sprite:\t\t-%s-\n", mlx.path.sprite_path);
	ft_printf("F Color:\t-%d-\n", mlx.window.floor_color);
	ft_printf("C Color:\t-%d-\n", mlx.window.ceiling_color);
}
