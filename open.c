/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:53:02 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/29 17:31:59 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void	count_lines(char **argv, t_textures *textures, int fd, char *line)
{
	int line_count = 0;
	int map_started = 0;
	(void)argv;
	while (line != NULL && textures->found == 6)
	{
		int i = 0;
		while (line[i] && check_space(line[i]))
			i++;
		if (!map_started && (line[i] == '1' || line[i] == '0'))
			map_started = 1;
		if (map_started)
		{
			if (line[i] != '\0' && line[i] != '\n')
				line_count++;
		}
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	textures->how_many_lines = line_count;
	printf("Map lines count -> %d\n", textures->how_many_lines);
	close(fd);
}

void open_close_file(char **argv, t_textures *textures)
{
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_fun(textures);
	line = get_next_line(fd);
	while (line != NULL && textures->found < 6)
	{
		checking_textures(textures, line);
		checking_color(textures, line);
		all_found(textures);
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	if (textures->found != 6)
	{
		printf("text %d\n", textures->found);
		close(fd);
		printf("KUKU\n");
		error_fun(textures);
	}
	count_lines(argv,textures,fd, line);

	//opening new fd
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_fun(textures);
	line = get_next_line(fd);
 	int map_started = 0;
	textures->map = malloc(sizeof(char*) * (textures->how_many_lines + 1));
	if (!textures->map)
	{
		close(fd);
		error_fun(textures);
	}
	textures->map[textures->how_many_lines] = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("Searching for map start, line: %s\n", line);
		if (!map_started)
		{
			int i = 0;
			while (line[i] && (line[i] == ' ' || line[i] == '\t'))
				i++;
			if (line[i] == '1' || line[i] == '0') 
				map_started = 1;
		}
		if (map_started)
		{
			if (*line =='\n')
				closing(textures,line, fd);
			if (*line != '\n')
			{
				textures->map_valid = checking_map(textures, line);
				if (!textures->map_valid)
					closing(textures,line, fd);
				if (textures->map_index >= textures->how_many_lines)
					error_fun(textures);
				textures->map[textures->map_index] = ft_strdup(line);
				if (!textures->map[textures->map_index])
				{
					free(line);
					close(fd);
					error_fun(textures);
				}
				textures->map_index++;
			}
		}
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	textures->map[textures->map_index] = NULL;
	if(textures->player_found == 0)
		error_fun(textures);
	textures->how_many_lines = textures->map_index;
	printf("OLD\n");
	for (int i = 0; i < textures->how_many_lines; i++)
		printf("Map line %d: %s", i, textures->map[i]);
	printf("\n");
	replacing_spaces_with_one(textures);
	printf("NEW after 1\n");
	for (int i = 0; i < textures->how_many_lines; i++)
		printf("Map line %d: %s", i, textures->map[i]);
	replacing_nl_with_zero(textures);
	printf("NEW\n");
	for (int i = 0; i < textures->how_many_lines; i++)
		printf("Map line %d: %s", i, textures->map[i]);
	if_new_line_in_middle(textures);
	printf("Map lines count -> %d\n", textures->how_many_lines);
	if (!map_closed(textures))
		error_fun(textures);
	if (textures->how_many_lines < 3) {
		close(fd);
		error_fun(textures);
	}
	free(line);
	close(fd);
}