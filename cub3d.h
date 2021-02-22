/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 10:43:59 by asfaihi           #+#    #+#             */
/*   Updated: 2021/02/22 15:23:40 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct		s_window
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				scr_w;
	int				scr_h;
	int				floor_color;
	int				ceiling_color;
}					t_window;

typedef struct		s_player
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	double			olddirx;
	double			oldplanex;
	double			movespeed;
	double			rotspeed;
}					t_player;

typedef struct		s_ray
{
	double			camerax;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	int				stepx;
	int				stepy;
	int				hit;
}					t_ray;

typedef struct		s_keys
{
	int				left;
	int				right;
	int				w;
	int				s;
	int				a;
	int				d;
}					t_keys;

typedef struct		s_img
{
	void			*img_ptr;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;
}					t_img;

typedef struct		s_texture
{
	double			wallx;
	int				texx;
	int				texy;
	double			step;
	double			texpos;
	int				y;
	int				color;
}					t_texture;

typedef struct		s_paths
{
	char			*spr_path;
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
}					t_paths;

typedef struct		s_tex_load
{
	int				*sp_text_data;
	void			*sp_text;
	int				sp_height;
	int				sp_width;

	int				*texture_data;
	int				height;
	int				width;

	int				*text_data_1;
	void			*text_1;
	int				height_1;
	int				width_1;

	int				*text_data_2;
	void			*text_2;
	int				height_2;
	int				width_2;

	int				*text_data_3;
	void			*text_3;
	int				height_3;
	int				width_3;

	int				*text_data_4;
	void			*text_4;
	int				height_4;
	int				width_4;
}					t_tex_load;

typedef struct		s_draw_sp
{
	double			spritex;
	double			spritey;
	double			invdet;
	double			transformx;
	double			transformy;
	int				spritescreenx;
	int				spriteheight;
	int				spritewidth;
	int				drawstartx;
	int				drawstarty;
	int				drawendx;
	int				drawendy;
	int				stripe;
	int				texx;
	int				texy;
	int				y;
	int				d;
	int				color;
}					t_draw_sp;

typedef struct		s_sprite
{
	double			x;
	double			y;
}					t_sprite;

typedef struct		s_status
{
	int				res_done;
	int				floor_done;
	int				ceiling_done;
	int				sprite_done;
	int				north_done;
	int				south_done;
	int				west_done;
	int				east_done;
	int				player_done;
}					t_status;

typedef struct		s_color
{
	int				color;
	int				commas;
}					t_color;

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

typedef struct		s_mlx
{
	t_window		window;
	t_player		player;
	t_ray			ray;
	t_keys			keys;
	t_img			img;
	t_texture		texture;
	t_paths			path;
	t_color			color;
	t_tex_load		tex_load;
	t_status		status;
	t_draw_sp		draw_sp;
	t_sprite		*sprite;
	t_screenshot	*shot;
	int				mapx;
	int				mapy;
	int				side;
	double			perpwalldist;
	double			raydirx;
	double			raydiry;
	int				lineheight;
	int				drawstart;
	int				drawend;
	char			walldir;
	char			**lines;
	int				lines_count;
	int				map_height;
	int				map_width;
	int				**world_map;
	int				*sprite_order;
	int				sprite_num;
	double			*zbuffer;
	int				save_arg;
}					t_mlx;

int					name_checker(char *arg);
int					save_checker(char *arg);
void				ft_start_game(t_mlx *mlx, int save);
void				ft_read_map(t_mlx *mlx, char *file);
void				ft_read_map_2(t_mlx *mlx, int i);
void				ft_init_vars(t_mlx *mlx);
char				**get_filelines(char **lines, char **temp, int fd);
int					get_lines_count();
int					parse_lines(char *line, t_mlx *mlx);
void				parse_color(char *line, t_mlx *mlx);
void				get_resolution(char *line, t_mlx *mlx);
void				get_sprite_path(char *line, t_mlx *mlx);
void				get_color(char *line, t_mlx *mlx, char type);
int					color_parse(char *line, int i, t_mlx *mlx);
void				get_tex_path(char *line, t_mlx *mlx);
void				north_south_path(char *line, t_mlx *mlx, int i, int j);
void				west_east_path(char *line, t_mlx *mlx, int i, int j);
void				ft_check_vars(t_mlx *mlx);
void				verify_vars(t_mlx *mlx);
int					get_map_x(char **lines, t_mlx *mlx);
int					get_map_y(char **lines);
void				map_allocation(t_mlx *mlx);
void				create_map(char **lines, t_mlx *mlx);
void				player_position(t_mlx *mlx);
int					check_for_player(int x, int y, t_mlx *mlx);
void				get_player_details(char spot, int x, int y, t_mlx *mlx);
void				set_camera_ns(char dir, t_mlx *mlx);
void				set_camera_ew(char spot, t_mlx *mlx);
void				ft_map_checker(t_mlx *mlx);
void				check_spot(t_mlx *mlx, int x, int y);
t_sprite			*ft_get_sprites(t_mlx *mlx);
int					ft_count_sprites(t_mlx *mlx);
void				ft_screenshot(t_mlx *mlx);
t_screenshot		*ft_init_shot(t_mlx *mlx);
void				ft_screen_meta(t_mlx *mlx);
void				ft_fill_shot(t_mlx *mlx, unsigned char *buf);
void				ft_sort_sprites(t_mlx *mlx);
int					check_file(char *file_path);
void				ft_put_error(char *error, t_mlx *mlx);
int					ft_close_game(t_mlx *mlx, int ret);
void				ft_initialize(t_mlx *mlx);
void				load_textures(t_mlx *mlx);
int					ft_update(t_mlx *mlx);
void				ft_movement(t_mlx *mlx);
void				ft_move_left_right(t_mlx *mlx);
int					check_movement(int x, int y, t_mlx *mlx);
void				ft_rotation(t_mlx *mlx);
void				ft_rotate_left(t_mlx *mlx);
int					ft_key_pressed(int key, t_mlx *mlx);
int					ft_key_released(int key, t_mlx *mlx);
void				ft_draw_ceiling_floor(t_mlx *mlx);
void				ft_draw_walls(t_mlx *mlx);
void				ray_step_dir(t_mlx *mlx);
void				cal_wall_distance(t_mlx *mlx);
void				ft_texture(t_mlx *mlx, int x);
void				texture_posx(t_mlx *mlx);
void				load_right_tex(t_mlx *mlx);
void				ft_sprites(t_mlx *mlx);
void				cal_sprite_size(t_mlx *mlx);
void				draw_sprite(t_mlx *mlx);

#endif
