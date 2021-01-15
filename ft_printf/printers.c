/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 16:38:37 by asfaihi           #+#    #+#             */
/*   Updated: 2021/01/14 12:19:25 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pre_space_print(int width, char c, long arg, t_set *group)
{
	int		precision;

	precision = group->precision;
	if ((c == 'x' || c == 'X') && arg)
	{
		if (precision < ft_intsize_hexa(arg))
			width -= ft_intsize_hexa(arg);
		else
			width -= precision;
	}
	else if (c == 'u' && arg < 0 && (precision <= ft_intsize(arg + M_UI)))
		width -= ft_intsize(arg + M_UI);
	else
	{
		if (precision < ft_intsize(arg) && arg)
			width -= ft_intsize(arg);
		else
			width -= precision;
	}
	if ((c == 'd' || c == 'i') && arg < 0 && precision >= ft_intsize(arg))
		width--;
	while (width-- > 0)
		ft_putchar_g(' ', group);
}

void	zeroes_printer(int i, char c, long arg, t_set *group)
{
	if (c == 'c' || c == '%')
		i--;
	else if (c == 'd' || c == 'i')
		i -= ft_intsize(arg);
	else if (c == 'x' || c == 'X')
		i -= ft_intsize_hexa(arg);
	else if (c == 'p')
	{
		ft_putstr_g("0x", group);
		if (i > ft_intsize_hexa_p(arg) && group->pre_toggle)
			i -= ft_intsize_hexa_p(arg);
		else
			i -= ft_intsize_hexa_p(arg) + 2;
	}
	else if (c == 'u')
	{
		if (arg >= 0)
			i -= ft_intsize(arg);
		else
			i -= ft_intsize(arg + M_UI);
	}
	while (i-- > 0)
		ft_putchar_g('0', group);
}

void	space_printer(int i, char c, long arg, t_set *group)
{
	if (c == 'c' || c == '%')
		i--;
	else if (c == 'd' || c == 'i')
		i -= ft_intsize(arg);
	else if (c == 'x' || c == 'X')
		i -= ft_intsize_hexa(arg);
	else if (c == 'p')
		i -= ft_intsize_hexa_p(arg) + 2;
	else if (c == 'u')
	{
		if (arg >= 0)
			i -= ft_intsize(arg);
		else
			i -= ft_intsize(arg + M_UI);
	}
	while (i-- > 0)
		ft_putchar_g(' ', group);
}

void	specifier_printer(char c, long arg, t_set *group)
{
	if (c != '%' && c != 'c' && group->pre_toggle && !group->precision && !arg)
		return ;
	if (c == 'c')
		ft_putchar_g(arg, group);
	else if (c == 'd' || c == 'i')
		ft_putnbr_g(arg, group);
	else if (c == 'u')
	{
		if (arg > 0 || arg == 0)
			ft_putnbr_g(arg, group);
		else
			ft_putnbr_g(arg + M_UI, group);
	}
	else if (c == 'p')
	{
		deci_to_hexa_lower_p(arg, group);
	}
	else if (c == '%')
		ft_putchar_g('%', group);
	else if (c == 'x')
		deci_to_hexa_lower(arg, group);
	else if (c == 'X')
		deci_to_hexa_upper(arg, group);
}

void	executer(t_set *group, va_list list)
{
	if (group->specifier == 'c' || group->specifier == '%')
		percent_c(group, list);
	else if (group->specifier == 's')
		percent_s(group, list);
	else if (group->specifier == 'p')
		percent_p(group, list);
	else if (group->specifier == 'd' || group->specifier == 'i')
		percent_d(group, list);
	else if (group->specifier == 'X' || group->specifier == 'x' ||
			group->specifier == 'u')
		percent_u_x(group, list);
}
