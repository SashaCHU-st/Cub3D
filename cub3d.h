#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <math.h>
# include "get_next_line.h"
# include "MLX42/include/MLX42/MLX42.h"


# define WIDTH 1080 
# define HEIGHT 1080
# define COL_WALL 0xffff64d9
# define COL_BACK 0x9c0164
# define ANGL_INCREM 60 / WIDTH
# define CONVERT M_PI / 180
# define EPSILON 0.0001
# define PLANE tan(THIRTY)


# define THIRTY 30 * CONVERT
# define NINETY 90 * CONVERT
# define TWOSEVEN 270 * CONVERT
# define THREESIX 360 * CONVERT

typedef struct s_vector
{
	double	x;
	double	y;
} t_vector;

typedef struct s_vector
{
	double	x;
	double	y;
} t_vector;

typedef struct s_wall
{
	t_vector	map;
	t_vector	dir;
	t_vector	ray_dir;
	t_vector	camera;
    double  distance;
    int  height;
	int  start;
	int  end;
	char	side;	
} t_wall;

typedef struct s_playa
{
    double x;
    double y;
    double  angle;
    // double  dir_ray;
    // double  min_ray;
    // double  max_ray;
} t_playa;

typedef struct s_intersection
{
    double dot;
    double step;
} t_intersection;

typedef struct s_collision
{
	t_intersection hori;
	t_intersection vert;
	t_vector iterate;
}	t_collision;

typedef struct s_textures
{
	char	*line;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		found_no;
	int		found_so;
	int		found_we;
	int		found_ea;
	int		found_f;
	int		found_c;
	int		found;
	char	sides;
	char	*floor_color;
	char	*ceiling_color;
	int		floor_r;
	int		floor_g;
	int		floor_b;
	int		ceiling_r;
	int		ceiling_g;
	int		ceiling_b;
	int		map_valid;
	int		how_many_lines;
	int		player_found;
	int		map_index;
	char	**map;
	int		ceiling;
	int		floor;
	int		length;
	t_playa	play;
} t_textures;

typedef struct s_cub
{	
	mlx_t   *mlx;
    mlx_image_t *image;
	t_textures texture;
} t_cub;
// void open_close_file(char **argv);

int		check_args(char *str);
void 	open_close_file(char **argv, t_textures *textures);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	checking_textures(t_textures *textures, char *line);
char	*ft_strdup(const char *src);
char	*avoid_whitespace(char *str);
int		check_space(char ch);
void	checking_color(t_textures *textures, char *line);
void	init(t_textures *textures);
char	*ft_strcpy(char *dest, const char *src);
char	**ft_split(char const *s, char c);
void	parse_floor_color(const char *color_string, t_textures *textures, bool is_floor);
int		ft_atoi(const char *str);
int		parse_color_values(t_textures *textures,const char *color_string, int *values);
void	no(t_textures *textures, char *line);
void	so(t_textures *textures, char *line);
void	ea(t_textures *textures, char *line);
void	we(t_textures *textures, char *line);
void	error_fun(t_textures *textures);
int		ft_isdigit(int c);
int		check_if_png(char *str);
void	all_found(t_textures *textures);\
void	count_lines(char **argv, t_textures *textures, int fd, char *line);
void	closing(t_textures *textures,char *line, int fd);
int		map_closed(t_textures *textures);
int		map_closed(t_textures *textures);
void	if_new_line_in_middle(t_textures *textures);
char	*ft_strtrim(char *s1, char *set);
void	replacing_spaces_with_one(t_textures *textures);
//void replacing_spaces_with_one_or_two(t_textures *textures);
int		map_closed(t_textures *textures);
int		flood_fill(char **map, int rows, int cols, int x, int y);
void	print_map(t_textures *textures);
void	*ft_memset(void *b, int c, size_t len);
void	replacing_nl_with_zero(t_textures *textures);
void	free_map(t_textures *textures);
int	checking_map(t_textures *textures, char *line, int number);

uint32_t get_rgba(int r, int g, int b);
#endif