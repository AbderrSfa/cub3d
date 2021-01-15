/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 16:39:53 by asfaihi           #+#    #+#             */
/*   Updated: 2021/01/15 12:47:43 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_PRINTF_H

# define __FT_PRINTF_H

# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

typedef struct		s_set
{
	char			specifier;
	int				width;
	int				pre_toggle;
	int				precision;
	int				zeroes;
	int				left_field;
	int				ret;
	int				offset;
}					t_set;

# define M_UI 4294967296

int					ft_atoi(const char *str);
size_t				ft_strlen(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_isdigit(int c);
void				ft_putchar(char c);
void				ft_putchar_g(char c, t_set *group);
void				ft_putstr(char *s);
void				ft_putstr_g(char *s, t_set *group);
void				ft_putnbr(long n);
void				ft_putnbr_g(long n, t_set *group);
void				ft_special_putnbr(long n, t_set *group);
int					ft_intsize(long nb);
int					ft_printf(char const *s, ...);
void				struct_filler(char *s, va_list list, t_set *group);
int					struct_filler_2(char *s, va_list list, t_set *group, int i);
int					struct_filler_precision(char *s, int i, va_list list);
void				set_flags(t_set *group);
void				executer(t_set *group, va_list list);
void				star_converter(t_set *group);
void				percent_s(t_set *group, va_list list);
void				percent_u_x(t_set *group, va_list list);
void				percent_c(t_set *group, va_list list);
void				percent_d(t_set *group, va_list list);
void				percent_p(t_set *group, va_list list);
void				percent_d_rest(t_set *group, int arg);
void				precision(t_set *group, long arg);
void				percent_p_precision(unsigned long arg, t_set *group);
void				specifier_printer(char c, long arg, t_set *group);
void				space_printer(int i, char c, long arg, t_set *group);
void				zeroes_printer(int i, char c, long arg, t_set *group);
void				pre_space_print(int width, char c, long arg, t_set *group);
void				specifier_percent_s(char *s, int precision, t_set *group);
void				s_space_printer(int width, char *s, int pre, t_set *group);
void				s_zeroes_printer(int width, char *s, int pre, t_set *group);
void				deci_to_hexa_upper(long n, t_set *group);
void				deci_to_hexa_lower(long n, t_set *group);
void				deci_to_hexa_lower_p(unsigned long n, t_set *group);
int					ft_intsize_hexa_p(unsigned long n);
void				pre_sp_print_p(int width, unsigned long arg, t_set *group);
int					ft_intsize_hexa(long n);

#endif
