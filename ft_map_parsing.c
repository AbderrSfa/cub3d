#include "cub3d.h"

int		get_map_x(char **lines, t_mlx *mlx)
{
	int		i;
	int		j;
	int		empty;

	i = 0;
	j = 0;
	empty = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j] == ' ' || lines[i][j] == '\t')
			j++;
		if (!lines[i][j])
			empty = 1;
		if (lines[i][j] && empty)
			ft_put_error("Extra input after end of map!", mlx);
		i++;
	}
	return (i);
}

int		get_map_y(char **lines, t_mlx *mlx)
{
	int		i;
	int		j;
	int		ret;


	i = 0;
	j = 0;
	ret = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
			j++;
		if (ret < j)
			ret = j;
		i++;
	}
	return (ret);
}

void	map_allocation(t_mlx *mlx)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	mlx->world_map = malloc(sizeof(int *) * (mlx->map_width + 1));
	while (i <= mlx->map_width)
	{
		j = 0;
		mlx->world_map[i] = malloc(sizeof(int) * (mlx->map_height + 1));
		while (j <= mlx->map_height)
		{
			mlx->world_map[i][j] = 'x';
			j++;
		}
		i++;
	}
}

void	create_map(char **lines, t_mlx *mlx)
{
	int		i;
	int		j;
	int		x;
	int		y;
	int		last_y;


	x = 0;
	i = 0;
	last_y = 0;
	while (lines[i])
	{
		y = 0;
		j = 0;
		while (lines[i][j])
		{
			while (lines[i][j] == ' ' || lines[i][j] == '\t')
				j++;
			if (lines[i][j])
				mlx->world_map[i][y++] = lines[i][j++];
		}
		if (last_y < y)
			last_y = y;
		x++;
		i++;
	}
	mlx->map_height = last_y;
}

void	check_spot(t_mlx *mlx, int x, int y)
{
	int 	**map;

	mlx->status.player_done = 0;
	map = mlx->world_map;
	if (x == 0 || y == 0 || x == mlx->map_width)
		ft_put_error("Map not properly closed off!", mlx);
	if (map[x][y - 1] == 'x')
		ft_put_error("Map not properly closed off!", mlx);
	if (map[x][y + 1] == 'x')
		ft_put_error("Map not properly closed off!", mlx);
	if (map[x + 1][y] == 'x')
		ft_put_error("Map not properly closed off!", mlx);
	if (map[x - 1][y] == 'x')
		ft_put_error("Map not properly closed off!", mlx);
}

void	ft_map_checker(t_mlx *mlx)
{
	int x;
	int y;

	x = 0;
	while (x < mlx->map_width)
	{
		y = 0;
		while (y < mlx->map_height)
		{
			if (mlx->world_map[x][y] != '1'
					&& mlx->world_map[x][y] != 'x')
				check_spot(mlx, x, y);
			y++;
		}
		x++;
	}
}