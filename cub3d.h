#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <math.h>
# include "MLX42/include/MLX42/MLX42.h"


# define WIDTH 512 
# define HEIGHT 512
# define COL_WALL 0xffff64d9
# define COL_BACK 0x9c0164
# define ANGL_INCREM 60 / WIDTH
# define CONVERT M_PI / 180

# define THIRTY 30 * CONVERT
# define NINETY 90 * CONVERT
# define TWOSEVEN 270 * CONVERT
# define THREESIX 360 * CONVERT


typedef struct s_wall
{
	double     x;
    double     y;
    double  distance;
    double  height;
	double  start;
	double  end;
} t_wall;

typedef struct s_playa
{
    double x;
    double y;
    double  angle;
    double  dir_ray;
    double  min_ray;
    double  max_ray;
} t_playa;

typedef struct s_cub
{	
	mlx_t   *mlx;
    mlx_image_t *image;
	int 	**map;
	size_t size;
    t_playa play;
} t_cub;

typedef struct s_intersection
{
    double x;
    double y;
    double v;
    double h;
    double dist;
} t_intersection;

// void open_close_file(char **argv);


#endif