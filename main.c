/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:39:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/09 18:00:30 by mspasic          ###   ########.fr       */
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
	if (check_length(x, y, data))
		return (1);
    if (data->texture.map[y / 64][x / 64] == '1')
	{
		printf("wall found at %d and %d\n", x / 64, y / 64);
		return (1);
	}
	else
	{
		printf("no wall\n");
	 	return (0);
	}
}	

void get_horizontal(t_cub *data, t_intersection *hori, double angle)
{	
	double tangens;

	tangens = tan(angle); //0/360/180 == 0; 90/180 == infinity
	printf("tangens of the angle is %f\n", tangens);
	if (sin(angle) >= 0) //from 0/360 until 181 or facing up
	{
		hori->y = floor(data->texture.play.y / 64) * 64 - 1;
		hori->v = -64;
	}
	else
	{
		hori->y = floor(data->texture.play.y / 64) * 64 + 64;
		hori->v = 64;
	}
	printf("hori->y is %f\n", hori->y);
	if (cos(angle) >= 0)
	{
		hori->x = data->texture.play.x + (fabs(data->texture.play.y - hori->y) / tan(angle));///!!!!! cannot be here 0, so no angle 90 or 0
		hori->h = 64 / tan(angle);
	}
	else
	{
		hori->x = data->texture.play.x - (fabs(data->texture.play.y - hori->y) / tan(angle));///!!!!! cannot be here 0, so no angle 90 or 0
		hori->h = -(64 / tan(angle));
	}
	printf("hori->x is %f\n", hori->x);
	while(hori->x >= 0 && hori->x < 512 && hori->y >= 0 && hori->y < 512 && !check_coord((int)hori->x, (int)hori->y, data))
	{
		hori->x = hori->x + hori->h;
		hori->y = hori->y + hori->v;
	}
	printf("hori->x and y are %f and %f\n", hori->x, hori->y);
	hori->dist = sqrt(pow((data->texture.play.x - hori->x), 2) + pow((data->texture.play.y - hori->y), 2));
}

void	get_vertical(t_cub *data, t_intersection *vert, double angle)
{
	if (cos(angle) >= 0) //from 270 to 90 or facing right
	{
		vert->x = floor(data->texture.play.x / 64) * 64 + 64;
		vert->h = 64;
	}
	else
	{
		vert->x = floor(data->texture.play.x / 64) * 64 - 1;
		vert->h = -64;
	}
	printf("vert->x is %f\n", vert->x);
	if (sin(angle) >= 0)
	{
		vert->y = data->texture.play.y - (fabs(data->texture.play.x - vert->x) / tan(angle));///!!!!! cannot be here 0
		vert->v = -(64 / tan(angle));
	}
	else
	{
		vert->y = data->texture.play.y + (fabs(data->texture.play.x - vert->x) / tan(angle));///!!!!! cannot be here 0
		vert->v = 64 / tan(angle);
	}
	printf("vert->y is %f\n", vert->y);
	while(vert->x >= 0 && vert->x < 512 && vert->y >= 0 && vert->y < 512 && !check_coord((int)vert->x, (int)vert->y, data))
	{
		vert->x = vert->x + vert->h;
		vert->y = vert->y + vert->v;
		printf("vert->y is %f\n", vert->y);
	}
	vert->dist = sqrt(pow((data->texture.play.x - vert->x), 2) + pow((data->texture.play.y - vert->y), 2));
}

void get_collision(t_cub *data, t_wall *wall, double angle) //or a double pointer for wall?
{
	t_intersection hori;
	t_intersection vert;

	vert = (t_intersection){0};
	hori = (t_intersection){0};
	//FILE *file = fopen("output.txt", "a");
	//FILE *file1 = fopen("output1.txt", "a");
	// FILE *file2 = fopen("output2.txt", "a");
	// FILE *file3 = fopen("output3.txt", "a");
	if (angle != 0 || angle != M_PI || angle != 2 * M_PI)
		get_horizontal(data, &hori, angle);
	//printf("hori coordinates are %f and %f\n", hori.x, hori.y);
	if (angle != 3 * M_PI / 2 || angle != M_PI / 2)
		get_vertical(data, &vert, angle);
	//printf( "hori coordinates are %f and %f\n", hori.x, hori.y);
	//fprintf(file1, "vert coordinates are %f and %f\n", vert.x, vert.y);
	printf("ver dist is %f\n",vert.dist);
	printf("hor dist is %f\n",hori.dist);
	// fprintf(file2, "ver dist are %f\n",vert.dist);
	// fprintf(file3, "hor dist are %f\n",hori.dist);
	if (vert.dist == 0 || (hori.dist != 0 && vert.dist > hori.dist))
	{
		wall->distance = hori.dist;
		wall->offset = (int)hori.dist % 64;
	}
	else
	{
		wall->distance = vert.dist;
		wall->offset = (int)vert.dist % 64;
	}
//	fclose(file);
}

