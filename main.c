/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:39:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/14 19:45:00 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int   check_length(int x, int y, t_cub *data)
// {
// 	int	len;
// 	int strlen;

// 	len = 0;
// 	while (data->texture.map[len] != NULL)
// 		len++;
// 	if (y / 64 >= len)
// 		return (1);
// 	strlen = ft_strlen(data->texture.map[y / 64]);
// 	if (x / 64 >= strlen)
// 		return (1);
// 	return (0);	
// }

// double	get_angle(double angle, int i)
// {
// 	double	cur;
// 	double	adjust_angle;

// 	adjust_angle = 2 * (double)i / (double)WIDTH - 1;
// 	// adjust_angle = 1 - 2 * (double)i / (double)WIDTH;

// 	//printf("angle atm is %f\n", cur);
// 	return (cur * CONVERT);
// }

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
	// FILE *file = fopen("output.txt", "a");
	// FILE *file2 = fopen("output2.txt", "a");
	// FILE *file3 = fopen("output3.txt", "a");
	// FILE *file4 = fopen("output4.txt", "a");
	// FILE *file5 = fopen("output5.txt", "a");
	unsigned int from_texture; 
	cur = (t_wall){0};
	while (px_x < WIDTH)
	{
		// angle = get_angle(data->texture.play.angle, px_x); // get the cur angle until you go through all of them (depends on the width)
		// printf("cur angle is %f\n", angle);
		angle = get_collision(data, &cur, px_x); //get the closest wall grid coordinates (horizontal or vertical collision) depending on which way the player is facing
		if (cur.distance == 0)
			cur.distance = EPSILON;
		cur.height = (int)(HEIGHT / cur.distance);
		// fprintf(file5, "CUR HEIGHT %d: %d\n", px_x, cur.height);
		cur.start = HEIGHT / 2 - cur.height / 2; //get where the wall starts
		cur.end = HEIGHT / 2 + cur.height / 2; // get where the wall ends
		// fprintf(file3, " start %d: %d\n", px_x, cur.start);
		// fprintf(file4, "end  %d: %d\n", px_x, cur.end);
		px_y = 0; //technically a y or a pixel of the slice
		while (px_y < HEIGHT)
		{
			if (px_y >= (int) cur.start && px_y <= (int)cur.end)
			{
				from_texture = get_wall_color(cur, angle);
				mlx_put_pixel(data->image, px_x, px_y, from_texture);
// =======
// 				// fprintf(file,"x => %d, y =>%d\n", px_x, px_y);
// 				mlx_put_pixel(data->image, px_x, px_y, COL_WALL);
// 			}
// 			else if(px_y <=cur.start)
// 			{
// 				// fprintf(file2,"x => %d, y =>%d\n", px_x, px_y);
// 				mlx_put_pixel(data->image, px_x, px_y, data->texture.floor);
// 			}
// 			else if(px_y >= cur.end)
// 			{
// 				// fprintf(file2,"x => %d, y =>%d\n", px_x, px_y);
// 				mlx_put_pixel(data->image, px_x, px_y, data->texture.ceiling);
// >>>>>>> main
			}
			drawing_ceil_floor(px_y, px_x,data, cur);
			px_y++;
		}
		px_x++;
	}
	// fclose(file2);
	// fclose(file);
	// fclose(file3);
	// fclose(file4);
	// fclose(file5);
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
// <<<<<<< textures
// 		// param.texture.north = mlx_texture_to_image(param.mlx,param.texture.no_side);
// 		// param.texture.south = mlx_texture_to_image(param.mlx,param.texture.so_side);
// 		// param.texture.west = mlx_texture_to_image(param.mlx,param.texture.we_side);
// 		// param.texture.east = mlx_texture_to_image(param.mlx,param.texture.ea_side);
// =======
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
