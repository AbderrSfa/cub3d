/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 16:38:42 by asfaihi           #+#    #+#             */
/*   Updated: 2021/02/11 16:24:54 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		ft_isdigit(int c)
{
	if ((c > 47 && c < 58))
		return (1);
	else
		return (0);
}

void	ft_putchar_g(char c, t_set *group)
{
	write(1, &c, 1);
	group->ret += 1;
}

void	ft_putstr_g(char *s, t_set *group)
{
	if (s == NULL)
		return ;
	while (*s)
	{
		ft_putchar_g(*s, group);
		s++;
	}
}

void	ft_putnbr_g(long n, t_set *group)
{
	long i;
	long bn;

	bn = n;
	i = 1;
	if (n == 0)
		ft_putchar_g('0', group);
	else
	{
		if (n < 0)
		{
			bn = -bn;
			ft_putchar_g('-', group);
		}
		while ((bn / (i * 10)) != 0)
			i = (i * 10);
		while (i != 0)
		{
			ft_putchar_g((bn / i) + 48, group);
			bn = (bn % i);
			i = (i / 10);
		}
	}
}

void	ft_special_putnbr(long n, t_set *group)
{
	long i;
	long bn;

	bn = n;
	i = 1;
	if (n == 0)
		ft_putchar_g('0', group);
	else
	{
		if (n < 0)
			bn = -bn;
		while ((bn / (i * 10)) != 0)
			i = (i * 10);
		while (i != 0)
		{
			ft_putchar_g((bn / i) + 48, group);
			bn = (bn % i);
			i = (i / 10);
		}
	}
}

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	size_t			i;
	unsigned char	*x;
	unsigned char	*y;

	x = src;
	y = dst;
	i = 0;
	if (src == dst)
		return (dst);
	if ((dst == NULL) && (src == NULL))
		return (NULL);
	while (i < n)
	{
		y[i] = x[i];
		i++;
	}
	return (y);
}