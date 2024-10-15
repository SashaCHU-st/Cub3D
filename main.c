/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:39:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/15 09:34:44 by aheinane         ###   ########.fr       */
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
		return (1);
	}
	else
	{
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
	}
}

/*setting the wall variables values and adjusting the FOV for the fishbowl effect*/

void	set_wall(t_cub *data, t_wall *wall, double angle, int i)
{
	double	adjust_angle;

	adjust_angle = 2 * (double)i / (double)WIDTH - 1;
	wall->map.x = (int)data->texture.play.x;
	wall->map.y = (int)data->texture.play.y;
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

	//printf("angle atm is %f\n", cur);
	return (cur * CONVERT);
}

// double get_lll(mlx_texture_t *texture, t_wall *cur)
// {
// 	double x;
// 	if(cur->side == 'h')
// 	{
// 		x = (int)fmodf(cur->ray_dir.y * texture->width, texture->width);
// 	}
// 	else
// 		x = (int)fmodf(cur->ray_dir.x*texture->width, texture->width);
// 	return(x);
// }


// void ft_draw_map(void *param)

// {
// 	t_cub *data;

// 	data = (t_cub *)param;
// 	double	angle;
// 	t_wall cur;
// 	int px_x = 0;
// 	int px_y;
// 	uint32_t		*pixels;
// 	mlx_texture_t *from_texture;
// 	double			x_o;
// 	double			y_o;
// 	int				tex_y;
// 	cur = (t_wall){0};
// 	while (px_x < WIDTH)
// 	{
// 		angle = get_angle(data->texture.play.angle, px_x); // get the cur angle until you go through all of them (depends on the width)
// 		// printf("cur angle is %f\n", angle);
// 		get_collision(data, &cur, angle, px_x); //get the closest wall grid coordinates (horizontal or vertical collision) depending on which way the player is facing
// 		if (cur.distance == 0)
// 			cur.distance = EPSILON;
// 		cur.height = (int)(HEIGHT / cur.distance);
// 		cur.start = HEIGHT / 2 - cur.height / 2; //get where the wall starts
// 		cur.end = HEIGHT / 2 + cur.height / 2; // get where the wall ends
// 		px_y = 0; //technically a y or a pixel of the slice
// 		while (px_y < HEIGHT)
// 		{
// 			if (px_y >= (int) cur.start && px_y <= (int)cur.end)
// 			{
// 				from_texture = get_wall_color(cur,angle, data);
// 				pixels = (uint32_t *)from_texture->pixels;
// 				x_o = get_lll(from_texture,&cur );
// 				y_o = ((int)cur.start - HEIGHT/2) + (((int)cur.end-(int)cur.start)/2) * (double)from_texture->height/((int)cur.end- (int)cur.start);
// 				if (y_o < 0)
// 					y_o = 0;
// 				tex_y = (int)y_o*from_texture->width + (int)x_o;
// 				if (tex_y < 0)
// 					return ;
// 				mlx_put_pixel(data->image, px_x, px_y, norm_color(pixels[tex_y]));
// 				y_o += (double)from_texture->height/((int)cur.end- (int)cur.start);
// 			}
// 			drawing_ceil_floor(px_y, px_x,data, cur);
// 			px_y++;
// 		}
// 		px_x++;
// 	}
// }


///////////////////////////////////SOMEHOW WORKING WITH TEXTURES BUT NOT CORRECT

// void drawing_ceil_floor(int px_y, int px_x, t_cub *data, t_wall cur )
// {
// 	if(px_y <=cur.start)
// 	{
// 		// fprintf(file2,"x => %d, y =>%d\n", px_x, px_y);
// 		mlx_put_pixel(data->image, px_x, px_y, data->texture.floor);
// 	}
// 	if(px_y >= cur.end)
// 	{
// 		// fprintf(file2,"x => %d, y =>%d\n", px_x, px_y);
// 		mlx_put_pixel(data->image, px_x, px_y, data->texture.ceiling);
// 	}
// }

// mlx_texture_t *get_wall_color(t_wall cur, double angle, t_cub *data)
// {
// 	if(cur.side == 'v')
// 	{
// 		if(angle > 0*CONVERT && angle < 180 *CONVERT)
// 		{
// 			//printf("NORTH\n");// green
// 			//return(COL_WALL_NORTH);// orange
// 			return(data->texture.no_side);
// 		}
// 		else
// 		{
// 		//	printf("SOUTH\n");
// 			//return(COL_WALL_SOUTH);//green
// 		return(data->texture.so_side);
// 		}
		
