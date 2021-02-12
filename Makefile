NAME = cub3d

SRC = cub3d.c ft_draw.c ft_map_parsing.c ft_movement.c \
		ft_player.c ft_put_error.c ft_read_file.c ft_screenshot.c \
		ft_sprites.c ft_update.c libft_functions.c libft_functions_2.c \
		get_next_line.c get_next_line_utils.c

LIBNAME = ft_cub3d.a

FLAGS = -Wall -Wextra -Werror

MLX = -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

OBJECT = $(SRC:.c=.o)

all: $(NAME)

	@gcc $(MLX) $(LIBNAME) -o $(NAME)
	@echo "Compiling game..."

$(NAME): $(OBJECT)
	ar rcs $(LIBNAME) $(OBJECT)

%.o:%.c
	gcc -c $<

clean:
	/bin/rm -f $(OBJECT)

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(LIBNAME)
	/bin/rm -f screenshot.bmp

re: fclean all