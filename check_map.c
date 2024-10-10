/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:12:50 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/10 12:19:51 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	all_found(t_textures *textures)
{
	if(textures->found_no == 1 && textures->found_so == 1 && textures->found_we == 1 && textures->found_we == 1
		&& textures->found_ea == 1 && textures->found_f == 1 && textures->found_c == 1)
		textures->found = textures->found_no+textures->found_so+textures->found_we+textures->found_ea+textures->found_c + textures->found_f;
	else
		error_fun(textures);
}

int	checking_map(t_textures *textures, char *line, int number)
{
	int i = 0;
	(void)textures;
	(void)number;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != '\n' && line[i] != '\t' )
		{
			if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			{
				if(line[i] == 'N')
					textures->sides = 'N';
				if(line[i] == 'S')
					textures->sides = 'S';
				if(line[i] == 'W')
					textures->sides = 'W';
				if(line[i] == 'E')
					textures->sides = 'E';
				textures->play.x = i*32;
				textures->play.y = number*32;
				textures->player_found++;
				if (textures->player_found > 1 || textures->player_found == 0)
					error_fun(textures);
			}
			else
				error_fun(textures);
		}
		i++;
	}
	return (1);
}