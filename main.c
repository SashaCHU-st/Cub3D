/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:39:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/15 13:11:27 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

////////////////////////////////CDRWAING COLORS
void drawing_ceil_floor(int px_y, int px_x, t_cub *data, t_wall cur )
{
	if(px_y <=cur.start)
	{
		// fprintf(file2,"x => %d, y =>%d\n", px_x, px_y);
		mlx_put_pixel(data->image, px_x, px_y, data->texture.floor);
	}
	if(px_y >= cur.end)
	{
		// fprintf(file2,"x => %d, y =>%d\n", px_x, px_y);
		mlx_put_pixel(data->image, px_x, px_y, data->texture.ceiling);
	}
}

unsigned int get_wall_color(t_wall cur, double angle)
{
	if(cur.side == 'v')
	{
		// printf("angle %f\n", angle);
		// printf("180 %f\n",180 *CONVERT);
		if(angle > 0*CONVERT && angle < 180 *CONVERT)
		{
			//printf("NORTH\n");// green
			return(COL_WALL_NORTH);// orange
			//return(data->texture.no_side);
		}
		else
		{
		//	printf("SOUTH\n");
			return(COL_WALL_SOUTH);//green
			//return(data->texture.so_side);
		}
		
	}
	if(cur.side == 'h')
	{
		if(angle > 90*CONVERT && angle < 270 *CONVERT)
		{
		///	printf("WEST\n");
			return(COL_WALL_WEST);// light blue
		//return(data->texture.we_side);
		}
		else
		{
			///printf("EAST \n");
			return (COL_WALL_EAST); //pink
			//return(data->texture.ea_side);
		}
	}
	 return (0xFFFFFFFF); 
}


void ft_draw_map(void *param)

{
	t_cub *data;

	data = (t_cub *)param;
	double	angle;
	t_wall cur;
	int px_x = 0;
	int px_y;
	unsigned int from_texture; 
	cur = (t_wall){0};
	while (px_x < WIDTH)
	{

		angle = get_collision(data, &cur, px_x); //get the closest wall grid coordinates (horizontal or vertical collision) depending on which way the player is facing
		if (cur.distance == 0)
			cur.distance = EPSILON;
		cur.height = (int)(HEIGHT / cur.distance);
		cur.start = HEIGHT / 2 - cur.height / 2; //get where the wall starts
		cur.end = HEIGHT / 2 + cur.height / 2; // get where the wall ends
		px_y = 0; //technically a y or a pixel of the slice
		while (px_y < HEIGHT)
		{
			if (px_y >= (int) cur.start && px_y <= (int)cur.end)
			{
				from_texture = get_wall_color(cur, angle);
				mlx_put_pixel(data->image, px_x, px_y, from_texture);
			}
			drawing_ceil_floor(px_y, px_x,data, cur);
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
