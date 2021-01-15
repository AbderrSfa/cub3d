/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:07:54 by asfaihi           #+#    #+#             */
/*   Updated: 2021/01/15 11:47:49 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "../ft_printf/ft_printf.h"

# define BUFFER_SIZE 1

char	*ft_strdup(const char *s1);
char	*ft_strjoin(const char *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
int		get_line(char **string, int n, char **line, int fd);
int		get_next_line(int fd, char **line);
#endif
