/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:35:02 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/18 15:36:25 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_floor_color(const char *color_string, t_textures *textures, \
	bool is_floor)
{
	int	values[3];

	if (parse_color_values(textures, color_string, values))
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
		error_fun(textures);
}

void	checking_color(t_textures *textures, char *line)
{
	if (ft_strncmp(line, "F", 1) == 0 && check_space(line[1]))
	{
		textures->found_f += 1;
		textures->floor_color = ft_strdup(avoid_whitespace(line + 2));
		parse_floor_color(textures->floor_color, textures, true);
	}
	else if (ft_strncmp(line, "C", 1) == 0 && check_space(line[1]))
	{
		textures->found_c += 1;
		textures->ceiling_color = ft_strdup(avoid_whitespace(line + 2));
		parse_floor_color(textures->ceiling_color, textures, false);
	}
}