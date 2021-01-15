/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 16:38:39 by asfaihi           #+#    #+#             */
/*   Updated: 2021/01/14 10:55:50 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_flags(t_set *group)
{
	group->width = 0;
	group->zeroes = 0;
	group->pre_toggle = 0;
	group->precision = 0;
	group->left_field = 0;
	group->offset = 0;
	group->specifier = '\0';
}

int		struct_filler_precision(char *s, int i, va_list list)
{
	char	*a;
	int		ret;
	int		j;

	i++;
	j = i;
	while (s[i] <= '9' && s[i] >= '0')
		i++;
	a = ft_substr(s, j, i - 1);
	ret = ft_atoi(a);
	free(a);
	if (s[i] == '*')
		ret = va_arg(list, int);
	return (ret);
}

int		struct_filler_2(char *s, va_list list, t_set *group, int i)
{
	while (s[i] == '0' || s[i] == '-' || s[i] == ' ')
	{
		if (s[i] == '0')
			group->zeroes = 1;
		if (s[i] == '-')
			group->left_field = 1;
		i++;
	}
	if (s[i] == '.')
	{
		group->pre_toggle = 1;
		group->precision = struct_filler_precision(s, i, list);
		if (s[i + 1] == '*')
		{
			group->specifier = s[i + 2];
			return (i + 2);
		}
		while (s[i] != 'c' && s[i] != 'd' && s[i] != 'i' && s[i] != 'p' &&
		s[i] != 's' && s[i] != 'u' && s[i] != 'x' && s[i] != 'X' && s[i] != '%')
			i++;
		group->specifier = s[i];
		group->offset = (i + 1);
		return (i);
	}
	return (i);
}

void	struct_filler(char *s, va_list list, t_set *group)
{
	int		i;
	int		j;
	char	*a;

	i = 1;
	j = 0;
	set_flags(group);
	i = struct_filler_2(s, list, group, i);
	j = i;
	while (s[i] <= '9' && s[i] >= '0')
		i++;
	a = ft_substr(s, j, i - 1);
	group->width = ft_atoi(a);
	if (s[i] == '*')
	{
		group->width = va_arg(list, int);
		i++;
	}
	free(a);
	i = struct_filler_2(s, list, group, i);
	group->specifier = s[i];
	group->offset = (i + 1);
	return ;
}

int		ft_printf(char const *s, ...)
{
	int		i;
	va_list	list;
	char	*a;
	t_set	group;

	va_start(list, s);
	i = 0;
	group.ret = 0;
	while (s[i])
	{
		while (s[i] == '%')
		{
			struct_filler((a = ft_substr(s, i, ft_strlen(s))), list, &group);
			executer(&group, list);
			i += group.offset;
			free(a);
		}
		if (!s[i])
			break ;
		ft_putchar_g(s[i++], &group);
	}
	va_end(list);
	return (group.ret);
}
