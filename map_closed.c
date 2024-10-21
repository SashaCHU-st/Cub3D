/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:05:10 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/21 12:09:33 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_top_row_closed(t_textures *textures)
{
	int	i;

	i = 0;
	while (textures->map[0][i])
	{
		if (textures->map[0][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_bottom_row_closed(t_textures *textures)
{
	int	i;
	int	last_index;

	i = 0;
	last_index = textures->how_many_lines - 1;
	while (textures->map[last_index][i])
	{
		if (textures->map[last_index][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_sides_closed(t_textures *textures, int i)
{
	int	len_current;

	len_current = ft_strlen(textures->map[i]);
	if (textures->map[i][0] != '1' || textures->map[i][len_current - 1] != '1')
		return (0);
	return (1);
}

int	check_row_closure(t_textures *textures, int i)
{
	int	j;

	textures->len_current = ft_strlen(textures->map[i]);
	textures->len_next = ft_strlen(textures->map[i + 1]);
	if (textures->len_current < textures->len_next)
	{
		j = textures->len_current;
		while (j < textures->len_next)
		{
			if (textures->map[i + 1][j] != '1')
				return (0);
			j++;
		}
	}
	else if (textures->len_current > textures->len_next)
	{
		j = textures->len_next;
		while (j < textures->len_current)
		{
			if (textures->map[i][j] != '1')
				return (0);
			j++;
		}
	}
	return (1);
}

int	map_closed(t_textures *textures)
{
	int	i;
	int	last_index;

	last_index = textures->how_many_lines - 1;
	i = 0;
	if (!check_top_row_closed(textures) || !check_bottom_row_closed(textures))
		return (0);
	while (i < last_index)
	{
		if (!check_sides_closed(textures, i)
			|| !check_row_closure(textures, i))
			return (0);
		i++;
	}
	return (1);
}
