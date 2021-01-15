#include "cub3d.h"

void	ft_put_error(char *error)
{
	ft_printf("Error:\n\t%s\n", error);
	exit(EXIT_SUCCESS);
}

void	ft_check_vars(t_mlx *mlx)
{
	if (!mlx->status.res_done)
		ft_put_error("Missing resolution identifier!");
	else if (!mlx->status.north_done)
		ft_put_error("Missing north texture identifier!");
	else if (!mlx->status.south_done)
		ft_put_error("Missing south texture identifier!");
	else if (!mlx->status.west_done)
		ft_put_error("Missing west texture identifier!");
	else if (!mlx->status.east_done)
		ft_put_error("Missing east texture identifier!");
	else if (!mlx->status.sprite_done)
		ft_put_error("Missing sprite texture identifier!");
	else if (!mlx->status.floor_done)
		ft_put_error("Missing floor color identifier!");
	else if (!mlx->status.ceiling_done)
		ft_put_error("Missing ceiling color identifier!");
}