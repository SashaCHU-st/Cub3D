NAME = cub3d

LIBFT = ./libft/libft.a

MLX42 = ./MLX42/build/libmlx42.a

# HEADER = ./cub3d.h

SRCS = main.c 
		# open.c \
		# get_next_line.c \
		# get_next_line_utils.c \

OBJ = $(SRCS:.c=.o)

CFLAGS =  -Wall -Wextra -Werror -fsanitize=address -g

MLX42FLAGS = -lglfw -lm

all: ${NAME}

${NAME}: $(LIBFT) $(MLX42) $(OBJ)
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
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re