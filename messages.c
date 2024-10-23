/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:21:21 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 11:09:49 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wrong_player(t_textures *textures, int fd)
{
	printf("Wrong Player\n");
	closing(textures, fd);
}

void	more_the_one_or_no(t_textures *textures, int fd)
{
	printf("No player or more then 1\n");
	closing(textures, fd);
}

void	wrong_values_color(int j, char **colors, t_textures *text, int fd)
{
	free_color(j, colors);
	printf("Wrong values\n");
	closing(text, fd);
}

void	malloc_fails(t_textures *textures, int fd)
{
	printf("Malloc fails\n");
	closing(textures, fd);
}

void	error_map_not_closed(t_textures *textures, int fd)
{
	printf("Map is not closed\n");
	closing(textures, fd);
}
