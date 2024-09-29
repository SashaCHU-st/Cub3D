/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:27:15 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/29 17:54:14 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_map(t_textures *textures)
{
	if (textures->map)
	{
		printf("Freeing map with %d lines\n", textures->map_index);
		for (int i = 0; i < textures->map_index; i++)
		{
			if (textures->map[i])
			{
				printf("Freeing line %d: %s\n", i, textures->map[i]);
				free(textures->map[i]);
			}
		}
		free(textures->map);
		textures->map = NULL;
	}
	else
	{
		printf("Nothing to free in the map\n");
	}
}



void error_fun(t_textures *textures)
{
	printf("Error\n");
	if(textures)
	{
		printf("KUKUUUU\n");
		//free_map(textures);
	}
	exit(1);
}

void closing(t_textures *textures,char *line, int fd)
{
	free(line);
	close(fd);
	error_fun(textures);
}