/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:42:30 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/19 10:29:42 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void colors_here(char **colors, int i, int values[])
{
	if (!colors)
	{
		printf("Error: Failed to split the color string.\n");
		return;
	}
	while (colors[i] != NULL && i < 3)
	{
		values[i] = ft_atoi(colors[i]);
		i++;
	}
}

void parse_floor_color(const char *color_string, t_textures *textures, bool is_floor)
{
	char **colors;
	int values[3];
	int i = 0;

	colors = ft_split(color_string, ',');
	colors_here(&colors, i, values);
	// if (!colors)
	// {
	// 	printf("Error: Failed to split the color string.\n");
	// 	return;
	// }
	// while (colors[i] != NULL && i < 3)
	// {
	// 	values[i] = ft_atoi(colors[i]);
	// 	i++;
	// }
	if (i == 3)
	{
		if (is_floor)
		{
			textures->floor_r = values[0];
			textures->floor_g = values[1];
			textures->floor_b = values[2];
			printf("Parsed floor color values: R = %d, G = %d, B = %d\n", textures->floor_r, textures->floor_g, textures->floor_b);
		}
		else
		{
			textures->ceiling_r = values[0];
			textures->ceiling_g = values[1];
			textures->ceiling_b = values[2];
			printf("Parsed ceiling color values: R = %d, G = %d, B = %d\n", textures->ceiling_r, textures->ceiling_g, textures->ceiling_b);
		}
	}
	else
	{
		printf("Error: Invalid color format, expected 3 values.\n");
	}
	i = 0;
	while (colors[i] != NULL)
	{
		free(colors[i]);
		i++;
	}
	free(colors);
}


void checking_color(t_textures *textures, char *line)
{
	if (!line || !textures)
		return;

	if (ft_strncmp(line, "F", 1) == 0 && check_space(line[1]))
	{
		textures->found_f = 1;
		textures->floor_color = ft_strdup(avoid_whitespace(line + 2));
		printf("FLOOR COLOR: %s\n", textures->floor_color);
		parse_floor_color(textures->floor_color, textures, true);
	}
	else if (ft_strncmp(line, "C", 1) == 0 && check_space(line[1]))
	{
		textures->found_c = 1;
		textures->ceiling_color = ft_strdup(avoid_whitespace(line + 2));
		printf("CEILING COLOR: %s\n", textures->ceiling_color);
		parse_floor_color(textures->ceiling_color, textures, false);
	}
}