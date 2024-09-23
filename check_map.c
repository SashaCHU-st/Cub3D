/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:12:50 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/23 11:53:24 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	all_found(t_textures *textures)
{
	int number = 0;
	number = textures->found_no + textures->found_so + textures->found_we
		 +textures->found_ea + textures->found_f +textures->found_c;
	if(number == 6)
		textures->found = 6;
}

int checking_map(t_textures *textures, char *line)
{
	int i = 0;
	(void)textures;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != '\n')
		{
			if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			{
				textures->player_found++;
				printf("!!!!!!%d\n", textures->player_found);
				if (textures->player_found > 1)
					error_fun();
			}
			else
				error_fun();
		}
		i++;
	}
	return (1);
}

void count_lines(t_textures *textures, char *line)
{
	int i = 0;
	int is_empty = 1;
	while (line[i] != '\0')
	{
		if (!check_space(line[i]) && line[i] != '\n')
		{
			is_empty = 0;
			break;
		}
		i++;
	}
	if (!is_empty)
		textures->how_many_lines++;
}