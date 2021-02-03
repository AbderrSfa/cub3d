#include "cub3d.h"

void		ft_sort_sprites(t_mlx *mlx)
{
	double	distance[mlx->sprite_num];
	int		tmp;
	int		disttmp;
	int		i;

	i = -1;
	while (++i < mlx->sprite_num)
	{
		distance[i] = ((mlx->player.posX - mlx->sprite[i].x) * (mlx->player.posX -
		mlx->sprite[i].x) + (mlx->player.posY - mlx->sprite[i].y) * (mlx->player.posY -
		mlx->sprite[i].y));
		mlx->sprite_order[i] = i;
	}
	i = -1;
	while (++i < mlx->sprite_num - 1)
		if (distance[i] < distance[i + 1])
		{
			disttmp = distance[i];
			distance[i] = distance[i + 1];
			distance[i + 1] = disttmp;
			tmp = mlx->sprite_order[i];
			mlx->sprite_order[i] = mlx->sprite_order[i + 1];
			mlx->sprite_order[i + 1] = tmp;
			i = -1;
		}
}

int         ft_count_sprites(t_mlx *mlx)
{
    int     x;
    int     y;
    int     ret;

    x = 0;
    y = 0;
    ret = 0;
    while (x < mlx->map_width)
    {
        y = 0;
        while (y < mlx->map_height)
        {
            if (mlx->world_map[x][y] == '2')
                ret++;
            y++;
        }
        x++;
    }
    return (ret);
}

t_sprite    *ft_get_sprites(t_mlx *mlx)
{
    int         x;
    int         y;
    int         i;
    t_sprite    *sprites;

    x = 0;
    y = 0;
    i = 0;
    mlx->sprite_num = ft_count_sprites(mlx);
    sprites = malloc(sizeof(t_sprite) * mlx->sprite_num);
    mlx->sprite_order = malloc(sizeof(int) * mlx->sprite_num);
    while (x < mlx->map_width)
    {
        y = 0;
        while (y < mlx->map_height)
        {
            if (mlx->world_map[x][y] == '2')
            {
                sprites[i].x = x + 0.5;
                sprites[i].y = y + 0.5;
                i++;
            }
            y++;
        }
        x++;
    }
    return (sprites);
}
