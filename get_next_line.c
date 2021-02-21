/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:07:52 by asfaihi           #+#    #+#             */
/*   Updated: 2021/02/16 11:52:20 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_line(char **string, int n, char **line, int fd)
{
	char	*temp;
	int		i;

	i = 0;
	while (string[fd][i] && string[fd][i] != '\n')
		i++;
	*line = ft_substr(string[fd], 0, i);
	if (!string[fd][i])
	{
		temp = string[fd];
		string[fd] = NULL;
		free(temp);
		return (0);
	}
	else
	{
		temp = string[fd];
		string[fd] = ft_strdup((string[fd]) + i + 1);
		free(temp);
	}
	if (!string[fd] || !*line)
		return (-1);
	if (n || (n == 0 && string[fd] != NULL))
		return (1);
	return (-1);
}

int		get_next_line(int fd, char **line)
{
	char			*buffer;
	static char		*string[4864];
	char			*temp;
	int				n;

	buffer = NULL;
	if (!line || fd < 0 || fd >= 4864 || BUFFER_SIZE <= 0 ||
			read(fd, buffer, 0) == -1 || !(buffer = malloc(BUFFER_SIZE + 1)))
		return (-1);
	if (!string[fd])
		if (!(string[fd] = ft_strdup("")))
			return (-1);
	while ((n = read(fd, buffer, BUFFER_SIZE)))
	{
		temp = string[fd];
		buffer[n] = '\0';
		if (!(string[fd] = ft_strjoin(string[fd], buffer)))
			return (-1);
		free(temp);
		if (ft_strchr(string[fd], '\n') != NULL)
			break ;
	}
	free(buffer);
	return (get_line(string, n, line, fd));
}
