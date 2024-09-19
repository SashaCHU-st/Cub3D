/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:45:25 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/19 10:50:23 by aheinane         ###   ########.fr       */
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
int		validation(t_textures *text);
char	*ft_strcpy(char *dest, const char *src);
char	**ft_split(char const *s, char c);
void	parse_floor_color(const char *color_string, t_textures *textures, bool is_floor);
int		ft_atoi(const char *str);
int		parse_color_values(const char *color_string, int *values);
void	validity_map(t_textures *textures);
#endif