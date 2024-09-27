/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:39:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/27 19:06:37 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

//char **map;
// map[0] = {1, 1, 1, 1};
// map[1] = {1, 0, 0, 1};
// map[2] = {1, 0, 0, 1};
// map[4] = {1, 1, 1, 1};

void	draw_sqr(uint32_t x, uint32_t y, uint32_t color)
{
	uint32_t max_x = x + 32;
	uint32_t max_y = y + 32;
	uint32_t	start_x = x;

	while (y < max_y)
	{
		x = start_x;
		while (x < max_x)
		{
			mlx_put_pixel(image, x, y, color);
			x++;
		}
		y++;
	}
}

void ft_randomize(t_cub *param)
{
	int	c = 0;
	int	c_2 = 0;
	uint32_t	x;
	uint32_t y = 0;
	uint32_t	color;

	while(y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			printf("checking %d\n", param->map[c][c_2]);
			if (param->map[c][c_2] == 1)
				color = ft_pixel(61 % 0xFF, 96 % 0xFF, 71 % 0xFF, 1% 0xFF);
			else
				color = ft_pixel (199 % 0xFF, 18 % 0xFF, 94 % 0xFF, 1 % 0xFF);
			draw_sqr(x, y, color);
			x = x + 32;
			c_2++;
			if (c_2 == 8)
			{
				c_2 = 0;
				c++;
			}
		}
		y = y + 32;
	}
	// printf("check %d and %d and %d\n", param->map[1][4], image->width, image->height);
	// for (uint32_t i = 0; i < image->width; ++i)
	// {
	// 	for (uint32_t y = 0; y < image->height; ++y)
	// 	{
	// 		uint32_t color = ft_pixel(
	// 			rand() % 0xFF, // R
	// 			rand() % 0xFF, // G
	// 			rand() % 0xFF, // B
	// 			rand() % 0xFF  // A
	// 		);
	// 		mlx_put_pixel(image, i, y, color);
	// 	}
	// }	
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	printf("herehere\n");
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	// if (mlx_is_key_down(mlx, MLX_KEY_UP))
	// 	image->instances[0].y -= 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	// 	image->instances[0].y += 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	// 	image->instances[0].x -= 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	// 	image->instances[0].x += 5;
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

int	initialise_mlx(mlx_t **mlx)
{
	if (!(*mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		perror(mlx_strerror(mlx_errno));
		mlx_terminate(*mlx);
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(*mlx, 256, 256)))
	{
		mlx_close_window(*mlx);
		perror(mlx_strerror(mlx_errno));
		mlx_terminate(*mlx);
		return(EXIT_FAILURE);
	}
	// if (mlx_image_to_window(*mlx, image, 256 - (image->width / 2), 256 - (image->height / 2)) == -1)
	if (mlx_image_to_window(*mlx, image, 0, 0) == -1)
	{
		mlx_close_window(*mlx);
		perror(mlx_strerror(mlx_errno));
		mlx_terminate(*mlx);
		return(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	print_err_int(char *str)
{
	printf("%s\n", str);
	return (EXIT_FAILURE);
}

int *set_map(int i, int *map)
{
	int j = 0;

	if (i == 0 || i == 7)
	{
		while (j < 8)
			map[j++] = 1;
	}
	else
	{
		while(j < 8)
		{
			if (j == 0 || j == 7)
				map[j] = 1;
			else
				map[j] = 0;
			j++;
		}
	}
	return (map);
}

int	main(int argc, char **argv)
{
	t_cub param;
	int i = 0;

	param = (t_cub){0};
	param.map = malloc(sizeof(int *) * 8);
	if (!param.map)
		return (1);
	while (i < 8)
	{
		param.map[i] = malloc(sizeof(int) * 8);
		if (!param.map[i])
		{
			while (i != -1)
				free(param.map[i--]);
			free(param.map);
			return (1);
		}
		param.map[i] = set_map (i, param.map[i]);
		i++;
	}
	if (argc == 2)
	{
		if (check_args(argv[1]))
			return (print_err_int("Error: Please provide a valid *.cub file."));
		// open_close_file(argv);
		if (initialise_mlx(&param.mlx))
			return (print_err_int("Error: Failed to init MLX."));
		// mlx_loop_hook(param.mlx, ft_randomize, &param);
		mlx_loop_hook(param.mlx, ft_hook, param.mlx);
		ft_randomize(&param);
		mlx_loop(param.mlx);
		mlx_terminate(param.mlx);
		i = 7;
		while (i > -1)
			free(param.map[i--]);
		free(param.map);
	}
	else
		return (print_err_int("Error: Please provide only a valid *.cub file."));
	return (EXIT_SUCCESS);
}
