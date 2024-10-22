/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:12:50 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/22 17:01:57 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	all_found(t_textures *textures)
{
	if (textures->found_no == 1 && textures->found_so == 1
		&& textures->found_we == 1
		&& textures->found_we == 1
		&& textures->found_ea == 1
		&& textures->found_f == 1
		&& textures->found_c == 1)
		textures->found = textures->found_no + textures->found_so
			+ textures->found_we + textures->found_ea
			+ textures->found_c + textures->found_f;
	else
	{
		printf("Some element missing\n");
		error_fun(textures);
	}
}

void	when_player_found(t_textures *textures, char *line, int i)
{
	if (line[i] == 'N')
	{
		textures->sides = 'N';
		textures->play.angle = 270;
	}
	if (line[i] == 'S')
	{
		textures->sides = 'S';
		textures->play.angle = 90;
	}
	if (line[i] == 'W')
	{
		textures->sides = 'W';
		textures->play.angle = 360;
	}
	if (line[i] == 'E')
	{
		textures->sides = 'E';
		textures->play.angle = 180;
	}
}

void	more_then_one(t_textures *textures)
{
	printf("More then one player\n");
	error_fun(textures);
}

void	no_player(t_textures *textures)
{
	printf("No player\n");
	error_fun(textures);
}

int	checking_map(t_textures *textures, char *line, int n)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' '
			&& line[i] != '\n' && line[i] != '\t' )
		{
			if (line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'E' || line[i] == 'W')
			{
				when_player_found(textures, line, i);
				textures->play.x = i + 0.5;
				textures->play.y = n + 0.5;
				textures->player_found++;
				if (textures->player_found > 1 || textures->player_found == 0)
					more_then_one(textures);
			}
			else
				no_player(textures);
		}
		i++;
	}
	return (1);
}
