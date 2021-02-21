/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 12:06:20 by asfaihi           #+#    #+#             */
/*   Updated: 2021/02/21 12:07:17 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_color(char *line, t_mlx *mlx)
{
	if (*line == 'C')
		get_color(&(*++line), mlx, 'C');
	else
		get_color(&(*++line), mlx, 'F');
}

int		color_parse(char *line, int i, t_mlx *mlx)
{
	int		count;

	count = 0;
	mlx->color.color = 0;
	mlx->color.commas = 0;
	while (count < 3)
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (!ft_isdigit(line[i]) || ft_atoi(line + i) > 255)
			ft_put_error("Invalid color input!", mlx);
		mlx->color.color = mlx->color.color * 256 + ft_atoi(line + i);
		i += ft_intsize(ft_atoi(line + i));
		count++;
		if (count == 3)
			break ;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == ',')
		{
			mlx->color.commas++;
			i++;
		}
	}
	return (i);
}

void	get_color(char *line, t_mlx *mlx, char type)
{
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	i = color_parse(line, i, mlx);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (mlx->color.commas != 2 || line[i])
		ft_put_error("Invalid color input!", mlx);
	if (type == 'C')
	{
		if (mlx->status.ceiling_done)
			ft_put_error("Ceiling color already defined!", mlx);
		mlx->window.ceiling_color = mlx->color.color;
		mlx->status.ceiling_done = 1;
	}
	else
	{
		if (mlx->status.floor_done)
			ft_put_error("Floor color already defined!", mlx);
		mlx->window.floor_color = mlx->color.color;
		mlx->status.floor_done = 1;
	}
}
