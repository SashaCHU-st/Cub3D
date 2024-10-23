/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finilizing_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:18:33 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 11:02:46 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wrong_info(t_textures *textures, int fd)
{
	printf("Wrong info provided\n");
	closing(textures, fd);
}

void	finilizing(int map_started, t_textures *textures, int fd)
{
	textures->map[textures->map_index] = NULL;
	textures->how_many_lines = textures->map_index;
	if (!map_started)
		wrong_info(textures, fd);
	if (textures->player_found == 0)
	{
		printf("No player\n");
		closing(textures, fd);
	}
	replacing_spaces_with_one(textures);
	replacing_nl_with_zero(textures);
	if (!map_closed(textures))
		error_map_not_closed(textures, fd);
	if (textures->how_many_lines < 3)
	{
		free(textures->line);
		printf("Less then 2 lines in the map\n");
		closing(textures, fd);
	}
	free(textures->line);
	close(fd);
}
