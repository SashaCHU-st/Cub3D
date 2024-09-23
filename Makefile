NAME = cub3d

LIBFT = ./libft/libft.a

MLX42 = ./MLX42/build/libmlx42.a

SRCS = main.c \
		check_args.c \
		open.c \
		get_next_line.c \
		get_next_line_utils.c \
		textures.c \
		color.c \
		init.c \
		utils.c \
		error.c \
		check_map.c \


OBJ = $(SRCS:.c=.o)

CFLAGS =  -Wall -Wextra -Werror

MLX42FLAGS = -I include -lglfw -L"/Users/aheinane/.brew/opt/glfw/lib/"

all: ${NAME}

${NAME}: ${SRCS} $(LIBFT) $(MLX42) $(OBJ)
	cc $(CFLAGS) $(OBJ) $(LIBFT) $(MLX42) $(MLX42FLAGS) -o $(NAME)

$(LIBFT):
	make -C libft/

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
	make clean -C MLX42/build
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re