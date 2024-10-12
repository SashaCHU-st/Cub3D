/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:39:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/12 17:17:15 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t get_rgba(int r, int g, int b)
{
    return ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | 255;
}

int   check_length(int x, int y, t_cub *data)
{
	int	len;
	int strlen;

	len = 0;
	while (data->texture.map[len] != NULL)
		len++;
	if (y / 64 >= len)
		return (1);
	strlen = ft_strlen(data->texture.map[y / 64]);
	if (x / 64 >= strlen)
		return (1);
	return (0);	
}


int   check_coord(int x, int y, t_cub *data)
{
	// if (check_length(x, y, data))
	// 	return (1); //not needed because it always finds a wall eventually
    if (data->texture.map[y][x] == '1')
	{
		// printf("wall found at %d and %d\n", x, y);
		return (1);
	}
	else
	{
		// printf("no wall\n");
	 	return (0);
	}
}	

void set_hori(t_cub *data, t_collision *cur, t_wall *wall)
{	
	//calculate how much you need to iterate by to get from one x/y coordinate to the next one
	if (wall->ray_dir.x == 0)
		cur->iterate.x = 1e30; //to avoid dividing by 0
	else
		cur->iterate.x = fabs(1 / wall->ray_dir.x); //to get the first x coordinate
	// printf("iterate delta is %f\n", cur->iterate.x);
	if (wall->ray_dir.x < 0) //the angle goes left
	{
		cur->hori.step = -1;
		cur->hori.dot = (data->texture.play.x - wall->map.x) * cur->iterate.x;
	}
	else
	{
		cur->hori.step = 1;
		cur->hori.dot = (-data->texture.play.x + wall->map.x + 1) * cur->iterate.x;
	}
	// printf("dot is %f\n", cur->hori.dot);
}

void set_vert(t_cub *data, t_collision *cur, t_wall *wall)
{
	if (wall->ray_dir.y == 0)
		cur->iterate.y = 1e30; //to avoid dividing by 0
	else
		cur->iterate.y = fabs(1 / wall->ray_dir.y); //to get the first y coordinate
	if (wall->ray_dir.y < 0) //the angle goes left
	{
		cur->vert.step = -1;
		cur->vert.dot = (data->texture.play.y - wall->map.y) * cur->iterate.y;
	}
	else
	{
		cur->vert.step = 1;
		cur->vert.dot = (-data->texture.play.y + wall->map.y + 1) * cur->iterate.y;
	}
}

void	do_dda(t_cub *data, t_collision *cur, t_wall *wall)
{
	// printf("cur coordinates are %d and %d\n", (int)wall->map.x, (int)wall->map.y);
	while (!(check_coord((int)wall->map.x, (int)wall->map.y, data)))
	{
		if (cur->hori.dot < cur->vert.dot)
		{
			cur->hori.dot += cur->iterate.x;
			wall->map.x += cur->hori.step;
			wall->side = 'h';
		}
		else
		{
			cur->vert.dot += cur->iterate.y;
			wall->map.y += cur->vert.step;
			wall->side = 'v';
		}
		// printf("cur coordinates are %d and %d\n", (int)wall->map.x, (int)wall->map.y);
	}
}

/*setting the wall variables values and adjusting the FOV for the fishbowl effect*/

void	set_wall(t_cub *data, t_wall *wall, double angle, int i)
{
	double	adjust_angle;

	adjust_angle = 2 * (double)i / (double)WIDTH - 1;
	wall->map.x = (int)data->texture.play.x;
	wall->map.y = (int)data->texture.play.y;
	// printf("wall starting position are x and y %f and %f\n", wall->map.x, wall->map.y);
	//calculate the direction of the ray on x and y axis
	wall->dir.x = cos(angle); //check if 0
	wall->dir.y = sin(angle);//check if 0
	wall->camera.x = -(wall->dir.y) * PLANE;
	wall->camera.y = wall->dir.x * PLANE;
	wall->ray_dir.x = wall->dir.x + wall->camera.x * adjust_angle;
	wall->ray_dir.y = wall->dir.y + wall->camera.y * adjust_angle;
}

