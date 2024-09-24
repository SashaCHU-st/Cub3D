/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:39:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/19 13:53:58 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* image;


int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

//char **map;
// map[0] = {1, 1, 1, 1};
// map[1] = {1, 0, 0, 1};
// map[2] = {1, 0, 0, 1};
// map[4] = {1, 1, 1, 1};

void ft_randomize(void* param)
{
	(void)param;
	int	im_height = 4;
	int	im_width = 4;
	uint32_t	color;
	int i = 0;
	int y = 0;
	int	square_count = 0;
	int min_h = (HEIGHT - im_height * 25) / 2;
	int max_h = HEIGHT - min_h;
	int min_w = (WIDTH - im_width * 25) / 2;
	int max_w = WIDTH - max_w;
	
	while (i < x || i > WIDTH - x)
	{
		if (i < x || i > WIDTH - x)
			ft_pixel(189, 155, 25, 1);
	}
	
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}	
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

// -----------------------------------------------------------------------------

int	check_args(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (i == 0)
		return (EXIT_FAILURE);
	if (str[i - 1] == 'b' && str[i - 2] == 'u' && \
		str[i - 3] == 'c' && str[i - 4] == '.' && \
		i - 4 != 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	initialise_mlx(mlx_t *mlx)
{
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		perror(mlx_strerror(mlx_errno));
		mlx_terminate(mlx);
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 128, 128)))
	{
		mlx_close_window(mlx);
		perror(mlx_strerror(mlx_errno));
		mlx_terminate(mlx);
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		perror(mlx_strerror(mlx_errno));
		mlx_terminate(mlx);
		return(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	print_er_int(char *str)
{
	printf("%s\n", str);
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	mlx_t*	mlx;

	if (argc == 2)
	{
		if (check_args(argv[1]))
			return (print_err_int("Error: Please provide a valid *.cub file."));
		open_close_file(argv);
		if (initialise_mlx(mlx))
			return (print_err_int("Error: Failed to init MLX."));
		mlx_loop_hook(mlx, ft_randomize, mlx);
		mlx_loop_hook(mlx, ft_hook, mlx);
		mlx_loop(mlx);
		mlx_terminate(mlx);
	}
	else
		return (print_err_int("Error: Please provide only a valid *.cub file."));
	return (EXIT_SUCCESS);
}
