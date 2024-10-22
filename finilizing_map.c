/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finilizing_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:18:33 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/22 13:29:11 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	finilizing(int map_started, t_textures *textures, int fd)
{
	textures->map[textures->map_index] = NULL;
	textures->how_many_lines = textures->map_index;
	if (!map_started)
		error_fun(textures);
	if (textures->player_found == 0)
		error_fun(textures);
	if_new_line_in_middle(textures);
	replacing_spaces_with_one(textures);
	replacing_nl_with_zero(textures);
	if (!map_closed(textures))
		error_fun(textures);
	if (textures->how_many_lines < 3)
	{
		free(textures->line);
		close(fd);
		error_fun(textures);
	}
	free(textures->line);
	close(fd);
}
