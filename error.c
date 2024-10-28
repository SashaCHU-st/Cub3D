/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:27:15 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/24 12:45:56 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map_two(t_textures *textures)
{
	if (textures->so_side)
		mlx_delete_texture(textures->so_side);
	if (textures->we_side)
		mlx_delete_texture(textures->we_side);
	if (textures->ea_side)
		mlx_delete_texture(textures->ea_side);
	if (textures->no_side)
		mlx_delete_texture(textures->no_side);
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
}

void	free_map_three(t_textures *textures)
{
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
}

void	free_map(t_textures *textures)
{
	int	i;

	i = 0;
	free_map_two(textures);
	free_map_three(textures);
	if (textures->line)
	{
		free(textures->line);
		textures->line = NULL;
	}
	if (textures->map)
	{
		while (i < textures->how_many_lines)
		{
			if (textures->map[i])
			{
				free(textures->map[i]);
				textures->map[i] = NULL;
			}
			i++;
		}
		free(textures->map);
		textures->map = NULL;
	}
}

void	error_fun(t_textures *textures, char *str)
{
	printf("Error\n");
	printf("%s", str);
	free_map(textures);
	exit(1);
}

void	closing(t_textures *textures, int fd, char *str)
{
	close(fd);
	error_fun(textures, str);
}
