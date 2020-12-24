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

void  load_textures(t_mlx *mlx)
{
	mlx->tex.texture_1 = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/eagle.XPM", &mlx->tex.width, &mlx->tex.height);
	mlx->tex.texture_data[0] = (int *)mlx_get_data_addr(mlx->tex.texture_1, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx->tex.texture_2 = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/wood.XPM", &mlx->tex.width, &mlx->tex.height);
	mlx->tex.texture_data[1] = (int *)mlx_get_data_addr(mlx->tex.texture_2, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx->tex.texture_3 = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/purplestone.XPM", &mlx->tex.width, &mlx->tex.height);
	mlx->tex.texture_data[2] = (int *)mlx_get_data_addr(mlx->tex.texture_3, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx->tex.texture_4 = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/mossy.XPM", &mlx->tex.width, &mlx->tex.height);
	mlx->tex.texture_data[3] = (int *)mlx_get_data_addr(mlx->tex.texture_4, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx->tex.texture_5 = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/bluestone.XPM", &mlx->tex.width, &mlx->tex.height);
	mlx->tex.texture_data[4] = (int *)mlx_get_data_addr(mlx->tex.texture_5, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx->tex.texture_6 = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/redbrick.XPM", &mlx->tex.width, &mlx->tex.height);
	mlx->tex.texture_data[5] = (int *)mlx_get_data_addr(mlx->tex.texture_6, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx->tex.texture_7 = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/greystone.XPM", &mlx->tex.width, &mlx->tex.height);
	mlx->tex.texture_data[6] = (int *)mlx_get_data_addr(mlx->tex.texture_7, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx->tex.texture_8 = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/colorstone.XPM", &mlx->tex.width, &mlx->tex.height);
	mlx->tex.texture_data[7] = (int *)mlx_get_data_addr(mlx->tex.texture_8, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
}

void	ft_initialize(t_mlx *mlx)
{
	mlx->posX = 22;
	mlx->posY = 11.5;
	mlx->dirX = -1;
	mlx->dirY = 0;
	mlx->planeX = 0;
	mlx->planeY = 0.66;
	mlx->moveSpeed = 0.1;
	mlx->rotSpeed = 0.05;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
  load_textures(mlx);
}

int		main()
{
	t_mlx	mlx;

	ft_initialize(&mlx);
	mlx_hook(mlx.win_ptr, 2, (1L<<0), ft_key_pressed, &mlx);
	mlx_hook(mlx.win_ptr, 3, (1L<<1), ft_key_released, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, ft_update, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
