#include "mlx.h"

# define TILE_SIZE 32
# define NUM_COLOMNS 16
# define NUM_ROWS 10
# define WIN_WIDTH (TILE_SIZE * NUM_COLOMNS)
# define WIN_HEIGHT (TILE_SIZE * NUM_ROWS)

int		world_map[NUM_ROWS][NUM_COLOMNS] =
{
	{1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
	{1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1},
	{1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void	draw_square(void *mlx_ptr, void *win_ptr, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < TILE_SIZE)
	{
		i = 0;
		while (i < TILE_SIZE)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x + i, y + j, 0xFFFFFF);
			i++;
		}
		j++;
	}
}

int     main()
{
	void    *mlx_ptr;
	void    *win_ptr;
	int     x;
	int     y;

	x = 0;
	y = 0;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "map");
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (world_map[y / TILE_SIZE][x / TILE_SIZE] == 1)
				draw_square(mlx_ptr, win_ptr, x, y);
			x += TILE_SIZE;
		}
		y += TILE_SIZE;
	}
	mlx_loop(mlx_ptr);
}