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
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	j = i;
	while (line[j] != ' ')
		j++;
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
	else if (line[0] == 'W')
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

void	get_color(char *line, t_mlx *mlx, char type)
{
	int		i;
	int		count;
	int		color;
	int		commas;

	i = 0;
	count = 0;
	color = 0;
	commas = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (count < 3)
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (!ft_isdigit(line[i]))
			ft_put_error("Invalid color input!", mlx);
		color = color * 256 + ft_atoi(line + i);
		i += ft_intsize(ft_atoi(line + i));
		count++;
		if (count == 3)
			break;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == ',')
		{
			commas++;
			i++;
		}
	}
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (commas != 2)
		ft_put_error("Invalid color input!", mlx);
	if (line[i])
		ft_put_error("Too many color inputs!", mlx);
	if (type == 'C')
	{
		if (mlx->status.ceiling_done)
			ft_put_error("Ceiling color already defined!", mlx);
		mlx->window.ceiling_color = color;
		mlx->status.ceiling_done = 1;
	}
	else
	{
		if (mlx->status.floor_done)
			ft_put_error("Floor color already defined!", mlx);
		mlx->window.floor_color = color;
		mlx->status.floor_done = 1;
	}
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
	while (line[j] != ' ')
		j++;
	mlx->path.sprite_path = ft_substr(line, i, j - i);
	mlx->status.sprite_done = 1;
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
	mlx->window.screen_width = ft_atoi(line + i);
	i += ft_intsize(mlx->window.screen_width);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!ft_isdigit(line[i]))
		ft_put_error("Invalid resolution input!", mlx);
	mlx->window.screen_height = ft_atoi(line + i);
	i += ft_intsize(mlx->window.screen_height);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i])
		ft_put_error("Invalid resolution input!", mlx);
	mlx->status.res_done = 1;
}

void	parse_lines(char *line, t_mlx *mlx)
{
	if (*line == '\0')
		return ;
	if (*line == 'R' && *(line + 1) == ' ')
		get_resolution(line, mlx);
	else if (*line == 'S' && *(line + 1) == ' ')
		get_sprite_path(line, mlx);
	else if ((*line == 'C' && *(line + 1) == ' ') || (*line == 'F' && *(line + 1) == ' '))
	{
		if (*line == 'C')
			get_color(&(*++line), mlx, 'C');
		else
			get_color(&(*++line), mlx, 'F');
	}
	else if ((*line == 'N' && *(line + 1) == 'O' && *(line + 2) == ' ') ||
	(*line == 'S' && *(line + 1) == 'O' && *(line + 2) == ' ') ||
	(*line == 'W' && *(line + 1) == 'E' && *(line + 2) == ' ') ||
	(*line == 'E' && *(line + 1) == 'A' && *(line + 2) == ' '))
		get_tex_path(line, mlx);
	else
		ft_put_error("Invalid Identifier!", mlx);
}

void	ft_init_vars(t_mlx *mlx)
{
	mlx->status.res_done = 0;
	mlx->status.north_done = 0;
	mlx->status.south_done = 0;
	mlx->status.west_done = 0;
	mlx->status.east_done = 0;
	mlx->status.sprite_done = 0;
	mlx->status.floor_done = 0;
	mlx->status.ceiling_done = 0;
	mlx->window.screen_width = 0;
	mlx->window.screen_height = 0;
	mlx->path.north_path = NULL;
	mlx->path.south_path = NULL;
	mlx->path.west_path = NULL;
	mlx->path.east_path = NULL;
	mlx->path.sprite_path = NULL;
	mlx->window.floor_color = 0;
	mlx->window.ceiling_color = 0;
}

void	ft_read_map(t_mlx *mlx)
{
	int		i;

	i = 0;
	ft_init_vars(mlx);
	mlx->status.lines = get_lines(mlx->status.lines);
	while (i <= get_lines_count())
	{
		parse_lines(mlx->status.lines[i], mlx);
		i++;
	}
	ft_check_vars(mlx);
}