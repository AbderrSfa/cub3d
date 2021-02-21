/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 12:44:24 by asfaihi           #+#    #+#             */
/*   Updated: 2021/02/21 12:06:47 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	north_south_path(char *line, t_mlx *mlx, int i, int j)
{
	if (line[0] == 'N')
	{
		if (mlx->status.north_done)
			ft_put_error("North texture path already defined!", mlx);
		mlx->path.north_path = ft_substr(line, i, j - i);
		mlx->status.north_done = 1;
	}
	else if (line[0] == 'S')
	{
		if (mlx->status.south_done)
			ft_put_error("South texture path already defined!", mlx);
		mlx->path.south_path = ft_substr(line, i, j - i);
		mlx->status.south_done = 1;
	}
}

void	west_east_path(char *line, t_mlx *mlx, int i, int j)
{
	if (line[0] == 'W')
	{
		if (mlx->status.west_done)
			ft_put_error("West texture path already defined!", mlx);
		mlx->path.west_path = ft_substr(line, i, j - i);
		mlx->status.west_done = 1;
	}
	else if (line[0] == 'E')
	{
		if (mlx->status.east_done)
			ft_put_error("East texture path already defined!", mlx);
		mlx->path.east_path = ft_substr(line, i, j - i);
		mlx->status.east_done = 1;
	}
}

void	get_tex_path(char *line, t_mlx *mlx)
{
	int		i;
	int		j;

	i = 2;
	j = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	j = i;
	while (line[j] != ' ' && line[j] != '\0')
		j++;
	north_south_path(line, mlx, i, j);
	west_east_path(line, mlx, i, j);
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	if (line[j])
		ft_put_error("Extra input next to texture path!", mlx);
}

void	get_sprite_path(char *line, t_mlx *mlx)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (mlx->status.sprite_done)
		ft_put_error("Sprite path already defined!", mlx);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	j = i;
	while (line[j] != ' ' && line[j] != '\0')
		j++;
	mlx->path.spr_path = ft_substr(line, i, j - i);
	mlx->status.sprite_done = 1;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	if (line[j])
		ft_put_error("Extra input next to sprite path!", mlx);
}

void	get_resolution(char *line, t_mlx *mlx)
{
	int		i;

	i = 1;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (mlx->status.res_done)
		ft_put_error("Resolution identifier already defined!", mlx);
	if (!ft_isdigit(line[i]))
		ft_put_error("Invalid resolution input!", mlx);
	mlx->window.scr_w = ft_atoi(line + i);
	i += ft_intsize(mlx->window.scr_w);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!ft_isdigit(line[i]))
		ft_put_error("Invalid resolution input!", mlx);
	mlx->window.scr_h = ft_atoi(line + i);
	i += ft_intsize(mlx->window.scr_h);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i])
		ft_put_error("Invalid resolution input!", mlx);
	mlx->status.res_done = 1;
}
