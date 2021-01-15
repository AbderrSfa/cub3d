/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 16:38:44 by asfaihi           #+#    #+#             */
/*   Updated: 2021/01/14 10:56:22 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_intsize(long nb)
{
	int		l;

	l = 0;
	if (nb == 0)
		l++;
	if (nb < 0)
	{
		nb = -nb;
		l++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		l++;
	}
	return (l);
}

int		ft_intsize_hexa(long n)
{
	int		i;
	int		temp;
	char	buffer[20];

	i = 0;
	if (n == 0)
		i++;
	if (n < 0)
		n = n + 4294967296;
	while (n)
	{
		temp = n % 16;
		if (temp < 10)
			buffer[i++] = temp + 48;
		else
			buffer[i++] = temp + 55;
		n = n / 16;
	}
	return (i);
}

void	deci_to_hexa_lower(long n, t_set *group)
{
	int		i;
	int		temp;
	char	buffer[20];

	i = 0;
	if (n == 0)
		ft_putchar_g('0', group);
	if (n < 0)
		n = n + 4294967296;
	while (n)
	{
		temp = n % 16;
		if (temp < 10)
			buffer[i++] = temp + 48;
		else
			buffer[i++] = temp + 87;
		n = n / 16;
	}
	while (i)
		ft_putchar_g(buffer[--i], group);
}

void	deci_to_hexa_upper(long n, t_set *group)
{
	int		i;
	int		temp;
	char	buffer[20];

	i = 0;
	if (n == 0)
		ft_putchar_g('0', group);
	if (n < 0)
		n = n + 4294967296;
	while (n)
	{
		temp = n % 16;
		if (temp < 10)
			buffer[i++] = temp + 48;
		else
			buffer[i++] = temp + 55;
		n = n / 16;
	}
	while (i)
		ft_putchar_g(buffer[--i], group);
}

void	star_converter(t_set *group)
{
	if (group->width < 0)
	{
		group->left_field = 1;
		group->width = -group->width;
	}
}
