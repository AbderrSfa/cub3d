/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:07:54 by asfaihi           #+#    #+#             */
/*   Updated: 2021/02/12 18:36:17 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 1

void	ft_putchar(char c);
int		ft_isdigit(int c);
void	ft_putnbr(long n);
void	*ft_memcpy(void *dst, void *src, size_t n);
void	ft_putstr(char *s);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
int		ft_intsize(long nb);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_smallest(const char *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(const char *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
int		get_line(char **string, int n, char **line, int fd);
int		get_next_line(int fd, char **line);
#endif
