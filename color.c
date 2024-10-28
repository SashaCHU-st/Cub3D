/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:42:30 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/28 10:52:35 by aheinane         ###   ########.fr       */
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
		colors[j] = NULL;
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

int	process_and_validate_colors(char ***colors, int *values,
	t_textures *text, int fd)
{
	int	how_many_colors;

	how_many_colors = 0;
	while ((*colors)[how_many_colors] != NULL)
	{
		if (how_many_colors >= 3)
		{
			free_color(0, *colors);
			*colors = NULL;
			closing(text, fd, "More then 3 elements in colors\n");
		}
		if (is_valid_number((*colors)[how_many_colors]))
		{
			values[how_many_colors] = ft_atoi((*colors)[how_many_colors]);
			color_out_of_range(values[how_many_colors], text, fd, colors);
		}
		else
			wrong_values_color(how_many_colors, (*colors), text, fd);
		how_many_colors++;
	}
	return (how_many_colors);
}

int	parse_color_values(t_textures *text, const char *color_string,
	int *values, int fd)
{
	char	**colors;
	int		how_many_colors;

	if (!split_colors(&colors, color_string))
		return (0);
	how_many_colors = process_and_validate_colors(&colors, values, text, fd);
	free_color(how_many_colors, colors);
	if (how_many_colors == 3)
		return (1);
	else
	{
		closing(text, fd, "Not valid set of colors\n");
		return (0);
	}
}
