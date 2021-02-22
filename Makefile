NAME = cub3d

SRC = cub3d.c check_args.c ft_draw_walls.c ft_map_parsing.c ft_movement.c \
		ft_player.c ft_put_error.c ft_read_file.c ft_rotation.c ft_screenshot.c \
		ft_sprites.c ft_texture.c ft_update.c get_map_size.c libft_functions.c libft_functions_2.c \
		get_next_line.c get_next_line_utils.c parse_color.c parse_params.c

LIBNAME = ft_cub3d.a

FLAGS = -Wall -Wextra -Werror

MLX = -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

OBJECT = $(SRC:.c=.o)

all: $(NAME)
	

$(NAME): $(OBJECT)
	@ar rcs $(LIBNAME) $(OBJECT)
	@gcc $(MLX) $(LIBNAME) -o $(NAME)
	@echo "\033[34m[Compiling is done !]"

%.o:%.c
	@gcc $(FLAGS) -c $<

clean:
	@echo "\033[31m[Removing Files ...!]\033[0m"
	/bin/rm -f $(OBJECT)

fclean: clean
	@echo "\033[31m[Removing Cub3D ...!]\033[0m"
	/bin/rm -f $(NAME)
	/bin/rm -f $(LIBNAME)
	@echo "\033[31m[Deleting Old Screenshot...!]\033[0m"
	/bin/rm -f screenshot.bmp

re: fclean all