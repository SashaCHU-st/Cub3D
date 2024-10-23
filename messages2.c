/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:34:55 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 11:09:31 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_error(t_textures *text)
{
	printf("Error to open file\n");
	error_fun(text);
}

void	error_map_not_valid(t_textures *textures, int fd)
{
	printf("Map not valid\n");
	closing(textures, fd);
}

void	found_nl_in_map(t_textures *textures, int fd)
{
	printf("New line in map\n");
	closing(textures, fd);
}

void	failed_to_copy(t_textures *textures, int fd)
{
	free(textures->line);
	printf("Malloc fails\n");
	closing(textures, fd);
}

void	wrong_values(t_textures *textures, int fd)
{
	printf("Wrong values\n");
	closing(textures, fd);
}
