/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:39:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 19:55:55 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	initialise_mlx(t_cub *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (!(data->mlx))
	{
		perror(mlx_strerror(mlx_errno));
		mlx_terminate(data->mlx);
		return (EXIT_FAILURE);
	}
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!(data->image))
	{
		mlx_close_window(data->mlx);
		perror(mlx_strerror(mlx_errno));
		mlx_terminate(data->mlx);
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		perror(mlx_strerror(mlx_errno));
		mlx_terminate(data->mlx);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_cub	param;

	param = (t_cub){0};
	param.texture = (t_textures){0};
	param.texture.play = (t_playa){0};
	param.cur = (t_wall){0};
	param.ture = (t_draw_tex){0};
	if (argc >= 2)
	{
		if (check_args(argv[1]))
			return (print_err_int("Error: Please provide a valid *.cub file."));
		open_close_file(argv, &param.texture);
		if (initialise_mlx(&param))
			return (print_err_int("Error: Failed to init MLX."));
		mlx_loop_hook(param.mlx, &ft_draw_window, &param);
		mlx_key_hook(param.mlx, &ft_hook, &param);
		mlx_loop(param.mlx);
		mlx_terminate(param.mlx);
		free_map(&param.texture);
	}
	else
		return (print_err_int \
			("Error: Please provide a *.cub file as the first argument."));
	return (EXIT_SUCCESS);
}
