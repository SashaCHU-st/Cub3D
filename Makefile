NAME = cub3d

LIBFT = ./libft/libft.a

MLX42 = ./MLX42/build/libmlx42.a

SRCS = main.c \
		open.c \
		


CFLAGS =  -Wall -Wextra -Werror

MLX42FLAGS = -Iinclude -lglfw -L"/Users/aheinane/.brew/opt/glfw/lib/"

all: ${NAME}

${NAME}: ${SRCS} $(LIBFT) $(MLX42)
	cc $(CFLAGS) $^ -o $@ $(LIBFT) $(MLX42) $(MLX42FLAGS)

$(LIBFT):
	make -C libft/

$(MLX42):
	cd MLX42 && cmake -B build
	cd MLX42 && cmake --build build -j4
	make -C MLX42/build -j4

clean:
	make clean -C libft
	make clean -C MLX42/build

fclean: clean
	make fclean -C libft
	make clean -C MLX42/build

re: fclean all

.PHONY: all clean fclean re