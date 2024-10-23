/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:19:30 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 15:35:39 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_floor_color(const char *color_string, t_textures *textures, \
	bool is_floor, int fd)
{
	int	values[3];

	if (parse_color_values(textures, color_string, values, fd))
	{
		if (is_floor)
		{
			textures->floor_r = values[0];
			textures->floor_g = values[1];
			textures->floor_b = values[2];
			textures->floor = get_rgba(values[0], values[1], values[2]);
		}
		else
		{
			textures->ceiling_r = values[0];
			textures->ceiling_g = values[1];
			textures->ceiling_b = values[2];
			textures->ceiling = (textures->ceiling_r << 16) | \
				(textures->ceiling_g << 8) | textures->ceiling_b;
			textures->ceiling = get_rgba(values[0], values[1], values[2]);
		}
	}
	else
		closing(textures, fd, "Wrong values\n");
}

void	checking_color(t_textures *textures, char *line, int fd)
{
	if (ft_strncmp(line, "F", 1) == 0 && check_space(line[1]))
	{
		textures->found_f += 1;
		if (textures->found_f > 1)
			closing(textures, fd, "More than one same texture found\n");
		if (textures->floor_color)
			free(textures->floor_color);
		textures->floor_color = ft_strdup(avoid_whitespace(line + 2));
		if (!textures->floor_color)
			closing(textures, fd, "Malloc failed\n");
		parse_floor_color(textures->floor_color, textures, true, fd);
	}
	else if (ft_strncmp(line, "C", 1) == 0 && check_space(line[1]))
	{
		textures->found_c += 1;
		if (textures->found_c > 1)
			closing(textures, fd, "More than one same texture found\n");
		if (textures->ceiling_color)
			free(textures->ceiling_color);
		textures->ceiling_color = ft_strdup(avoid_whitespace(line + 2));
		if (!textures->ceiling_color)
			closing(textures, fd, "Malloc failed\n");
		parse_floor_color(textures->ceiling_color, textures, false, fd);
	}
}
