/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:11:53 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/24 13:45:02 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

# define WIDTH 1080 
# define HEIGHT 1080
# define EPSILON 0.0001

const static double	g_convert = M_PI / 180;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_vector_i
{
	int	x;
	int	y;
}	t_vector_i;

typedef struct s_wall
{
	t_vector	map;
	t_vector	dir;
	t_vector	ray_dir;
	t_vector	camera;
	double		distance;
	double		height;
	double		hit;
	int			start;
	int			end;
	char		side;
}	t_wall;

typedef struct s_playa
{
	double	x;
	double	y;
	double	angle;
}	t_playa;

typedef struct s_intersection
{
	double	dot;
	double	step;
}	t_intersection;

typedef struct s_collision
{
	t_intersection	hori;
	t_intersection	vert;
	t_vector		iterate;
}	t_collision;

typedef struct s_draw_tex
{
	mlx_texture_t	*cur;
	t_vector_i		tex;
	unsigned int	i;
	double			start_tex;
	double			step;
}	t_draw_tex;

typedef struct s_textures
{
	char			*line;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				found_no;
	int				found_so;
	int				found_we;
	int				found_ea;
	int				found_f;
	int				found_c;
	int				found;
	char			sides;
	char			*floor_color;
	char			*ceiling_color;
	int				floor_r;
	int				floor_g;
	int				floor_b;
	int				ceiling_r;
	int				ceiling_g;
	int				ceiling_b;
	int				map_valid;
	int				how_many_lines;
	int				player_found;
	int				map_index;
	char			**map;
	int				ceiling;
	int				floor;
	int				len_current;
	int				len_next;
	int				length;
	int				*found_flag;
	int				map_started;
	int				permission;
	mlx_texture_t	*no_side;
	mlx_texture_t	*so_side;
	mlx_texture_t	*we_side;
	mlx_texture_t	*ea_side;
	t_playa			play;
}	t_textures;

typedef struct s_cub
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_textures	texture;
	t_wall		cur;
	t_draw_tex	ture;
}	t_cub;

//check_args.c
int				check_args(char *str);

//check_map.c
void			all_found(t_textures *textures, int fd);
void			when_player_found(t_textures *textures, char *line, int i);
int				checking_map(t_textures *textures, char *line, int n, int fd);

///collision.c
void			set_hori(t_cub *data, t_collision *cur, t_wall *wall);
void			set_vert(t_cub *data, t_collision *cur, t_wall *wall);
void			do_dda(t_cub *data, t_collision *cur, t_wall *wall);
double			set_wall_angle(t_cub *data, t_wall *wall, int i);
double			get_collision(t_cub *data, t_wall *wall, int px_x);

//color.c
int				parse_color_values(t_textures *text,
					const char *color_string, int *values, int fd);
int				split_colors(char ***colors, const char *color_string);
int				process_and_validate_colors(char **colors, int *values, \
					t_textures *text, int fd);
void			free_color(int j, char	**colors);
int				is_valid_number(const char *str);

//color_parsing.c
void			parse_floor_color(const char *color_string,
					t_textures *textures, bool is_floor, int fd);
void			checking_color(t_textures *textures, char *line, int fd);

//draw_window.c
mlx_texture_t	*get_wall_color(t_wall *cur, double angle, t_cub *data);
double			get_tex_x(mlx_texture_t *from_texture, t_wall *cur);
void			set_draw_tex(t_cub *data, double angle);
void			calc_wall(t_wall *cur);
void			ft_draw_window(void *param);

//error.c
void			free_map_two(t_textures *textures);
void			free_map_three(t_textures *textures);
void			free_map(t_textures *textures);
void			error_fun(t_textures *textures, char *str);
void			closing(t_textures *textures, int fd, char *str);

//finilizing.c
void			finilizing(int map_started, t_textures *textures, int fd);

//if_png.c
int				check_if_png(char *str);

//map_closed.c
int				map_closed(t_textures *textures);
int				check_row_closure(t_textures *textures, int i);
int				check_sides_closed(t_textures *textures, int i);
int				check_bottom_row_closed(t_textures *textures);
int				check_top_row_closed(t_textures *textures);

//map_last.c
void			replacing_nl_with_zero(t_textures *textures);
void			for_last_one(t_textures *textures, int j);
void			replacing_spaces_with_one(t_textures *textures);

//movement.c
void			ft_move_up(t_cub *data);
void			ft_move_down(t_cub *data);
void			ft_move_right(t_cub *data);
void			ft_move_left(t_cub *data);
void			ft_hook(mlx_key_data_t keydata, void *param);

//open.c
void			open_close_file(char **argv, t_textures *textures);
void			open_first(int fd, char **argv, t_textures *textures);
void			checking_the_info( t_textures *textures, int i, int fd);
void			scanning_map(char **argv, t_textures *textures, int fd);
void			checking_validity(t_textures *textures, int fd);

//parsing_statered.c
int				count_map_lines(t_textures *textures, int fd);
int				if_is_map_started(const char *line);
void			open_second(int fd, char **argv, t_textures *text);
void			reading_lines(int fd, t_textures *textures, int i);
void			map_started_fun(int map_started, int i,
					t_textures *textures, int fd);

//slice.c
int				norm_color(int c);
void			drawing_ceil_floor(int px_y, int px_x, t_cub *data,
					t_wall *cur);
void			slice(t_cub *data, t_vector_i px);

void			ea(t_textures *textures, char *line, int fd);
void			we(t_textures *textures, char *line, int fd);
void			so(t_textures *textures, char *line, int fd);
void			no(t_textures *textures, char *line, int fd);

//textures.c
void			checking_textures(t_textures *textures, char *line, int fd);

//utils.c
char			*ft_strcpy(char *dest, const char *src);
int				check_space(char ch);
char			*avoid_whitespace(char *str);
int				print_err_int(char *str);

//utils2.c
uint32_t		get_rgba(int r, int g, int b);
int				check_coord(int x, int y, t_cub *data);
void			set_wall_dist(t_wall *wall, t_cub *data, double step);

//messages.c
void			wrong_values_color(int j, char **colors, t_textures *text,
					int fd);
void			failed_to_copy(t_textures *textures, int fd);
void			color_out_of_range(int *values, int i, t_textures *text,
					int fd);

//uploading_text.c
void			uploading_text(t_textures *textures, int fd);
int				check_text(mlx_texture_t *tex);

#endif