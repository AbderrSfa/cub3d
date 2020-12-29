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

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

# define TEXTURE_WIDTH mlx->tex.width
# define TEXTURE_HEIGHT mlx->tex.height

# define NUM_SPRITES 19

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;

	int			size_l;
	int			bpp;
	int			endian;	
}				t_img;

typedef struct	s_tex
{
	int			*texture_data[9];

	void		*texture_1;
	void		*texture_2;
	void		*texture_3;
	void		*texture_4;
	void		*texture_5;
	void		*texture_6;
	void		*texture_7;
	void		*texture_8;
	void		*texture_9;

	int			height;
	int			width;
}				t_tex;

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			texture;
}				t_sprite;


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
	t_keys		keys;
	t_img		img;
	t_tex		tex;
}				t_mlx;

int 		worldMap[MAP_WIDTH][MAP_HEIGHT];

t_sprite	sprite[NUM_SPRITES];
double		ZBuffer[SCREEN_WIDTH];
int			spriteOrder[NUM_SPRITES];
double		spriteDistance[NUM_SPRITES];

void	sortSprites(int *order, double *dist, int amount);
void	ft_sprites(t_mlx *mlx);
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
