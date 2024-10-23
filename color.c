/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:42:30 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 09:23:43 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_color(int j, char	**colors)
{
	j = 0;
	while (colors[j] != NULL)
	{
		free(colors[j]);
		j++;
	}
	free(colors);
}

int	split_colors(char ***colors, const char *color_string)
{
	*colors = ft_split(color_string, ',');
	if (!*colors)
		return (0);
	return (1);
}

int	valid_color(int i, int j, char **colors, t_textures *textures)
{
	free_color(j, colors);
	if (i == 3)
		return (1);
	else
	{
		printf("Not valid set of colors\n");
		error_fun(textures);
		return (0);
	}
}

int	parse_color_values(t_textures *text, const char *color_string, int *values)
{
	char	**colors;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!split_colors(&colors, color_string))
		return (0);
	while (colors[i] != NULL)
	{
		if (is_valid_number(colors[i]))
		{
			values[i] = ft_atoi(colors[i]);
			if (values[i] > 255 || values[i] < 0)
			{
				printf("Values must be from 0 to 255\n");
				error_fun(text);
			}
		}
		else
			wrong_values_color(j, colors, text);
		i++;
	}
	return (valid_color(i, j, colors, text));
}
