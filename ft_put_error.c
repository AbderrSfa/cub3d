#include "cub3d.h"

int		check_file(char *file_path)
{
	int		fd;

	fd = open(file_path, O_RDONLY);
	close(fd);
	return (fd);
}

void	verify_vars(t_mlx *mlx)
{
	if (check_file(mlx->path.north_path) == -1)
		ft_put_error("North texture file does not exist!", mlx);
	if (check_file(mlx->path.south_path) == -1)
		ft_put_error("South texture file does not exist!", mlx);
	if (check_file(mlx->path.west_path) == -1)
		ft_put_error("West texture file does not exist!", mlx);
	if (check_file(mlx->path.east_path) == -1)
		ft_put_error("East texture file does not exist!", mlx);
	if (check_file(mlx->path.sprite_path) == -1)
		ft_put_error("Sprite texture file does not exist!", mlx);
	if (mlx->window.screen_height > 1440)
		mlx->window.screen_height = 1440;
	if (mlx->window.screen_width > 2560)
		mlx->window.screen_width = 2560;
}

int		ft_close_game(t_mlx *mlx, int ret)
{
	int		i;

	i = 0;
	if (mlx->lines != NULL)
	{
		while (i <= mlx->lines_count)
			free(mlx->lines[i++]);
		free(mlx->lines);
	}
	if (mlx->status.north_done)
		free(mlx->path.north_path);
	if (mlx->status.south_done)
		free(mlx->path.south_path);
	if (mlx->status.west_done)
		free(mlx->path.west_path);
	if (mlx->status.east_done)
		free(mlx->path.east_path);
	if (mlx->status.sprite_done)
		free(mlx->path.sprite_path);
	if (ret == 0)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

void	ft_put_error(char *error, t_mlx *mlx)
{
/* 	ft_printf("Error:\n\033[0;31m\t%s\n", error);
 */
	ft_putstr("Error:\n\033[0;31m\t");
	ft_putstr(error);
	ft_putstr("\n");
	ft_close_game(mlx, 1);
}

void	ft_check_vars(t_mlx *mlx)
{
	if (!mlx->status.res_done)
		ft_put_error("Missing resolution identifier!", mlx);
	else if (!mlx->status.north_done)
		ft_put_error("Missing north texture identifier!", mlx);
	else if (!mlx->status.south_done)
		ft_put_error("Missing south texture identifier!", mlx);
	else if (!mlx->status.west_done)
		ft_put_error("Missing west texture identifier!", mlx);
	else if (!mlx->status.east_done)
		ft_put_error("Missing east texture identifier!", mlx);
	else if (!mlx->status.sprite_done)
		ft_put_error("Missing sprite texture identifier!", mlx);
	else if (!mlx->status.floor_done)
		ft_put_error("Missing floor color identifier!", mlx);
	else if (!mlx->status.ceiling_done)
		ft_put_error("Missing ceiling color identifier!", mlx);
}