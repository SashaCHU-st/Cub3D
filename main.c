/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:39:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/18 15:53:12 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	norm_color(int c)
{
	unsigned char	bytes[4];
	int				reversed;
	unsigned char	reversed_bytes[4];

	ft_memcpy(bytes, &c, sizeof(int));
	reversed_bytes[0] = bytes[3];
	reversed_bytes[1] = bytes[2];
	reversed_bytes[2] = bytes[1];
	reversed_bytes[3] = bytes[0];
	ft_memcpy(&reversed, reversed_bytes, sizeof(int));
	return (reversed);
}

void drawing_ceil_floor(int px_y, int px_x, t_cub *data, t_wall cur )
{
	if(px_y <=cur.start)
		mlx_put_pixel(data->image, px_x, px_y, data->texture.floor);
	if(px_y >= cur.end)

		mlx_put_pixel(data->image, px_x, px_y, data->texture.ceiling);
}

mlx_texture_t *get_wall_color(t_wall cur, double angle, t_cub *data)
{
	if(cur.side == 'v')
	{
		if(angle > 0*CONVERT && angle < 180 *CONVERT)
			return(data->texture.no_side);
		else
			return(data->texture.so_side);
	}
	if(cur.side == 'h')
	{
		if(angle > 90*CONVERT && angle < 270 *CONVERT)
			return(data->texture.we_side);
		else
			return(data->texture.ea_side);
	}
	return (NULL);
}

double get_lll(mlx_texture_t *from_texture, t_wall *cur)
{
	int	x;

	//printf("hit %f\n", cur->hit);
	x = (int)(cur->hit * (double)from_texture->width);
//	printf("1 checking x of the texture %d\n", x);
	// if (x < 0 || x >= 64)
	// 	printf("this shouldnt have happened\n");
	if((cur->side == 'v' && cur->ray_dir.y < 0) || (cur->side = 'h' && cur->ray_dir.x > 0))
		// printf("this shouldnt have happened\n");
		x = from_texture->width - x - 1; //correction based on ray direction and wall orientation
	// if (x < 0)
	// 	x = 0;
	// if (x >= from_texture->width)
	// 	x = from_texture->width - 1;
			// x = (int)fmodf(cur->ray_dir.x * from_texture->width, from_texture->width);
	// else
		// x = (int)fmodf(cur->ray_dir.y * from_texture->width, from_texture->width);
	// printf("2 checking x of the texture %d\n", x);
	return(x);
}

void ft_draw_map(void *param)
{
	t_cub *data = (t_cub *)param;
	double angle;
	t_wall cur;
	int px_x = 0;
	int px_y;
	mlx_texture_t *from_texture;
	uint32_t *pixels;
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
		// printf("curdist %f\n", cur.height);
		from_texture = get_wall_color(cur, angle, data);
		pixels = (uint32_t *)from_texture->pixels;
		x_o = get_lll(from_texture, &cur);
		if (cur.height == 0)
			cur.height = EPSILON;	
		y_o_step = ((double)from_texture->height / cur.height);
		// printf("step is %f, cur.start is %d and end is %d\n", y_o_step, cur.start, cur.end);
		px_y = 0;
		start_tex = (cur.start - HEIGHT / 2 + cur.height / 2) * y_o_step;
		// printf("start is %f from %f\n", start_tex, (cur.start - HEIGHT / 2 + cur.height / 2) );
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
				// y_o += (double)from_texture->height / cur.height;
// =======
// 				from_texture = get_wall_color(cur, angle);
// 				mlx_put_pixel(data->image, px_x, px_y, from_texture);
// // =======
// // 				// fprintf(file,"x => %d, y =>%d\n", px_x, px_y);
// // 				mlx_put_pixel(data->image, px_x, px_y, COL_WALL);
// // 			}
// // 			else if(px_y <=cur.start)
// // 			{
// // 				// fprintf(file2,"x => %d, y =>%d\n", px_x, px_y);
// // 				mlx_put_pixel(data->image, px_x, px_y, data->texture.floor);
// // 			}
// // 			else if(px_y >= cur.end)
// // 			{
// // 				// fprintf(file2,"x => %d, y =>%d\n", px_x, px_y);
// // 				mlx_put_pixel(data->image, px_x, px_y, data->texture.ceiling);
// // >>>>>>> main
// >>>>>>> main
			}
			//else
			drawing_ceil_floor(px_y, px_x, data, cur);
			px_y++;
		}
		px_x++;
	}
}


int	initialise_mlx(t_cub *data)
{
	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true)))
	{
		perror(mlx_strerror(mlx_errno));
		mlx_terminate(data->mlx);
		return(EXIT_FAILURE);
	}
	if (!(data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(data->mlx);
		perror(mlx_strerror(mlx_errno));
		mlx_terminate(data->mlx);
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		perror(mlx_strerror(mlx_errno));
		mlx_terminate(data->mlx);
		return(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_cub param;

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
		return (print_err_int("Error: Please provide only a valid *.cub file."));
	return (EXIT_SUCCESS);
}
