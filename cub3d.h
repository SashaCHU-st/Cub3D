#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
# include "MLX42/include/MLX42/MLX42.h"

typedef struct s_cub
{
	
	char **map;
	size_t size;
} t_cub;


void open_close_file(char **argv);


#endif