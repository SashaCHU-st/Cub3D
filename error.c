/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:27:15 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/14 20:17:33 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_map(t_textures *textures)
{
	if (textures->line)
	{
		free(textures->line);
		textures->line = NULL;
	}
	if (textures->map)
	{
		for (int i = 0; i < textures->how_many_lines; i++)
		{
			if (textures->map[i])
			{
				free(textures->map[i]);
				textures->map[i] = NULL;
			}
		}
		free(textures->map);
		textures->map = NULL;
	}
	if (textures->ea)
	{
		free(textures->ea);
		textures->ea = NULL;
	}
	if (textures->no)
	{
		free(textures->no);
		textures->no = NULL;
	}
	if (textures->so)
	{
		free(textures->so);
		textures->so = NULL;
	}
	if (textures->we)
	{
		free(textures->we);
		textures->we = NULL;
	}
	if (textures->floor_color) 
	{
		free(textures->floor_color);
		textures->floor_color = NULL;
	}
	if (textures->ceiling_color)
	{
		free(textures->ceiling_color);
		textures->ceiling_color = NULL;
	}
	if (textures->so_side)
	{
		free(textures->so_side);
		textures->so_side = NULL;
	}
	if (textures->we_side)
	{
		free(textures->we_side);
		textures->we_side = NULL;
	}
	if (textures->ea_side)
	{
		free(textures->ea_side);
		textures->ea_side = NULL;
	}
	if (textures->no_side)
	{
		free(textures->no_side);
		textures->no_side = NULL;
	}
}


void error_fun(t_textures *textures)
{
	printf("Error\n");
	// (void)textures;
	free_map(textures);
	exit(1);
}


void closing(t_textures *textures, char *line, int fd)
{
	(void)line;
	close(fd);
	error_fun(textures);
}
