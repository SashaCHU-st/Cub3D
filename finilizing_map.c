/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finilizing_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:18:33 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 14:50:42 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	finilizing(int map_started, t_textures *textures, int fd)
{
	textures->map[textures->map_index] = NULL;
	textures->how_many_lines = textures->map_index;
	if (!map_started)
		closing(textures, fd, "Wrong info provided\n");
	if (textures->player_found == 0)
	{
		closing(textures, fd, "No player\n");
	}
	replacing_spaces_with_one(textures);
	replacing_nl_with_zero(textures);
	if (!map_closed(textures))
		closing(textures, fd, "Map is not closed\n");
	if (textures->how_many_lines < 3)
	{
		free(textures->line);
		closing(textures, fd, "Less then 2 lines in the map\n");
	}
	free(textures->line);
	close(fd);
}
