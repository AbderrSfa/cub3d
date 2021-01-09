#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "mlx.h"
# include "get_next_line/get_next_line.h"

# define MAP_WIDTH 24
# define MAP_HEIGHT 24

# define SCREEN_WIDTH mlx->window.screen_width
# define SCREEN_HEIGHT mlx->window.screen_height

# define TEXTURE_WIDTH mlx->tex.width_1
# define TEXTURE_HEIGHT mlx->tex.height_1

# define NUM_SPRITES 19

typedef struct	s_window
{
	void    	*mlx_ptr;
	void		*win_ptr;
	int			screen_width;
	int			screen_height;
	int			floor_color;
	int			ceiling_color;
}				t_window;

typedef struct	s_player
{
	double		posX;			//x start position of player
	double		posY;			//y start position of player
	double		dirX;			//x coordinate of direction
	double		dirY;			//y coordinate of direction
	double		planeX;			//x camera coordinate
	double		planeY;			//y camera coordinate
	double		moveSpeed;
	double		rotSpeed;
}				t_player;

typedef struct	s_keys
{
	int			left;
	int			right;
	int			W;
	int			S;
	int			A;
	int			D;
}       		t_keys;

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;

	int			size_l;
	int			bpp;
	int			endian;	
}				t_img;

typedef struct	s_paths
{
	char		*sprite_path;
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
}				t_paths;

typedef struct	s_tex
{
	int			*sp_texture_data;
	void		*sp_texture;
	int			sp_height;
	int			sp_width;

	int			*texture_data;
	int			height;
	int			width;

	//int			*texture_data[4];

	int			*texture_data_1;
	void		*texture_1;
	int			height_1;
	int			width_1;

	int			*texture_data_2;
	void		*texture_2;
	int			height_2;
	int			width_2;

	int			*texture_data_3;
	void		*texture_3;
	int			height_3;
	int			width_3;

	int			*texture_data_4;
	void		*texture_4;
	int			height_4;
	int			width_4;
}				t_tex;

typedef struct	s_sprite
{
	double		x;
	double		y;
}				t_sprite;

typedef struct	s_mlx
{
	int			mapX;
	int			mapY;
	int			side;			//was it a NS or a EW wall hit;
	double		perpWallDist;
	double		rayDirX;
	double		rayDirY;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	char		wallDir;
	t_window	window;
	t_player	player;
	t_keys		keys;
	t_img		img;
	t_tex		tex;
	t_paths		path;
}				t_mlx;

int 			worldMap[MAP_WIDTH][MAP_HEIGHT];

t_sprite		sprite[NUM_SPRITES];
double			ZBuffer[1280];
int				spriteOrder[NUM_SPRITES];
double			spriteDistance[NUM_SPRITES];

void			ft_start_game(t_mlx *mlx);
void			ft_read_map(t_mlx *mlx);
void			ft_initialize(t_mlx *mlx);
int				ft_update(t_mlx *mlx);
void			ft_movement(t_mlx *mlx);
void			ft_rotation(t_mlx *mlx);
int				ft_key_pressed(int key, t_mlx *mlx);
int				ft_key_released(int key, t_mlx *mlx);
void			ft_draw_ceiling_floor(t_mlx *mlx);
void			ft_draw_walls(t_mlx *mlx);
void			ft_texture(t_mlx *mlx, int x);
//void			sortSprites(int *order, double *dist, int amount);
void			ft_sprites(t_mlx *mlx);
void			ft_putchar(char c);
void			ft_putstr(char *s);
void			ft_putnbr(long n);

#endif
