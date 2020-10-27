#include "cub3d.h"

void	set_player(t_player *player)
{
	player->x = WIN_WIDTH / 2;
	player->y = WIN_HEIGHT / 2;
	player->radius = 10;
	player->turn_dir = 0;
	player->walk_dir = 0;
	player->rotation_angle = M_PI / 2;
	player->move_speed = 6.0;
	player->rotation_speed = 6 * (M_PI / 180);
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
			mlx_pixel_put(mlx_ptr, win_ptr, player->x + i, player->y + j, 0xFFFFFF);
			i++;
		}
		j++;
	}
}

int		has_wall(t_player *player)
{
	if (player->x < 0 || player->x > WIN_WIDTH || player->y < 0 || player->y > WIN_HEIGHT)
		return (1);
	if (world_map[(player->y / TILE_SIZE)][(player->x / TILE_SIZE)] == 1)
		return (1);
	return (0);
}

void	update_player(void *mlx_ptr, void *win_ptr, t_player *player)
{
	double	move_step;
	double	temp_x;
	double	temp_y;

	move_step = player->walk_dir * player->move_speed;
	player->rotation_angle += player->turn_dir * player->rotation_speed;
	temp_x = player->x + cos(player->rotation_angle) * move_step;
	temp_y = player->y + sin(player->rotation_angle) * move_step;
/* 	if (!has_wall(player))
	{ */
		player->x = temp_x;
		player->y = temp_y;
/* 	} */
	draw_player(mlx_ptr, win_ptr, player);
}

int		key_pressed(int key, t_player *player)
{
	if (key == 126)
		player->walk_dir = -1;
	else if (key == 123)
		player->turn_dir = -1;
	else if (key == 125)
		player->walk_dir = 1;
	else if (key == 124)
		player->turn_dir = 1;
	draw_map(player->mlx, player->win);
	mlx_clear_window(player->mlx, player->win);
	update_player(player->mlx, player->win, player);
	return (0);
}

int		key_released(int key, t_player *player)
{
	if (key == 126)
		player->walk_dir = 0;
	else if (key == 125)
		player->walk_dir = 0;
	else if (key == 124)
		player->turn_dir = 0;
	else if (key == 123)
		player->turn_dir = 0;
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
	mlx_hook(win_ptr, 2, (1L<<0), key_pressed, &player);
	mlx_hook(win_ptr, 3, (1L<<1), key_released, &player);
	mlx_loop(mlx_ptr);
}
