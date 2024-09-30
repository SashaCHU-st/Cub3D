/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:39:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/30 18:48:50 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double get_rgba(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

//char **map;
// map[0] = {1, 1, 1, 1};
// map[1] = {1, 0, 0, 1};
// map[2] = {1, 0, 0, 1};
// map[4] = {1, 1, 1, 1};

// void	draw_sqr(double x, double y, double color, t_cub *data)
// {
// 	double max_x = x + 32;
// 	double max_y = y + 32;
// 	double	start_x = x;

// 	while (y < max_y - 1)
// 	{
// 		x = start_x;
// 		while (x < max_x - 1)
// 		{
// 			mlx_put_pixel(data->image, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }
// // void ft_start(t_cub *data);
// // {
int   check_coord(int x, int y, int **map)
{
	printf("map here at x %d and y %d is %d\n", x / 64, y / 64, map[x / 64][y / 64]);
    return (map[x / 64][y / 64]);
}	
// // }

// void get_horizontal(t_cub *data, t_intersection *hori, double angle)
// {
// 	double	specific_x = data->play.x * 64+ 64/ 2;
// 	double	specific_y = data->play.y * 64+ 64/ 2;
// 	printf("checking the sin of the %f angle %f\n", angle, sin(angle));
// 	if (sin(angle) >= 0) //from 0/360 until 181 or facing up
// 	{
// 		hori->y = floor(specific_y / 32) * 64- 1;
// 		printf("check y %f\n", hori->y);
// 		hori->v = -32;
// 	}
// 	else
// 	{
// 		hori->y = ceil(specific_y / 32) * 64+ 32;
// 		hori->v = 32;
// 	}
// 	hori->x = specific_x + (specific_y - hori->y) / tan(angle);
// 	hori->h = 64/ tan(angle);
// 	while(!check_coord((int)hori->x, (int)hori->y, data->map))
// 	{
// 		hori->x = hori->x + hori->h;
// 		hori->y = hori->y + hori->v;
// 	}
// 	hori->dist = sqrt(pow((specific_x - hori->x), 2) + pow((specific_y - hori->y), 2));
// }
void get_horizontal(t_cub *data, t_intersection *hori, double angle)
{
	if (sin(angle) >= 0) //from 0/360 until 181 or facing up
	{
		hori->y = floor(data->play.y / 64) * 64 - 1;
		hori->v = -64;
	}
	else
	{
		hori->y = floor(data->play.y / 64) * 64 + 64;
		hori->v = 64;
	}
	hori->x = data->play.x - ((data->play.y - hori->y) / tan(angle));
	hori->h = -(64 / tan(angle));
	while(!check_coord((int)hori->x, (int)hori->y, data->map))
	{
		hori->x = hori->x + hori->h;
		hori->y = hori->y + hori->v;
	}
	hori->dist = sqrt(pow((data->play.x - hori->x), 2) + pow((data->play.y - hori->y), 2));
}

void	get_vertical(t_cub *data, t_intersection *vert, double angle)
{
	if (cos(angle) >= 0) //from 90 until 270 or facing right
	{
		vert->x = floor(data->play.x / 64) * 64 + 64;
		vert->h = 64;
	}
	else
	{
		vert->x = floor(data->play.x / 64) * 64 - 1;
		vert->h = -64;
	}
	vert->y = data->play.y - ((data->play.x - vert->x) / tan(angle));
	vert->v = 64 / tan(angle);
	while(!check_coord((int)vert->x, (int)vert->y, data->map))
	{
		vert->x = vert->x + vert->h;
		vert->y = vert->y + vert->v;
	}
	vert->dist = sqrt(pow((data->play.x - vert->x), 2) + pow((data->play.y - vert->y), 2));
}

void	get_collision(t_cub *data, t_wall *wall, double angle) //or a double pointer for wall?
{
	t_intersection hori;
	t_intersection vert;

	get_horizontal(data, &hori, angle);
	printf("hori coordinates are %f and %f\n", hori.x, hori.y);
	get_vertical(data, &vert, angle);
	if (vert.dist > hori.dist)
		wall->distance = hori.dist;
	else
		wall->distance = vert.dist;
}


void ft_draw_map(t_cub *data)
{
// 	int	c = 0;
	double	min_angl;
	double	max_angl;
	double	distance;
	double	angle;
	t_wall cur;
	int i = 0;
	int counter;

	min_angl = (data->play.angle - 60 / 2);
	max_angl = (data->play.angle + 60 / 2);
	while (i < WIDTH)
	{
		angle = (min_angl + i * ANGL_INCREM) * CONVERT; // get the cur angle until you go through all of them (depends on the width)
		printf("cur angle is %f\n", angle);
		get_collision(data, &cur, angle); //get the closest wall grid coordinates dpeending on which way the player is facing
		distance = cur.distance / cos(angle - data->play.angle); //get the distance to the wall depending on the curangle
		cur.height = HEIGHT / (distance * cos(angle)); //correction to get the fishbowl effect
		cur.start = HEIGHT / 2 - cur.height / 2; //get where the wall starts
		cur.end = HEIGHT / 2 + cur.height / 2; // get where the wall ends
		counter = 0; //technically a y or a pixel of the slice
		while (counter < HEIGHT)
		{
			if (counter >= (int) cur.start && counter <= (int)cur.end)
			{
				mlx_put_pixel(data->image, i, counter, COL_WALL);
			}
			else
				mlx_put_pixel(data->image, i, counter, COL_BACK);
			counter++;
		}
		i++;
	}
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

// void ft_hook(mlx_key_data_t keydata, void *param)
// {
// 	t_cub *data;

// 	data = (t_cub *)param;
// 	if (keydata.key == MLX_KEY_ESCAPE)
// 		mlx_close_window(data->mlx);
// 	if ((mlx_is_key_down(data->mlx, MLX_KEY_UP) || mlx_is_key_down(data->mlx, MLX_KEY_W)) && data->map[(int)data->play.x][(int)data->play.y - 1] != 1)
// 	{
// 		mlx_put_pixel(data->image, (data->play.x * 32) + (64/ 2), (data->play.y * 32) + (64/ 2), COL_BACK);
// 		data->play.y -= 1; //wont work with the angles; use the middle ray to move in accordance
// 		mlx_put_pixel(data->image, (data->play.x * 32) + (64/ 2), (data->play.y * 32) + (64/ 2), COL_WALL);
// 	}
// 	if ((mlx_is_key_down(data->mlx, MLX_KEY_DOWN) || mlx_is_key_down(data->mlx, MLX_KEY_S)) && data->map[(int)data->play.x][(int)data->play.y + 1] != 1)
// 	{
// 		mlx_put_pixel(data->image, (data->play.x * 32) + (64/ 2), (data->play.y * 32) + (64/ 2), COL_BACK);
// 		data->play.y += 1;
// 		mlx_put_pixel(data->image, (data->play.x * 32) + (64/ 2), (data->play.y * 32) + (64/ 2), COL_WALL);
// 	}
	// if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	// 	image->instances[0].y += 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	// 	image->instances[0].x -= 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	// 	image->instances[0].x += 5;
// }

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
	if (!(data->mlx = mlx_init(512, 512, "MLX42", true)))
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


void	set_the_player(t_cub *data, char c)
{
	// double	wall_x;
	// double	wall_y;


	data->play.x = 256;
	data->play.y = 256;
	if (c == 'N')
	{
		data->play.angle = 90.00;
		// wall_x = data->play.x;
		// wall_y = data->play.y * 32;
		// while (data->map[(int)wall_x][(int)wall_y / 32] != 1)
		// 	wall_y = wall_y - 64/ 2 * sin(NINETY);
		// data->play.dir_ray = (data->play.y * 64+ 64/ 2) - wall_y;
	}
	else if (c == 'S')
	{
		data->play.angle = 270.00;
		// wall_x = data->play.x;
		// wall_y = data->play.y * 32;
		// while (data->map[(int)wall_x][(int)wall_y / 32] != 1)
		// 	wall_y = wall_y + 64/ 2 * sin(TWOSEVEN);
		// data->play.dir_ray = (data->play.y * 64+ 64/ 2) + wall_y;
	}
	else if (c == 'W')
	{
		data->play.angle = 180.00;
		// wall_x = data->play.x * 32;
		// wall_y = data->play.y;
		// while (data->map[(int)wall_x / 32][(int)wall_y] != 1)
		// 	wall_x = wall_x - 64/ 2 * sin(THREESIX);
		// data->play.dir_ray = (data->play.x * 64+ 64/ 2) - wall_x;
	}
	else
	{
		data->play.angle = 360.00;
		// wall_x = data->play.x * 32;
		// wall_y = data->play.y;
		// while (data->map[(int)wall_x / 32][(int)wall_y] != 1)
		// 	wall_x = wall_x + 64/ 2 * M_PI;
		// data->play.dir_ray = (data->play.x * 64+ 64/ 2) + wall_x;
	}
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
	set_the_player(&param, 'N');
	printf("map space check %d\n", param.map[3][3]);
	if (argc == 2)
	{
		if (check_args(argv[1]))
			return (print_err_int("Error: Please provide a valid *.cub file."));
		// open_close_file(argv);
		if (initialise_mlx(&param))
			return (print_err_int("Error: Failed to init MLX."));
		// mlx_loop_hook(param.mlx, ft_randomize, &param);
		// mlx_key_hook(param.mlx, &ft_hook, &param);
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
