#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "mlx.h"
# include "get_next_line.h"

# define MAP_WIDTH 24
# define MAP_HEIGHT 24

# define SCREEN_WIDTH mlx->window.screen_width
# define SCREEN_HEIGHT mlx->window.screen_height

# define TEXTURE_WIDTH mlx->tex.width_1
# define TEXTURE_HEIGHT mlx->tex.height_1

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

typedef struct	s_status
{
	int			res_done;
	int			floor_done;
	int			ceiling_done;
	int			sprite_done;
	int			north_done;
	int			south_done;
	int			west_done;
	int			east_done;
	int			player_done;
}				t_status;

# pragma pack(push, 1)

typedef struct		s_bitmapfile
{
	uint16_t		file_type;
	uint32_t		file_size;
	uint16_t		reserved_1;
	uint16_t		reserved_2;
	uint32_t		pixel_offset;
}					t_bitmapfile;

typedef struct		s_bitmapinfo
{
	uint32_t		header_size;
	int32_t			bmp_width;
	int32_t			bmp_height;
	uint16_t		num_planes;
	uint16_t		bits_per_pixel;
	uint32_t		compression;
	uint32_t		image_size;
	int32_t			xpixelpermeter;
	int32_t			ypixelpermeter;
	uint32_t		total_colors;
	uint32_t		important_colors;
}					t_bitmapinfo;

# pragma pack(pop)

typedef struct		s_screenshot
{
	int				width;
	int				height;
	int				bitcount;
	int				red;
	int				blue;
	int				green;
	int				width_in_bytes;
	uint32_t		imagesize;
	unsigned char	*buf;
}					t_screenshot;

typedef struct	s_mlx
{
	t_window		window;
	t_player		player;
	t_keys			keys;
	t_img			img;
	t_tex			tex;
	t_paths			path;
	t_status		status;	
	t_sprite		*sprite;
	t_screenshot	*screenshot;
	int				mapX;
	int				mapY;
	int				side;			//was it a NS or a EW wall hit;
	double			perpWallDist;
	double			rayDirX;
	double			rayDirY;
	int				lineHeight;
	int				drawStart;
	int				drawEnd;
	char			wallDir;
	char			**lines;
	int				lines_count;
	int				map_height;
	int				map_width;
	int				**world_map;
	int				*sprite_order;
	int				sprite_num;
	double			*ZBuffer;
	int				save_arg;
}				t_mlx;

int				name_checker(char *arg);
int				save_checker(char *arg);
void			ft_start_game(t_mlx *mlx, int save);
void			ft_read_map(t_mlx *mlx, char *file);
void			ft_init_vars(t_mlx *mlx);
char			**get_lines(char **lines, char *file);
int				get_lines_count();
int				parse_lines(char *line, t_mlx *mlx);
void			get_resolution(char *line, t_mlx *mlx);
void			get_sprite_path(char *line, t_mlx *mlx);
void			get_color(char *line, t_mlx *mlx, char type);
void			get_tex_path(char *line, t_mlx *mlx);
void			ft_check_vars(t_mlx *mlx);
void			verify_textures(t_mlx *mlx);
int				get_map_x(char **lines, t_mlx *mlx);
int				get_map_y(char **lines, t_mlx *mlx);
void			map_allocation(t_mlx *mlx);
void			create_map(char **lines, t_mlx *mlx);
void			player_position(t_mlx *mlx);
int				check_for_player(int x, int y, t_mlx *mlx);
void			get_player_details(char spot, int x, int y, t_mlx *mlx);
void			ft_map_checker(t_mlx *mlx);
void			check_spot(t_mlx *mlx, int x, int y);
t_sprite 	   *ft_get_sprites(t_mlx *mlx);
int 	        ft_count_sprites(t_mlx *mlx);
void			ft_screenshot(t_mlx *mlx);
t_screenshot	*ft_init_shot(t_mlx *mlx);
void			ft_screen_meta(t_mlx *mlx);
void			ft_fill_shot(t_mlx *mlx, unsigned char *buf);
void			ft_sort_sprites(t_mlx *mlx);
int				check_file(char *file_path);
void			ft_put_error(char *error, t_mlx *mlx);
int				ft_close_game(t_mlx *mlx, int ret);
void			ft_initialize(t_mlx *mlx);
int				ft_update(t_mlx *mlx);
void			ft_movement(t_mlx *mlx);
int				check_movement(int x, int y, t_mlx *mlx);
void			ft_rotation(t_mlx *mlx);
int				ft_key_pressed(int key, t_mlx *mlx);
int				ft_key_released(int key, t_mlx *mlx);
void			ft_draw_ceiling_floor(t_mlx *mlx);
void			ft_draw_walls(t_mlx *mlx);
void			ft_texture(t_mlx *mlx, int x);
void			ft_sprites(t_mlx *mlx);

#endif
