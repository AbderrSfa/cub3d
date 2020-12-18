#include "cub3d.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	if (s == NULL)
		return ;
	while (*s)
	{
		ft_putchar(*s);
		s++;
	}
}

void	ft_putnbr(long n)
{
	long i;
	long bn;

	bn = n;
	i = 1;
	if (n == 0)
		ft_putchar('0');
	else
	{
		if (n < 0)
		{
			bn = -bn;
			ft_putchar('-');
		}
		while ((bn / (i * 10)) != 0)
			i = (i * 10);
		while (i != 0)
		{
			ft_putchar((bn / i) + 48);
			bn = (bn % i);
			i = (i / 10);
		}
	}
}