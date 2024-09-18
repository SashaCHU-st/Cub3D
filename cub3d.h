/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:45:25 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/18 11:22:56 by aheinane         ###   ########.fr       */
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
	char *no;
	char *so;
	char *we;
	char *ea;
} t_textures;



void	open_close_file(char **argv);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	checking_textures(char *line);
char	*ft_strdup(const char *src);
char	*avoid_whitespace(char *str);
int		check_space(char ch);


#endif