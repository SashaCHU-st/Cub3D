/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:39:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/28 15:01:52 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t get_rgba(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

//char **map;
// map[0] = {1, 1, 1, 1};
// map[1] = {1, 0, 0, 1};
// map[2] = {1, 0, 0, 1};
// map[4] = {1, 1, 1, 1};

void	draw_sqr(uint32_t x, uint32_t y, uint32_t color, t_cub *data)
{
	uint32_t max_x = x + 32;
	uint32_t max_y = y + 32;
	uint32_t	start_x = x;

	while (y < max_y - 1)
	{
		x = start_x;
		while (x < max_x - 1)
		{
			mlx_put_pixel(data->image, x, y, color);
			x++;
		}
		y++;
	}
}

void ft_draw_map(t_cub *data)
{
	int	c = 0;
	int	c_2 = 0;
	uint32_t	x;
	uint32_t y = 0;

	while(y < data->image->height)
	{
		x = 0;
		while (x < data->image->width)
		{
			if (data->map[c][c_2] == 1)
				draw_sqr(x, y, COL_WALL, data);
			else
				draw_sqr(x, y, COL_BACK, data);
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
	mlx_put_pixel(data->image, (data->play.x * 32) + (32 / 2), (data->play.y * 32) + (32 / 2), COL_WALL);
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

void ft_hook(mlx_key_data_t keydata, void *param)
{
	t_cub *data;

	data = (t_cub *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	if ((mlx_is_key_down(data->mlx, MLX_KEY_UP) || mlx_is_key_down(data->mlx, MLX_KEY_W)) && data->map[data->play.x][data->play.y - 1] != 1)
	{
		mlx_put_pixel(data->image, (data->play.x * 32) + (32 / 2), (data->play.y * 32) + (32 / 2), COL_BACK);
		data->play.y -= 1;
		mlx_put_pixel(data->image, (data->play.x * 32) + (32 / 2), (data->play.y * 32) + (32 / 2), COL_WALL);
	}
	if ((mlx_is_key_down(data->mlx, MLX_KEY_DOWN) || mlx_is_key_down(data->mlx, MLX_KEY_S)) && data->map[data->play.x][data->play.y + 1] != 1)
	{
		mlx_put_pixel(data->image, (data->play.x * 32) + (32 / 2), (data->play.y * 32) + (32 / 2), COL_BACK);
		data->play.y += 1;
		mlx_put_pixel(data->image, (data->play.x * 32) + (32 / 2), (data->play.y * 32) + (32 / 2), COL_WALL);
	}
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

int	initialise_mlx(t_cub *data)
{
	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		perror(mlx_strerror(mlx_errno));
		mlx_terminate(data->mlx);
		return(EXIT_FAILURE);
	}
	if (!(data->image = mlx_new_image(data->mlx, 256, 256)))
	{
		mlx_close_window(data->mlx);
		perror(mlx_strerror(mlx_errno));
		mlx_terminate(data->mlx);
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(data->mlx, data->image, (WIDTH / 2) - (data->image->width / 2), (HEIGHT / 2) - (data->image->height / 2)) == -1)
	{
		mlx_close_window(data->mlx);
		perror(mlx_strerror(mlx_errno));
		mlx_terminate(data->mlx);
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
	param.play.x = 3;
	param.play.y = 3;
	param.play.x_i = param.play.x;
	param.play.y_i = param.play.y;
	if (argc == 2)
	{
		if (check_args(argv[1]))
			return (print_err_int("Error: Please provide a valid *.cub file."));
		// open_close_file(argv);
		if (initialise_mlx(&param))
			return (print_err_int("Error: Failed to init MLX."));
		// mlx_loop_hook(param.mlx, ft_randomize, &param);
		mlx_key_hook(param.mlx, &ft_hook, &param);
		ft_draw_map(&param);
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