double	get_angle(double angle, int i)
{
	double	min;
	double	cur;

	if (angle > 330)
	{
		min = 30 - (360 - angle);
	}
	else
		min = angle + 30;
	cur = min - i * ANGL_INCREM;
	printf("angle atm is %f\n", cur);
	if (cur > 360)
		cur = cur - 360;
	else if (cur < 0)
		cur = 360 + cur;
	printf("angle atm is %f\n", cur);
	return (cur * CONVERT);
}

void ft_draw_map(t_cub *data)
{
// 	int	c = 0;
	// double	distance;
	double cos_diff;
	double	angle;
	t_wall cur;
	int px_x = 0;
	int px_y;
	FILE *file = fopen("output.txt", "a");
	FILE *file2 = fopen("output2.txt", "a");
	FILE *file3 = fopen("output3.txt", "a");
	FILE *file4 = fopen("output4.txt", "a");
	FILE *file5 = fopen("output5.txt", "a");
	printf("entered ft_draw_map\n");
	printf("checking data %d, %f, %c\n", data->texture.found, data->texture.play.angle, data->texture.map[2][5]);
	while (px_x < WIDTH)
	{
		angle = get_angle(data->texture.play.angle, px_x); // get the cur angle until you go through all of them (depends on the width)
		printf("cur angle is %f\n", angle); //check if it being 0 creates issues
		get_collision(data, &cur, angle); //get the closest wall grid coordinates dpeending on which way the player is facing
		//distance = cur.distance / cos(angle - data->play.angle); //get the distance to the wall depending on the curangle
		//distance = cur.distance / cos (angle - (data->play.angle * CONVERT)); Milica
		cos_diff = cur.distance * cos(fabs(angle - (data->texture.play.angle * CONVERT)));
		// cos_diff = cos(angle - (data->texture.play.angle * CONVERT));
		if (fabs(cos_diff) < EPSILON)
			cos_diff = EPSILON;
		// //double distance_projected =64/distance*277;/// projecting as not fish eye
		// distance = cur.distance / cos_diff; 
		// if (distance > 0) 
		// 	cur.height = HEIGHT / distance; //correction to get the fishbowl effect
		// else
		// 	cur.height = fabs(HEIGHT / distance);/// or 0?
		//cur.height = HEIGHT / (distance * cos(angle)); //correction to get the fishbowl effect
		cur.height = ceil(64 / cos_diff * DIST);
		fprintf(file5, "CUR HEIGHT %d: %f\n", px_x, cur.height);
		cur.start = HEIGHT / 2 - cur.height / 2; //get where the wall starts
		cur.end = HEIGHT / 2 + cur.height / 2; // get where the wall ends
		// if (cur.start < 0)
		// 	cur.start = 0;
		// if (cur.end >= HEIGHT)
		// 	cur.end = HEIGHT - 1;
		fprintf(file3, " start %d: %f\n", px_x, cur.start);
		fprintf(file4, "end  %d: %f\n", px_x, cur.end);
		px_y = 0; //technically a y or a pixel of the slice
		while (px_y < HEIGHT)
		{
			if (px_y >= (int) cur.start && px_y <= (int)cur.end)// in th midddle hve to be the length of the wall*64
			{
				fprintf(file,"x => %d, y =>%d\n", px_x, px_y);
				mlx_put_pixel(data->image, px_x, px_y, COL_WALL);
			}
			else if(px_y <=cur.start)
			{
				fprintf(file2,"x => %d, y =>%d\n", px_x, px_y);
				mlx_put_pixel(data->image, px_x, px_y, data->texture.floor);
			}
			else if(px_y >= cur.end)
			{
				fprintf(file2,"x => %d, y =>%d\n", px_x, px_y);
				mlx_put_pixel(data->image, px_x, px_y, data->texture.ceiling);
			}
			px_y++;
		}
		px_x++;
	}
	fclose(file2);
	fclose(file);
	fclose(file3);
	fclose(file4);
	fclose(file5);
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

// int	check_args(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	if (i == 0)
// 		return (EXIT_FAILURE);
// 	if (str[i - 1] == 'b' && str[i - 2] == 'u' && \
// 		str[i - 3] == 'c' && str[i - 4] == '.' && \
// 		i - 4 != 0)
// 		return (EXIT_SUCCESS);
// 	return (EXIT_FAILURE);
// }

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

// 	return (map);
// }


int	main(int argc, char **argv)
{
	t_cub param;

	param = (t_cub){0};
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
		// mlx_loop_hook(param.mlx, ft_randomize, &param);
		// mlx_key_hook(param.mlx, &ft_hook, &param);
		ft_draw_map(&param);
		mlx_loop(param.mlx);
		mlx_terminate(param.mlx);
		// i = 7;
		// while (i > -1)
		// 	free(param.map[i--]);
		// free(param.map);
	}
	else
		return (print_err_int("Error: Please provide only a valid *.cub file."));
	return (EXIT_SUCCESS);
}
