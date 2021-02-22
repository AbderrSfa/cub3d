/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 12:41:17 by asfaihi           #+#    #+#             */
/*   Updated: 2021/02/22 15:26:41 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		get_map_y(char **lines)
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
