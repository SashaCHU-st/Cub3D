/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finilizing_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:18:33 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 09:57:44 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wrong_info(t_textures *textures)
{
	printf("Wrong info provided\n");
	error_fun(textures);
}

void	finilizing(int map_started, t_textures *textures, int fd)
{
	textures->map[textures->map_index] = NULL;
	textures->how_many_lines = textures->map_index;
	if (!map_started)
		wrong_info(textures);
	if (textures->player_found == 0)
	{
		printf("No player\n");
		error_fun(textures);
	}
	replacing_spaces_with_one(textures);
	replacing_nl_with_zero(textures);
	if (!map_closed(textures))
		error_map_not_closed(textures);
	if (textures->how_many_lines < 3)
	{
		free(textures->line);
		close(fd);
		printf("Less then 2 lines in the map\n");
		error_fun(textures);
	}
	free(textures->line);
	close(fd);
}
