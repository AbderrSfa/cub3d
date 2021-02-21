/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 12:46:19 by asfaihi           #+#    #+#             */
/*   Updated: 2021/02/18 11:11:36 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_vars(t_mlx *mlx)
{
	mlx->save_arg = 0;
	mlx->status.res_done = 0;
	mlx->status.north_done = 0;
	mlx->status.south_done = 0;
	mlx->status.west_done = 0;
	mlx->status.east_done = 0;
	mlx->status.sprite_done = 0;
	mlx->status.floor_done = 0;
	mlx->status.ceiling_done = 0;
	mlx->window.scr_w = 0;
	mlx->window.scr_h = 0;
	mlx->path.north_path = NULL;
	mlx->path.south_path = NULL;
	mlx->path.west_path = NULL;
	mlx->path.east_path = NULL;
	mlx->path.spr_path = NULL;
	mlx->window.floor_color = 0;
	mlx->window.ceiling_color = 0;
}

int		save_checker(char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
		i++;
	if (arg[i - 1] == 'e' && arg[i - 2] == 'v' && arg[i - 3] == 'a' &&
		arg[i - 4] == 's' && arg[i - 5] == '-' && arg[i - 6] == '-')
		return (1);
	return (0);
}

int		name_checker(char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
		i++;
	if (arg[i - 1] == 'b' && arg[i - 2] == 'u' && arg[i - 3] == 'c'
		&& arg[i - 4] == '.')
		return (1);
	return (0);
}
