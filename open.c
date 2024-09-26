/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:53:02 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/26 13:06:05 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void map_last(t_textures *textures, char *line, int fd)
{
	printf("UKU\n");
	if (textures->found < 6)
	{
		close(fd);
		error_fun();
	}
	textures->map = malloc(sizeof(char*) * (textures->how_many_lines + 1));
	if (!textures->map)
		error_fun();

	int map_index = 0;
	int map_started = 0;
	printf("UKU1\n");
	while (line != NULL)
	{
		if (*line =='\n' && map_started)
			closing(line, fd);
		if (*line !='\n')
		{
			printf("UKU2\n");
			map_started = 1;
			textures->map_valid = checking_map(textures, line);
			printf("!!!%d\n", textures->map_valid);
			if (!textures->map_valid)
				closing(line, fd);
			textures->map[map_index] = ft_strdup(line);
			if (!textures->map[map_index])
				error_fun();
			map_index++;
		}
		free(line);
		line = get_next_line(fd);
	}
	textures->how_many_lines = map_index;
	for (int i = 0; i < textures->how_many_lines; i++)
	{
		printf("Map line %d: %s", i, textures->map[i]);
	}
	
	for (int i = 0; i < textures->how_many_lines; i++)
	{
		int length = ft_strlen(textures->map[i]);
		for (int j = 0; j < length; j++)
		{
			if (textures->map[i][j] == 32)
				textures->map[i][j] = '1';
		}
	}

	printf("\n");
	printf("\n");
	for (int i = 0; i < textures->how_many_lines; i++)
	{
		printf("Map line %d: %s", i, textures->map[i]);
	}
	for (int i = 0; i < textures->how_many_lines; i++)
	{
		if (textures->map[i][0] == '\n')
		{
			
			error_fun();
		}
	}
	printf("UKU\n");
}

void open_close_file(char **argv, t_textures *textures)
{
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_fun();
	line = get_next_line(fd);
	while (line != NULL && textures->found < 6)
	{
		checking_textures(textures, line);
		checking_color(textures, line);
		all_found(textures);
		free(line);
		line = get_next_line(fd);
	}
	map_last(textures,line, fd);
	//scan_the_map(textures);
	
	if(textures->how_many_lines < 3)
	{
		close(fd);		
		error_fun();
	}
	printf("Number of map lines: %d\n", textures->how_many_lines);
	close(fd);
}
