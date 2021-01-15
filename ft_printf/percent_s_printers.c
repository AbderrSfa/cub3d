/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_s_printers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 16:38:30 by asfaihi           #+#    #+#             */
/*   Updated: 2021/01/14 10:58:20 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	s_zeroes_printer(int width, char *s, int precision, t_set *group)
{
	if (s == NULL)
		s = "(null)";
	if (precision > (int)ft_strlen(s) || (precision == 0 && !group->pre_toggle))
		width -= ft_strlen(s);
	else
		width -= precision;
	while (width-- > 0)
		ft_putchar_g('0', group);
}

void	s_space_printer(int width, char *s, int precision, t_set *group)
{
	if (precision > (int)ft_strlen(s) || (precision == 0 && !group->pre_toggle)
		|| group->precision < 0)
		width -= ft_strlen(s);
	else
		width -= precision;
	while (width-- > 0)
		ft_putchar_g(' ', group);
}

void	specifier_percent_s(char *s, int precision, t_set *group)
{
	int		i;

	i = 0;
	if (group->pre_toggle)
	{
		while (i < precision && i < (int)ft_strlen(s))
			ft_putchar_g(s[i++], group);
	}
	else
	{
		while (s[i])
			ft_putchar_g(s[i++], group);
	}
}

void	percent_s(t_set *group, va_list list)
{
	char	*arg;

	arg = va_arg(list, char *);
	if (arg == NULL)
		arg = "(null)";
	star_converter(group);
	if (group->precision < 0)
	{
		group->pre_toggle = 0;
		group->precision = 0;
	}
	if (group->left_field)
	{
		specifier_percent_s(arg, group->precision, group);
		s_space_printer(group->width, arg, group->precision, group);
	}
	else
	{
		if (group->zeroes && !group->left_field)
			s_zeroes_printer(group->width, arg, group->precision, group);
		else
			s_space_printer(group->width, arg, group->precision, group);
		specifier_percent_s(arg, group->precision, group);
	}
}

void	precision(t_set *group, long arg)
{
	if (arg < 0 && (group->specifier == 'd' || group->specifier == 'i'))
	{
		if (group->width && !group->left_field)
			pre_space_print(group->width, group->specifier, arg, group);
		ft_putchar_g('-', group);
		zeroes_printer(group->precision + 1, group->specifier, arg, group);
		ft_special_putnbr(arg, group);
		if (group->width && group->left_field)
			pre_space_print(group->width, group->specifier, arg, group);
	}
	else
	{
		if (group->width && !group->left_field)
			pre_space_print(group->width, group->specifier, arg, group);
		zeroes_printer(group->precision, group->specifier, arg, group);
		specifier_printer(group->specifier, arg, group);
		if (group->width && group->left_field)
			pre_space_print(group->width, group->specifier, arg, group);
	}
}
