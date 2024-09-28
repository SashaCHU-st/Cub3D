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


# define WIDTH 1080 
# define HEIGHT 1080
# define COL_WALL 0xffff64d9
# define COL_BACK 0x9c0164

typedef struct s_playa
{
    uint32_t x;
    uint32_t y;
    double x_i;
    double y_i;
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
    int x;
    int y;
    int v;
    int h;
    int angle;
} t_intersection;

typedef struct s_coll
{
    int     x;
    int     y;
    double  distance;
} t_coll;

// void open_close_file(char **argv);


#endif