// 	}
// 	if(cur.side == 'h')
// 	{
// 		if(angle > 90*CONVERT && angle < 270 *CONVERT)
// 		{
// 		///	printf("WEST\n");
// 			//return(COL_WALL_WEST);// light blue
// 			return(data->texture.we_side);
// 		}
// 		else
// 		{
// 			///printf("EAST \n");
// 			//return (COL_WALL_EAST); //pink
// 			return(data->texture.ea_side);
// 		}
// 	}
// 	return(NULL);
// }


// int	norm_color(int c)
// {
// 	unsigned char	bytes[4];
// 	int				reversed;
// 	unsigned char	reversed_bytes[4];

// 	ft_memcpy(bytes, &c, sizeof(int));
// 	reversed_bytes[0] = bytes[3];
// 	reversed_bytes[1] = bytes[2];
// 	reversed_bytes[2] = bytes[1];
// 	reversed_bytes[3] = bytes[0];
// 	ft_memcpy(&reversed, reversed_bytes, sizeof(int));
// 	return (reversed);
// }



// double get_lll(mlx_texture_t *texture, t_wall *cur)
// {
// 	double x;
// 	if (cur->side == 'v')
// 	{
// 		x = fmodf(cur->ray_dir.y * texture->width, texture->width);
// 	}
// 	else
// 	{
// 		x = fmodf(cur->ray_dir.x * texture->width, texture->width);
// 	}
// 	return x;
// }

// void ft_draw_map(void *param)
// {
// 	t_cub *data = (t_cub *)param;
// 	double angle;
// 	t_wall cur;
// 	int px_x = 0;
// 	uint32_t *pixels;
// 	mlx_texture_t *from_texture;
// 	double x_o, y_o;
// unsigned int tex_y;

// 	while (px_x < WIDTH)
// 	{
// 		angle = get_angle(data->texture.play.angle, px_x);
// 		get_collision(data, &cur, angle, px_x); // Ensure this correctly sets hit points and distances
// 		if (cur.distance == 0)
// 			cur.distance = EPSILON;

// 		cur.height = (int)(HEIGHT / cur.distance);
// 		cur.start = HEIGHT / 2 - cur.height / 2;
// 		cur.end = HEIGHT / 2 + cur.height / 2;

// 		for (int px_y = 0; px_y < HEIGHT; px_y++)
// 		{
// 			if (px_y >= cur.start && px_y <= cur.end)
// 			{
// 				from_texture = get_wall_color(cur, angle, data);
// 				if (!from_texture)
// 					continue;

// 				pixels = (uint32_t *)from_texture->pixels;
// 				x_o = get_lll(from_texture, &cur);
// 				y_o = (px_y - cur.start) * (double)from_texture->height / cur.height;
// 				if (y_o < 0) 
// 					y_o = 0;
// 				if (y_o >= from_texture->height) 
// 					y_o = from_texture->height - 1;
// 				tex_y = (int)y_o * from_texture->width + (int)x_o;
// 				if (tex_y < 0 || tex_y >= from_texture->width * from_texture->height)
// 					continue;
// 				mlx_put_pixel(data->image, px_x, px_y, norm_color(pixels[tex_y]));
// 			}

// 			drawing_ceil_floor(px_y, px_x, data, cur); // Draw ceiling and floor if necessary
// 		}
// 		px_x++;
// 	}
// }


///////////////////////////////////////////////WORKING WITH COLORS

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
	//uint32_t		*pixels;
	unsigned int from_texture; 
	cur = (t_wall){0};
	while (px_x < WIDTH)
	{
		angle = get_angle(data->texture.play.angle, px_x); // get the cur angle until you go through all of them (depends on the width)
		// printf("cur angle is %f\n", angle);
		get_collision(data, &cur, angle, px_x); //get the closest wall grid coordinates (horizontal or vertical collision) depending on which way the player is facing
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
				from_texture = get_wall_color(cur,angle);
				mlx_put_pixel(data->image, px_x, px_y, from_texture);
			}
			drawing_ceil_floor(px_y, px_x,data, cur);
			px_y++;
		}
		px_x++;
	}
}

void ft_hook(mlx_key_data_t keydata, void *param)
{
	t_cub *data;

	data = (t_cub *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		ft_move_up(data);
	if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
		ft_move_down(data);
	if (keydata.key == MLX_KEY_A)
		ft_move_left(data);
	if (keydata.key == MLX_KEY_D)
		ft_move_right(data);		
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