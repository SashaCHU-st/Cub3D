/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:53:02 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/26 11:50:35 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void map_last(t_textures *textures, char *line, int fd)
{
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
	while (line != NULL)
	{
		if (*line =='\n' && map_started) 
		{
			free(line);
			close(fd);
			error_fun();
		}

		if (*line !='\n')
		{
			map_started = 1;
			textures->map_valid = checking_map(textures, line);
			if (!textures->map_valid)
			{
				printf("Error: Invalid map line\n");
				free(line);
				close(fd);
				error_fun();
			}
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
	printf("\n");
	for (int i = 0; i < textures->how_many_lines; i++)
	{
		if (textures->map[i][0] == '\n')
		{
			error_fun();
		}
	}
}

// void scan_the_map(t_textures *textures)
// {
// 	int length = 0;
// 	int i = 0;
// 	length = ft_strlen(check_space(textures->map[0]));
// 	printf("length = %d\n", length - 1);
// 	while (i < length -1)
// 	{
// 		if(textures->map[0][i] != '1')
// 			error_fun();
// 		i++;
// 	}
// 	length = ft_strlen(textures->map[textures->how_many_lines - 1]);
// 	printf("Last length = %d\n", length);
// 	i = 0;
// 	while (i < length -1)
// 	{
// 		if(textures->map[textures->how_many_lines - 1][i] != '1')
// 			error_fun();
// 		i++;
// 	}

	
// }



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
