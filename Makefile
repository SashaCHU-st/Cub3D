NAME = cub3D

LIBFT = libft/libft.a

MLX42 = ./MLX42/build/libmlx42.a

SRCS = main.c \
		check_args.c \
		collision.c \
		open.c \
		get_next_line.c \
		get_next_line_utils.c \
		textures.c \
		color.c \
		error.c \
		check_map.c \
		map_closed.c \
		map_last.c \
		movement.c \
		if_png.c \
		utils.c \
		utils2.c \
		draw_window.c \
		color_parsing.c \
		slice.c \
		parsing_started.c \
		finilizing_map.c \
		tex_west.c \
		tex_east.c \
		tex_south.c \
		tex_north.c \
		messages.c \
		uploading_text.c \
		

OBJ = $(SRCS:.c=.o)

CFLAGS =  -Wall -Wextra -Werror

MLX42FLAGS = -lglfw -lm

$(NAME): $(MLX42) $(OBJ)
	make -C libft	
	cc $(CFLAGS) $(OBJ) $(LIBFT) $(MLX42) $(MLX42FLAGS) -o $(NAME)

all: $(NAME)

$(MLX42):
	cd MLX42 && cmake -B build
	cd MLX42 && cmake --build build -j4
	make -C MLX42/build -j4

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C libft
	make clean -C MLX42/build
	rm -f $(OBJ) 

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus