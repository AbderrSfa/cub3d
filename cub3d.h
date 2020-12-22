#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "mlx.h"

# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;	
}				t_img;

typedef struct	s_keys
{
	int			left;
	int			right;
	int			W;
	int			S;
	int			A;
	int			D;
}       		t_keys;

typedef struct	s_mlx
{
	void    	*mlx_ptr;
	void		*win_ptr;
	double		posX;			//x start position of player
	double		posY;			//y start position of player
	double		dirX;			//x coordinate of direction
	double		dirY;			//y coordinate of direction
	double		planeX;			//x camera coordinate
	double		planeY;			//y camera coordinate
	double		moveSpeed;
	double		rotSpeed;
	t_img		img;
	t_keys		keys;
}				t_mlx;

int 	worldMap[MAP_WIDTH][MAP_HEIGHT];

void	ft_initialize(t_mlx *mlx);
int		ft_update(t_mlx *mlx);
void	ft_movement(t_mlx *mlx);
void	ft_rotation(t_mlx *mlx);
int		ft_key_pressed(int key, t_mlx *mlx);
int		ft_key_released(int key, t_mlx *mlx);
void	ft_draw_sky_floor(t_mlx *mlx);
void	ft_draw_walls(t_mlx *mlx);
void	ft_putchar(char c);
void	ft_putstr(char *s);
void	ft_putnbr(long n);

#endif
