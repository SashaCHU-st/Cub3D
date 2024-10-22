/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:25:32 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/22 16:43:40 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	replacing_nl_with_zero(t_textures *textures)
{
	int	i;
	int	j;
	int	length;

	i = 0;
	while (i < textures->how_many_lines)
	{
		if (textures->map[i])
		{
			length = ft_strlen(textures->map[i]);
			j = 0;
			while (j < length)
			{
				if (textures->map[i][j] == '\n')
					textures->map[i][j] = '\0';
				j++;
			}
		}
		i++;
	}
}

void	for_last_one(t_textures *textures, int j)
{
	int	length2;

	if (textures->how_many_lines > 0
		&& textures->map[textures->how_many_lines - 1] != NULL)
	{
		length2 = ft_strlen(textures->map[textures->how_many_lines - 1]);
		j = 0;
		while (j < length2)
		{
			if (textures->map[textures->how_many_lines - 1][j] == ' ')
				textures->map[textures->how_many_lines - 1][j] = '1';
			j++;
		}
	}
}

void	replacing_spaces_with_one(t_textures *textures)
{
	int	i;
	int	j;
	int	length;

	i = 0;
	while (i < textures->how_many_lines)
	{
		if (textures->map[i] != NULL)
		{
			length = ft_strlen(textures->map[i]);
			j = 0;
			while (j < length)
			{
				if (textures->map[i][j] == ' ')
					textures->map[i][j] = '1';
				j++;
			}
		}
		i++;
	}
	for_last_one(textures, j);
}

void	if_new_line_in_middle(t_textures *textures)
{
	int	i;

	i = 0;
	while (i < textures->how_many_lines)
	{
		if (textures->map[i][0] == '\0' || (textures->map[i][0] == '\n'
			&& textures->map[i][1] == '\0'))
		{
			printf("Line in the middle of the map\n");
			error_fun(textures);
		}
		i++;
	}
}
