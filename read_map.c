#include "cub3d.h"

int		get_lines_count()
{
	int		fd;
	int		r;
	char	*line;
	int		count;

	count = 0;
	fd = open("./map.cub", O_RDONLY);
	while ((r = get_next_line(fd, &line)))
	{
		count++;
		free(line);
	}
	free(line);
	return (count);
}

char	**get_lines(char **lines)
{
	char	*temp;
	int		fd;
	int		r;
	int		i;
	int		j;

	i = 0;
	j = get_lines_count() + 1;
	lines = (char **)malloc(sizeof(char *) * j);
	fd = open("./map.cub", O_RDONLY);
	while ((r = get_next_line(fd, &temp)))
	{
		lines[i] = ft_strdup(temp);
		free(temp);
		i++;
	}
	lines[i] = ft_strdup(temp);
	free(temp);
	close(fd);
	return (lines);
}

void	get_tex_path(char *line, t_mlx *mlx)
{
	int		i;
	int		j;

	i = 2;
	j = 0;
	while (line[i] == ' ')
		i++;
	j = i;
	while (line[j] != ' ')
		j++;
	if (line[0] == 'N')
		mlx->path.north_path = ft_substr(line, i, j - i);
	else if (line[0] == 'S')
		mlx->path.south_path = ft_substr(line, i, j - i);
	else if (line[0] == 'W')
		mlx->path.west_path = ft_substr(line, i, j - i);
	else if (line[0] == 'E')
		mlx->path.east_path = ft_substr(line, i, j - i);
}

void	get_color(char *line, t_mlx *mlx, char type)
{
	int		i;
	int		count;
	int		color;

	i = 0;
	count = 0;
	color = 0;
	while (line[i] == ' ')
		i++;
	while (count < 3)
	{
		while (line[i] == ' ')
			i++;
		color = color * 256 + ft_atoi(line + i);
		i += ft_intsize(ft_atoi(line + i));
		if (line[i] == ',')
			i++;
		count++;
	}
	if (type == 'C')
		mlx->window.ceiling_color = color;
	else
		mlx->window.floor_color = color;
}

void	get_sprite_path(char *line, t_mlx *mlx)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (line[i] == ' ')
		i++;
	j = i;
	while (line[j] != ' ')
		j++;
	mlx->path.sprite_path = ft_substr(line, i, j - i);
	
}

void	get_resolution(char *line, t_mlx *mlx)
{
	int		i;

	i = 1;
	while (line[i] == ' ')
		i++;
	mlx->window.screen_width = ft_atoi(line + i);
	mlx->window.screen_height = ft_atoi(line + i + ft_intsize(mlx->window.screen_width));
}

void	parse_lines(char *line, t_mlx *mlx)
{
	while (*line == ' ')
		line++;
	if (*line == 'R')
		get_resolution(line, mlx);
	else if (*line == 'S' && *(line + 1) != 'O')
		get_sprite_path(line, mlx);
	else if (*line == 'C' || *line == 'F')
	{
		if (*line == 'C')
			get_color(&(*++line), mlx, 'C');
		else
			get_color(&(*++line), mlx, 'F');
	}
	else if ((*line == 'N' && *(line + 1) == 'O') || (*line == 'S' && *(line + 1) == 'O') || (*line == 'W' && *(line + 1) == 'E') || (*line == 'E' && *(line + 1) == 'A'))
		get_tex_path(line, mlx);
}

void	ft_read_map(t_mlx *mlx)
{
	char	**lines;
	int		i;

	i = 0;
	lines = get_lines(lines);
	while (i <= get_lines_count())
	{
		parse_lines(lines[i], mlx);
		i++;
	}
	
	i = 0;
	while (i <= get_lines_count())
		free(lines[i++]);
	free(lines);
}