void get_collision(t_cub *data, t_wall *wall, double angle, int px_x) //or a double pointer for wall?
{
	t_collision	cur;

	cur.vert = (t_intersection){0};
	cur.hori = (t_intersection){0};
	//FILE *file = fopen("output.txt", "a");
	//FILE *file1 = fopen("output1.txt", "a");
	// FILE *file2 = fopen("output2.txt", "a");
	// FILE *file3 = fopen("output3.txt", "a");
	set_wall(data, wall, angle, px_x);
	// printf("wall direction angles are x and y %f and %f\n", wall->dir.x, wall->dir.y);
	set_hori(data, &cur, wall);
	set_vert(data, &cur, wall);
	// printf("checking hori %f and vert %f\n", cur.hori.dot, cur.vert.dot);
	do_dda(data, &cur, wall);
	//account for the fishbowl effect
	if (wall->side == 'h')
	{
		if (wall->ray_dir.x == 0)
			wall->distance = (wall->map.x - data->texture.play.x + (1 - cur.hori.step) / 2) / EPSILON;
		else
			wall->distance = (wall->map.x - data->texture.play.x + (1 - cur.hori.step) / 2) / wall->ray_dir.x;
	}
	else
	{
		if (wall->ray_dir.y == 0)
			wall->distance = (wall->map.y - data->texture.play.y + (1 - cur.vert.step) / 2) / EPSILON;
		else
			wall->distance = (wall->map.y - data->texture.play.y + (1 - cur.vert.step) / 2) / wall->ray_dir.y;
	}
	// printf("WALL DISTANCE FOR ANGLE %f IS %f\n", angle, wall->distance);
//	fclose(file);
}

