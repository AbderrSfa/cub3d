#include "cub3d.h"

void	get_player_details(char spot, int x, int y, t_mlx *mlx)
{
	if (mlx->status.player_done == 1)
		ft_put_error("Multiple spawnpoints!", mlx);
	if (spot != 'N' && spot != 'S' && spot != 'W' && spot != 'E')
		ft_put_error("Invalid map character!", mlx);
	mlx->player.posX = x;
	mlx->player.posY = y;
}

int		check_for_player(int x, int y, t_mlx *mlx)
{
	char	spot;

	spot = mlx->world_map[x][y];
	if (spot != '0' && spot != '1' && spot != '2' && spot != ' ')
	{
		get_player_details(spot, x, y, mlx);
		return (1);
	}
	return (0);
}

void	player_position(t_mlx *mlx)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	mlx->status.player_done = 0;
	while (x <= mlx->map_width)
	{
		y = 0;
		while (y <= mlx->map_height)
		{
			if (check_for_player(x, y, mlx))
				mlx->status.player_done = 1;
			y++;
		}
		x++;
	}
	if (mlx->status.player_done == 0)
		ft_put_error("No player spawnpoint!", mlx);
}