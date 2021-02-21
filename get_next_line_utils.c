/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:07:50 by asfaihi           #+#    #+#             */
/*   Updated: 2021/02/16 11:43:33 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*a;

	a = malloc(ft_strlen(s1) + 1);
	if (a == 0)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		a[i] = s1[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	str;

	i = 0;
	str = c;
	while (s[i] && s[i] != str)
		i++;
	if (s[i] == str)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	l;
	char	*a;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	if (!(a = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	i = -1;
	l = 0;
	while (s1[++i])
		a[i] = s1[i];
	while (s2[l])
		a[i++] = s2[l++];
	a[i] = '\0';
	return (a);
}