/*get the current angle of the ray using the player's current angle of direction and 30 (field of view / 2) and screen width and cur_pixel_x*/
double	get_angle(double angle, int i)
{
	double	cur;
	double	adjust_angle;

	adjust_angle = 2 * (double)i / (double)WIDTH - 1;
	// adjust_angle = 1 - 2 * (double)i / (double)WIDTH;
	cur = angle + (30 * CONVERT) * adjust_angle; //the range of the camera view is -1 to 1 and this translates it to that
	// printf("angle atm is %f\n", cur);
	return (cur * CONVERT);
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
	
	cur = (t_wall){0};
	while (px_x < WIDTH)
	{
		angle = get_angle(data->texture.play.angle, px_x); // get the cur angle until you go through all of them (depends on the width)
		// printf("cur angle is %f\n", angle);
		get_collision(data, &cur, angle, px_x); //get the closest wall grid coordinates (horizontal or vertical collision) depending on which way the player is facing
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
				// fprintf(file,"x => %d, y =>%d\n", px_x, px_y);
				mlx_put_pixel(data->image, px_x, px_y, COL_WALL);
			}
			else if(px_y <=cur.start)
			{
				// fprintf(file2,"x => %d, y =>%d\n", px_x, px_y);
				mlx_put_pixel(data->image, px_x, px_y, data->texture.floor);
			}
			else if(px_y >= cur.end)
			{
				// fprintf(file2,"x => %d, y =>%d\n", px_x, px_y);
				mlx_put_pixel(data->image, px_x, px_y, data->texture.ceiling);
			}
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

// 	int	c_2 = 0;
// 	double	x;
// 	double y = 0;

// 	while(y < data->image->height)
// 	{
// 		x = 0;
// 		while (x < data->image->width)
// 		{
// 			if (data->map[c][c_2] == 1)
// 				draw_sqr(x, y, COL_WALL, data);
// 			else
// 				draw_sqr(x, y, COL_BACK, data);
// 			x = x + 32;
// 			c_2++;
// 			if (c_2 == 8)
// 			{
// 				c_2 = 0;
// 				c++;
// 			}
// 		}
// 		y = y + 32;
// 	}
	// mlx_put_pixel(data->image, (data->play.x * 32) + (64/ 2), (data->play.y * 32) + (64/ 2), COL_WALL);
	// printf("check %d and %d and %d\n", param->map[1][4], image->width, image->height);
	// for (double i = 0; i < image->width; ++i)
	// {
	// 	for (double y = 0; y < image->height; ++y)
	// 	{
	// 		double color = ft_pixel(
	// 			rand() % 0xFF, // R
	// 			rand() % 0xFF, // G
	// 			rand() % 0xFF, // B
	// 			rand() % 0xFF  // A
	// 		);
	// 		mlx_put_pixel(image, i, y, color);
	// 	}
	// }	
// }

void	ft_move_up(t_cub *data)
{
	t_collision move;
	t_vector	angle;

	angle.x = cos(data->texture.play.angle * CONVERT);
	angle.y = sin(data->texture.play.angle * CONVERT);
	// if (angle.x== 0)
	// 	move.iterate.x = 1e30; //to avoid dividing by 0
	// else
	// 	move.iterate.x = fabs(1 / angle.x); //to get the first x coordinate
	// printf("iterate delta is %f\n", cur->iterate.x);
	if (angle.x < 0) //the angle goes left
		move.hori.step = -1;
	else
		move.hori.step = 1;
	// if (angle.y == 0)
	// 	move.iterate.y = 1e30; //to avoid dividing by 0
	// else
	// 	move.iterate.y = fabs(1 / angle.x); //to get the first x coordinate
	// printf("iterate delta is %f\n", cur->iterate.x);
	if (angle.y < 0) //the angle goes left
		move.vert.step = -1;
	else
		move.vert.step = 1;
	printf("initial %d and %d\n", (int)data->texture.play.x, (int)data->texture.play.y);
	printf("should be %d and %d\n", (int)(data->texture.play.x + move.hori.step), (int)(data->texture.play.y + move.vert.step));
	printf("check coord %d\n",check_coord((int)(data->texture.play.x + move.hori.step), (int)(data->texture.play.y + move.vert.step), data));
	if (check_coord((int)(data->texture.play.x + move.hori.step), (int)(data->texture.play.y + move.vert.step), data) == 0)
	{
		printf("condition met\n");
		data->texture.play.x += move.hori.step;
		data->texture.play.y += move.vert.step;
	}
	printf("updated %d and %d\n", (int)data->texture.play.x, (int)data->texture.play.y);
}

void ft_hook(mlx_key_data_t keydata, void *param)
{
	t_cub *data;

	data = (t_cub *)param;
	printf("entered ft_hook\n");
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	// if ((mlx_is_key_down(data->mlx, MLX_KEY_UP) || mlx_is_key_down(data->mlx, MLX_KEY_W)))
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		ft_move_up(data);
	// if ((mlx_is_key_down(data->mlx, MLX_KEY_DOWN) || mlx_is_key_down(data->mlx, MLX_KEY_S)) && data->map[(int)data->play.x][(int)data->play.y + 1] != 1)
	// {
	// 	mlx_put_pixel(data->image, (data->play.x * 32) + (64/ 2), (data->play.y * 32) + (64/ 2), COL_BACK);
	// 	data->play.y += 1;
	// 	mlx_put_pixel(data->image, (data->play.x * 32) + (64/ 2), (data->play.y * 32) + (64/ 2), COL_WALL);
	// }
	// if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	// 	image->instances[0].y += 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	// 	image->instances[0].x -= 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	// 	image->instances[0].x += 5;
}

// -----------------------------------------------------------------------------


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

int	print_err_int(char *str)
{
	printf("%s\n", str);
	return (EXIT_FAILURE);
}

// int *set_map(int i, int *map)
// {
// 	int j = 0;

// 	if (i == 0 || i == 7)
// 	{
// 		while (j < 8)
// 			map[j++] = 1;
// 	}
// 	else
// 	{
// 		while(j < 8)
// 		{
// 			if (j == 0 || j == 7)
// 				map[j] = 1;
// 			else
// 				map[j] = 0;
// 			j++;
// 		}
// 	}


int	main(int argc, char **argv)
{
	t_cub param;

	param = (t_cub){0};

// 	param.map = malloc(sizeof(int *) * 8);
// 	if (!param.map)
// 		return (1);
// 	while (i < 8)
// 	{
// 		param.map[i] = malloc(sizeof(int) * 8);
// 		if (!param.map[i])
// 		{
// 			while (i != -1)
// 				free(param.map[i--]);
// 			free(param.map);
// 			return (1);
// 		}
// 		param.map[i] = set_map (i, param.map[i]);
// 		i++;
// 	}
	param.texture = (t_textures){0};
	param.texture.play = (t_playa){0};
	// printf("check if set: param %zu, text %d, play %f\n", param.size, param.texture.found, param.texture.play.angle);
	// param.map = malloc(sizeof(int *) * 8);
	// if (!param.map)
	// 	return (1);
	// while (i < 8)
	// {
	// 	param.map[i] = malloc(sizeof(int) * 8);
	// 	if (!param.map[i])
	// 	{
	// 		while (i != -1)
	// 			free(param.map[i--]);
	// 		free(param.map);
	// 		return (1);
	// 	}
	// 	param.map[i] = set_map (i, param.map[i]);
	// 	i++;
	// }
	// printf("map space check %d\n", param.map[3][3]);
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
// 		while (i < param.texture.how_many_lines)
// 		{
// 			free(param.texture.map[i]);
// 			i++;
// 		}
// 		free(param.texture.map);
// 		free(param.texture.no);
// 		free(param.texture.so);
// 		free(param.texture.ea);
// 		free(param.texture.we);
// 		free(param.texture.floor_color);
// 		free(param.texture.ceiling_color);
	}
	else
		return (print_err_int("Error: Please provide only a valid *.cub file."));
	return (EXIT_SUCCESS);
}
