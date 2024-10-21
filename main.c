/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:39:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/21 14:40:34 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_the_size(mlx_texture_t *from_texture, t_wall *cur)
{
	int	x;

	x = (int)(cur->hit * (double)from_texture->width);
	if ((cur->side == 'v' && cur->ray_dir.y < 0)
		|| (cur->side == 'h' && cur->ray_dir.x > 0))
		x = from_texture->width - x - 1;
	return (x);
}

void	ft_draw_map(void *param)
{
	t_cub	*data = (t_cub *)param;
	mlx_texture_t*from_texture;
	t_wall cur;
	uint32_t *pixels;
	double angle;
	int px_x = 0;
	int px_y;
	int x_o;
	double y_o_step;
	double start_tex;
	int y_o;
	unsigned int tex_y;

	while (px_x < WIDTH)
	{
		angle = get_collision(data, &cur, px_x);
		if (cur.distance == 0)
			cur.distance = EPSILON;
		cur.height = fabs((HEIGHT / cur.distance));
		cur.start = fabs(HEIGHT / 2 - cur.height / 2);
		cur.end = fabs(HEIGHT / 2 + cur.height / 2);
		from_texture = get_wall_color(cur, angle, data);
		pixels = (uint32_t *)from_texture->pixels;
		x_o = get_the_size(from_texture, &cur);
		if (cur.height == 0)
			cur.height = EPSILON;	
		y_o_step = ((double)from_texture->height / cur.height);
		px_y = 0;
		start_tex = (cur.start - HEIGHT / 2 + cur.height / 2) * y_o_step;
		y_o = (int)(start_tex) & (from_texture->height - 1);
		while (px_y < HEIGHT)
		{
			if (px_y >= cur.start && px_y <= cur.end)
			{
				y_o = (int)(start_tex) & (from_texture->height - 1);
				start_tex += y_o_step;
				tex_y = (int)(y_o * from_texture->width + x_o);
				if (tex_y < from_texture->width * from_texture->height)
					mlx_put_pixel(data->image, px_x, px_y, norm_color(pixels[tex_y]));
			}
			else
				drawing_ceil_floor(px_y, px_x, data, cur);
			px_y++;
		}
		px_x++;
	}
}

int	initialise_mlx(t_cub *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->mlx)
	{
		perror(mlx_strerror(mlx_errno));
		mlx_terminate(data->mlx);
		return (EXIT_FAILURE);
	}
	if (!data->image)
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
	if (argc == 2)
	{
		if (check_args(argv[1]))
			return (print_err_int("Error: Please provide a valid *.cub file."));
		open_close_file(argv, &param.texture);
		if (initialise_mlx(&param))
			return (print_err_int("Error: Failed to init MLX."));
		mlx_key_hook(param.mlx, &ft_hook, &param);
		mlx_loop_hook(param.mlx, &ft_draw_map, &param);
		mlx_loop(param.mlx);
		mlx_terminate(param.mlx);
		free_map(&param.texture);
	}
	else
		return (print_err_int
			("Error: Please provide only a valid *.cub file."));
	return (EXIT_SUCCESS);
}
