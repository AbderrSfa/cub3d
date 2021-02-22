/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:52:25 by asfaihi           #+#    #+#             */
/*   Updated: 2021/02/22 15:24:39 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**get_filelines(char **lines, char **temp, int fd)
{
	char	*string;
	int		i;
	int		j;
	int		r;

	r = 1;
	i = 1;
	while (r)
	{
		r = get_next_line(fd, &string);
		temp = lines;
		j = 0;
		lines = malloc((i + 1) * sizeof(char *));
		if (temp)
			while (temp[j])
			{
				lines[j] = temp[j];
				j++;
			}
		free(temp);
		lines[j++] = string;
		lines[j] = 0;
		i++;
	}
	return (lines);
}

int		get_lines_count(char *file)
{
	int		fd;
	int		r;
	char	*line;
	int		count;

	count = 0;
	fd = open(file, O_RDONLY);
	while ((r = get_next_line(fd, &line)))
	{
		count++;
		free(line);
	}
	free(line);
	close(fd);
	return (count);
}

int		parse_lines(char *line, t_mlx *mlx)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0')
		return (0);
	if (*line == 'R' && *(line + 1) == ' ')
		get_resolution(line, mlx);
	else if (*line == 'S' && *(line + 1) == ' ')
		get_sprite_path(line, mlx);
	else if ((*line == 'C' && *(line + 1) == ' ') ||
		(*line == 'F' && *(line + 1) == ' '))
		parse_color(line, mlx);
	else if ((*line == 'N' && *(line + 1) == 'O' && *(line + 2) == ' ') ||
	(*line == 'S' && *(line + 1) == 'O' && *(line + 2) == ' ') ||
	(*line == 'W' && *(line + 1) == 'E' && *(line + 2) == ' ') ||
	(*line == 'E' && *(line + 1) == 'A' && *(line + 2) == ' '))
		get_tex_path(line, mlx);
	else if (*line == '0' || *line == '1' || *line == '2')
		return (1);
	else
		ft_put_error("Invalid Identifier!", mlx);
	return (0);
}

void	ft_read_map_2(t_mlx *mlx, int i)
{
	verify_vars(mlx);
	mlx->map_width = get_map_x(&mlx->lines[i - 1], mlx);
	mlx->map_height = get_map_y(&mlx->lines[i - 1]);
	map_allocation(mlx);
	create_map(&mlx->lines[i - 1], mlx);
	player_position(mlx);
	ft_map_checker(mlx);
	mlx->sprite = ft_get_sprites(mlx);
}

void	ft_read_map(t_mlx *mlx, char *file)
{
	int		i;
	int		ret;
	int		fd;
	char	**temp;

	if ((fd = open(file, O_RDONLY)) < 0)
		ft_put_error("Map file does not exist!", mlx);
	i = 0;
	ret = 0;
	temp = NULL;
	mlx->lines = 0;
	mlx->lines_count = get_lines_count(file);
	ft_init_vars(mlx);
	mlx->lines = get_filelines(mlx->lines, temp, fd);
	close(fd);
	while (i <= mlx->lines_count && !ret)
	{
		ret = parse_lines(mlx->lines[i], mlx);
		i++;
	}
	if (!ret)
		ft_put_error("No map included in file!", mlx);
	ft_check_vars(mlx);
	ft_read_map_2(mlx, i);
}
