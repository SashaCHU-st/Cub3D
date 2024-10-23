/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finilizing_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:18:33 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 08:59:18 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	finilizing(int map_started, t_textures *textures, int fd)
{
	textures->map[textures->map_index] = NULL;
	textures->how_many_lines = textures->map_index;
	if (!map_started)
	{
		printf("Wrong info provided\n");
		error_fun(textures);
	}
	if (textures->player_found == 0)
	{
		printf("No player\n");
		error_fun(textures);
	}
	if_new_line_in_middle(textures);
	replacing_spaces_with_one(textures);
	replacing_nl_with_zero(textures);
	if (!map_closed(textures))
	{
		printf("Map is not closed\n");
		error_fun(textures);
	}
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
