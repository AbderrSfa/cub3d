#include "cub3d.h"

int		ft_close_game(t_mlx *mlx)
{
	int		i;

	i = 0;
	while (i <= get_lines_count())
		free(mlx->status.lines[i++]);
	free(mlx->status.lines);
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
	exit(EXIT_SUCCESS);
	return (0);
}

void	ft_put_error(char *error, t_mlx *mlx)
{
	ft_printf("Error:\n\t%s\n", error);
	ft_close_game(mlx);
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