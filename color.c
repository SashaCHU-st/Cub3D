/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:42:30 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 14:58:03 by aheinane         ###   ########.fr       */
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

int	process_and_validate_colors(char **colors, int *values,
	t_textures *text, int fd)
{
	int	i;

	i = 0;
	while (colors[i] != NULL)
	{
		if (is_valid_number(colors[i]))
		{
			values[i] = ft_atoi(colors[i]);
			color_out_of_range(values, i, text, fd);
		}
		else
		{
			wrong_values_color(i, colors, text, fd);
			return (0);
		}
		i++;
	}
	return (i);
}

int	parse_color_values(t_textures *text, const char *color_string,
	int *values, int fd)
{
	char	**colors;
	int		i;

	if (!split_colors(&colors, color_string))
		return (0);
	i = process_and_validate_colors(colors, values, text, fd);
	free_color(0, colors);
	if (i == 3)
		return (1);
	else
		closing(text, fd, "Not valid set of colors\n");
	return (0);
}
