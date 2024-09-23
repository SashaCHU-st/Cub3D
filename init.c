/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:05:18 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/23 13:47:50 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_textures *textures)
{
	textures->no = NULL;
	textures->so = NULL;
	textures->we = NULL;
	textures->ea = NULL;
	textures->found_no = 0;
	textures->found_so = 0;
	textures->found_we = 0;
	textures->found_ea = 0;
	textures->found_f = 0;
	textures->found_c = 0;
	textures->found = 0;
	textures->map_valid = 0;
	textures->floor_color = NULL;
	textures->ceiling_color = NULL;
	textures->floor_r = 0;
	textures->floor_g = 0;
	textures->floor_b = 0;
	textures->ceiling_r = 0;
	textures->ceiling_g = 0;
	textures->ceiling_b = 0;
	textures->how_many_lines = 0;
	textures->player_found = 0;
}
