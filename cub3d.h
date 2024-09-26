/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:45:25 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/26 16:24:57 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
# include "MLX42/include/MLX42/MLX42.h"

typedef struct s_cub
{
	char **map;
	size_t size;
} t_cub;


typedef struct s_textures
{
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
} t_textures;


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
int		parse_color_values(const char *color_string, int *values);
void	no(t_textures *textures, char *line);
void	so(t_textures *textures, char *line);
void	ea(t_textures *textures, char *line);
void	we(t_textures *textures, char *line);
void	error_fun();
int		ft_isdigit(int c);
int		check_if_png(char *str);
void	all_found(t_textures *textures);
void	count_lines(t_textures *textures, char *line);
int		checking_map(t_textures *textures, char *line);
void	map_last(t_textures *textures, char *line, int fd);
void	closing(char *line, int fd);
int		map_closed(t_textures *textures);
void	flood_fill(t_textures *textures, int x, int y);
int		map_closed(t_textures *textures);
void	map_last(t_textures *textures, char *line, int fd);
void	replacing_nl(t_textures *textures);
void	if_new_line_in_middle(t_textures *textures);
void	can_start_map(t_textures *textures, int fd);
void	parsing_map(t_textures *textures, char *line, int fd);

// void	parsing_the_map(t_textures *textures, char *line, int map_started, int fd, int map_index);
// void	scan_the_map(t_textures *textures);
// int		check_space2(char ch);
// int		check_leading_space(char *line);
#endif