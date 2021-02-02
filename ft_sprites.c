#include "cub3d.h"

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
                sprites[i].x = x;
                sprites[i].y = y;
                i++;
            }
            y++;
        }
        x++;
    }
    return (sprites);
}
