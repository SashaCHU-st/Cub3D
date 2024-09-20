/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:53:02 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/20 15:53:20 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validation(t_textures *text)
{
	if (text->found == 6)
		printf("All good\n");
	else
	{
		printf(" Not good good\n");
		error_fun();
	}
}


int checking_map(t_textures *textures, char *line)
{
	int i = 0;
	if(textures->found == 6)
	{
		int h = 0;
		while (line[i])
		{
			if (line[i] != '1' && line[i] != '0' && line[i] != ' ' &&
				(line[i] != 'N' || line[i] != 'S' || line[i] != 'E' || line[i] != 'W' ))
				{
					printf("HELLLLLOOO %d\n", h);
					return (0);
				}
				h++;
			i++;
		}
	}
	return (1);
}

void	open_close_file(char **argv, t_textures *textures)
{
	int		fd;
	char	*line;
	
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	if (fd < 0)
		error_fun();
	while (line != NULL)
	{
		checking_textures(textures, line);
		checking_color(textures, line);
		checking_map(textures, line);
		free(line);
		line = get_next_line(fd);
		textures->how_many_lines++;
	}
	// printf("!!!!!!%d\n", textures->how_many_lines);
	// textures->map_valid = validation(textures);
	// if (!textures->map_valid)
	// 	error_fun();
	close(fd);
}
