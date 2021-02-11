#include "cub3d.h"

int		ft_update(t_mlx *mlx)
{
	mlx->img.img_ptr = mlx_new_image(mlx->window.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx_clear_window(mlx->window.mlx_ptr, mlx->window.win_ptr);
	ft_movement(mlx);
	mlx->ZBuffer = malloc(sizeof(double) * SCREEN_WIDTH);
	ft_draw_ceiling_floor(mlx);
	ft_draw_walls(mlx);
	free(mlx->ZBuffer);
	if (mlx->save_arg == 1)
		ft_screenshot(mlx);
	mlx_put_image_to_window(mlx->window.mlx_ptr, mlx->window.win_ptr, mlx->img.img_ptr, 0, 0);
	mlx_destroy_image(mlx->window.mlx_ptr, mlx->img.img_ptr);
	return (0);
}

