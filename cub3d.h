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

# define COL_WALL_SOUTH 0xFFB34B28// green
# define COL_WALL_NORTH 0xFF8A2BE2 // orange
# define COL_WALL_EAST 0xFF6A5ACD// pink
# define COL_WALL_WEST 0xFFFFC0CB // light blue

//# define COL_WALL_EAST 0xFF6A5AC
//# define COL_WALL_SOUTH 0xFF00FF7F
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

typedef struct s_vector_i
{
	int	x;
	int	y;
} t_vector_i;

typedef struct s_wall
{
	t_vector	map;
	t_vector	dir;
	t_vector	ray_dir;
	t_vector	camera;
    double  distance;
    double  height;
	double	hit;
	int  start;
	int  end;
	char	side;	
} t_wall;

typedef struct s_playa
{
    double x;
    double y;
    double  angle;
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

typedef struct s_draw_tex
{
	mlx_texture_t *cur;
	t_vector_i	tex;
	unsigned int i;
	double	start_tex;
	double	step;
} t_draw_tex;

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
	mlx_texture_t *no_side;
	mlx_texture_t *so_side;
	mlx_texture_t *we_side;
	mlx_texture_t *ea_side;
	t_playa	play;
} t_textures;

typedef struct s_cub
{	
	mlx_t   *mlx;
    mlx_image_t *image;
	t_textures texture;
	t_wall	cur;
	t_draw_tex ture;
} t_cub;
// void open_close_file(char **argv);


//collision.c
void 			set_hori(t_cub *data, t_collision *cur, t_wall *wall);
void 			set_vert(t_cub *data, t_collision *cur, t_wall *wall);
void			do_dda(t_cub *data, t_collision *cur, t_wall *wall);
double			set_wall_angle(t_cub *data, t_wall *wall, int i);
double			get_collision(t_cub *data, t_wall *wall, int px_x);
//draw_window.c
mlx_texture_t	*get_wall_color(t_wall *cur, double angle, t_cub *data);
double			get_tex_x(mlx_texture_t *from_texture, t_wall *cur);
void			set_draw_tex(t_cub *data, double angle);
void			calc_wall(t_wall *cur);
void			ft_draw_window(void *param);
//movement.c
void			ft_move_up(t_cub *data);
void			ft_move_down(t_cub *data);
void			ft_move_left(t_cub *data);
void			ft_move_right(t_cub *data);
void	 		ft_hook(mlx_key_data_t keydata, void *param);
//slice.c
int				norm_color(int c);
void			drawing_ceil_floor(int px_y, int px_x, t_cub *data, t_wall *cur);
void			slice(t_cub *data, t_vector_i px);
//utils.c
char			*avoid_whitespace(char *str);
int				print_err_int(char *str);
int				check_space(char ch);
char			*ft_strcpy(char *dest, const char *src); //dont we have libft for this?
//utils2.c
uint32_t		get_rgba(int r, int g, int b);
int   			check_coord(int x, int y, t_cub *data);
void			set_wall_dist(t_wall *wall, t_cub *data, double	step);

void 			open_close_file(char **argv, t_textures *textures);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			checking_textures(t_textures *textures, char *line);
char			*ft_strdup(const char *src); //libft?
void			checking_color(t_textures *textures, char *line);
char			**ft_split(char const *s, char c); //libft?
void			parse_floor_color(const char *color_string, t_textures *textures, bool is_floor);
int				ft_atoi(const char *str);
int				parse_color_values(t_textures *textures,const char *color_string, int *values);
void			no(t_textures *textures, char *line);
void			so(t_textures *textures, char *line);
void			ea(t_textures *textures, char *line);
void			we(t_textures *textures, char *line);
void			error_fun(t_textures *textures);
int				ft_isdigit(int c);
int				check_if_png(char *str);
void			all_found(t_textures *textures);\
void			count_lines(char **argv, t_textures *textures, int fd);
void			closing(t_textures *textures,char *line, int fd);
int				map_closed(t_textures *textures);
int				map_closed(t_textures *textures);
void			if_new_line_in_middle(t_textures *textures);
char			*ft_strtrim(char *s1, char *set);
void			replacing_spaces_with_one(t_textures *textures);
int				map_closed(t_textures *textures);
void			*ft_memset(void *b, int c, size_t len);
void			replacing_nl_with_zero(t_textures *textures);
void			free_map(t_textures *textures);
int				checking_map(t_textures *textures, char *line, int number);
void			*ft_memcpy(void *dst, const void *src, size_t n);
int				check_args(char *str);

///checkin_textures_first.c
void if_all_6_found(t_textures *textures, int fd);
void checking_validity(t_textures *textures, int fd );
void	count_lines(char **argv, t_textures *textures, int fd);
void checking_the_info( t_textures *textures, int i);
void open_first(int fd, char **argv, t_textures *textures);

int			some_rubish_fun(t_textures *textures);
int			flood_fill(char **map, int rows, int cols, int x, int y);
void		print_map(t_textures *textures);
// =======
// int			some_rubish_fun(t_textures *textures);

// int			flood_fill(char **map, int rows, int cols, int x, int y);
// void		print_map(t_textures *textures);
// int			check_args(char *str);
// >>>>>>> main
#endif