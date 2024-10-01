/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:53:02 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/01 14:51:24 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

void open_close_file(char **argv)
{
	int fd;
	char *line;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("ERROR: Could not open the file.\n");
		return;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}

	textures->how_many_lines = line_count;
	printf("Map lines count -> %d\n", textures->how_many_lines);
	close(fd);
}
int map_closed(t_textures *textures)
{
	int i = 0;
	int j;
	while (textures->map[0][i])
	{
		if (textures->map[0][i] != '1')
			return 0;
		i++;
	}
	i = 0;
	while (textures->map[textures->how_many_lines - 1][i])
	{
		if (textures->map[textures->how_many_lines - 1][i] != '1')
			return 0;
		i++;
	}
	i = 0;
	while (i < textures->how_many_lines - 1)
	{
		int first = ft_strlen(textures->map[i]);
		int next = ft_strlen(textures->map[i + 1]);
		if (textures->map[i][0] != '1')
			return 0;
		if (textures->map[i][first - 1] != '1')
			return 0;
		if (first < next)
		{
			if (textures->map[i + 1][first - 1] != '1')
				return 0;
			j = first;
			while (j < next)
			{
				if (textures->map[i + 1][j] != '1')
					return 0;
				j++;
			}
		}
		else if (first > next)
		{
			if (textures->map[i + 1][next - 1] != '1')
				return 0;
			j = next;
			while (j < first)
			{
				if (textures->map[i][j] != '1')
					return 0;
				j++;
			}
		}
		
		i++;
	}

	return 1;
}


void open_close_file(char **argv, t_textures *textures)
{
	int		fd;
	// char	*line;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_fun(textures);
	textures->line = get_next_line(fd);
	while (textures->line != NULL && textures->found < 6)
	{
		checking_textures(textures, textures->line);
		checking_color(textures, textures->line);
		all_found(textures);
		free(textures->line);
		textures->line = NULL;
		textures->line = get_next_line(fd);
	}
	if (textures->found != 6)
	{
		printf("text %d\n", textures->found);
		close(fd);
		printf("KUKU\n");
		error_fun(textures);
	}
	count_lines(argv,textures,fd, textures->line);

	printf("HYHYHY\n");
	//opening new fd
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_fun(textures);
	textures->line = get_next_line(fd);
 	int map_started = 0;
	textures->map = malloc(sizeof(char*) * (textures->how_many_lines + 1));
	if (!textures->map)
	{
		close(fd);
		error_fun(textures);
	}
	for(int i = 0; i < textures->how_many_lines; i++)
		textures->map[i] = NULL;
	while (textures->line  != NULL)
	{
		printf("line: %s\n", textures->line );
		if (!map_started)
		{
			int i = 0;
			while (textures->line[i] && (textures->line[i] == ' ' || textures->line[i] == '\t'))
				i++;
			if (textures->line[i] == '1' || textures->line[i] == '0') 
				map_started = 1;
		}
		if (map_started)
		{
			if (*textures->line =='\n')
				closing(textures,textures->line, fd);
			if (*textures->line != '\n')
			{
				textures->map_valid = checking_map(textures, textures->line);
				if (!textures->map_valid)
					closing(textures,textures->line, fd);
				if (textures->map_index >= textures->how_many_lines)
					error_fun(textures);
				textures->map[textures->map_index] = ft_strdup(textures->line);
				if (!textures->map[textures->map_index])
				{
					free(textures->line);
					close(fd);
					error_fun(textures);
				}
				textures->map_index++;
			}
		}
		free(textures->line);
		textures->line = NULL;
		textures->line = get_next_line(fd);
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
	//if_new_line_in_middle(textures);
	printf("Map lines count -> %d\n", textures->how_many_lines);
	if (!map_closed(textures))
		error_fun(textures);
	if (textures->how_many_lines < 3)
	{
		free(textures->line);
		close(fd);
		error_fun(textures);
	}
	free(textures->line);
	close(fd);
}