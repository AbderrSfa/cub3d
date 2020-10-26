#include "cub3d.h"

void	set_player(t_player *player)
{
	player->x = WIN_WIDTH / 2;
	player->y = WIN_HEIGHT / 2;
	player->radius = 10;
	player->turn_dir = 0;
	player->walk_dir = 0;
	player->rotation_angle = M_PI / 2;
	player->move_speed = 3.0;
	player->rotation_speed = 3 * (M_PI / 180);
}

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
			mlx_pixel_put(mlx_ptr, win_ptr, x + i, y + j, 0x355E3B);
			i++;
		}
		j++;
	}
}

void	draw_map(void *mlx_ptr, void *win_ptr)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < (TILE_SIZE * NUM_ROWS))
	{
		x = 0;
		while (x < (TILE_SIZE * NUM_COLOMNS))
		{
			if (world_map[y / TILE_SIZE][x / TILE_SIZE] > 0)
				draw_square(mlx_ptr, win_ptr, x, y);
			x += TILE_SIZE;
		}
		y += TILE_SIZE;
	}
}

void	draw_player(void *mlx_ptr, void *win_ptr, t_player *player)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < player->radius)
	{
		i = 0;
		while (i < player->radius)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, player->x + player->turn_dir + i, player->y + player->walk_dir + j, 0xFFFFFF);
			i++;
		}
		j++;
	}
}

int		deal_key(int key, t_player *player)
{
	if (key == 126)
		player->walk_dir -= 8;
	else if (key == 125)
		player->walk_dir += 8;
	else if (key == 124)
		player->turn_dir += 8;
	else if (key == 123)
		player->turn_dir -= 8;
	draw_map(player->mlx, player->win);
	mlx_clear_window(player->mlx, player->win);
	draw_player(player->mlx, player->win, player);
	return (0);
}

int     main()
{
	void		*mlx_ptr;
	void    	*win_ptr;
	t_player	player;
	int     	x;
	int     	y;

	x = 0;
	y = 0;
	mlx_ptr = mlx_init();
	player.mlx = mlx_ptr;
	win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "map");
	player.win = win_ptr;
	set_player(&player);
	draw_map(mlx_ptr, win_ptr);
	draw_player(mlx_ptr, win_ptr, &player);
	mlx_key_hook(win_ptr, deal_key, &player);
	mlx_loop(mlx_ptr);
}
