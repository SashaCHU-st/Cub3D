/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:05:18 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/14 10:36:58 by aheinane         ###   ########.fr       */
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
	textures->map_index = 0;
	textures->line = NULL;
	textures->map = NULL;
	textures->ceiling = 0;
	textures->floor = 0;
	textures->length = 0;
	textures->no_side = NULL;
	textures->so_side = NULL;
	textures->we_side = NULL;
	textures->ea_side = NULL;
	//textures->sides = NULL;
}
