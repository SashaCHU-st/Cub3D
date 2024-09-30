/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:42:30 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/30 10:04:42 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_number(const char *str)
{
	int i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return 0;
		i++;
	}
	
	return 1;
}

int	parse_color_values(t_textures *textures,const char *color_string, int *values)
{
	char **colors;
	int i;
	int j = 0;
	i = 0;
	colors = ft_split(color_string, ',');
	if (!colors)
	{
		printf("to split the color string.\n");
		return 0;
	}
	while (colors[i] != NULL && i < 3)
	{
		if (is_valid_number(colors[i]))
		{
			values[i] = ft_atoi(colors[i]);
			if(values[i] > 255 || values[i] < 0)
				error_fun(textures);
		}
		else
		{
			j = 0;
			while (colors[j] != NULL)
			{
				free(colors[j]);
				j++;
			}
			free(colors);
			error_fun(textures);
		}
		i++;
	}
	j =0;
	while (colors[j] != NULL)
	{
		free(colors[j]);
		j++;
	}
	free(colors);
	if (i == 3)
		return 1;
	else
	{
		printf("expected 3.\n");
		error_fun(textures);
		return 0;
	}
}

void	parse_floor_color(const char *color_string, t_textures *textures, bool is_floor)
{
	int	values[3];

	if (parse_color_values(textures, color_string, values))
	{
		if (is_floor)
		{
			textures->floor_r = values[0];
			textures->floor_g = values[1];
			textures->floor_b = values[2];
			printf("floor color: R = %d, G = %d, B = %d\n", textures->floor_r, textures->floor_g, textures->floor_b);
		}
		else
		{
			textures->ceiling_r = values[0];
			textures->ceiling_g = values[1];
			textures->ceiling_b = values[2];
			printf("ceiling color: R = %d, G = %d, B = %d\n", textures->ceiling_r, textures->ceiling_g, textures->ceiling_b);
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
		printf("FLOOR COLOR: %s\n", textures->floor_color);
		parse_floor_color(textures->floor_color, textures, true);
	}
	else if (ft_strncmp(line, "C", 1) == 0 && check_space(line[1]))
	{
		textures->found_c += 1;
		textures->ceiling_color = ft_strdup(avoid_whitespace(line + 2));
		printf("CEILING COLOR: %s\n", textures->ceiling_color);
		parse_floor_color(textures->ceiling_color, textures, false);
	}
}