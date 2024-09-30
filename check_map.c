/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:12:50 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/30 13:24:42 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	all_found(t_textures *textures)
{
	printf("1 %d\n", textures->found_no);
	printf("2 %d\n", textures->found_so);
	printf("3 %d\n", textures->found_we);
	printf("4 %d\n", textures->found_ea);
	printf("5 %d\n", textures->found_f);
	printf("6 %d\n", textures->found_c);
	//textures->found = textures->found_no+textures->found_so+textures->found_we+textures->found_ea+textures->found_c + textures->found_f;
	if(textures->found_no == 1 && textures->found_so == 1 && textures->found_we == 1 && textures->found_we == 1
		&& textures->found_ea == 1 && textures->found_f == 1 && textures->found_c == 1)
		textures->found = textures->found_no+textures->found_so+textures->found_we+textures->found_ea+textures->found_c + textures->found_f;
	printf("HHHH %d\n", textures->found);
}

int	checking_map(t_textures *textures, char *line)
{
	int i = 0;
	(void)textures;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != '\n' && line[i] != '\t' )//&& line[i] != '\t'?????
		{
			if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			{
				textures->player_found++;
				if (textures->player_found > 1 || textures->player_found == 0)
					error_fun(textures);
			}
			else
			{
				printf("HHHH\n");
				error_fun(textures);
			}
		}
		i++;
	}
	return (1);
}