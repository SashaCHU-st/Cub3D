/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:53:02 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/23 14:30:30 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_last(t_textures *textures, char *line, int fd)
{
	if (textures->found < 6)// esli zakonchilsya loop no ne vse nashlis'
	{
		close(fd);
		error_fun();
	}
	textures->map = malloc(sizeof(char*)*(textures->how_many_lines + 1));
	if(!textures->map[textures->how_many_lines])
		error_fun();
	while (line != NULL)
	{
		textures->map_valid = checking_map(textures, line);
		if (!textures->map_valid)
		{
			printf("KUKU\n");
			free(line);
			close(fd);
			error_fun();
		}
		count_lines(textures, line);
		textures->map[textures->how_many_lines] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	for (int i = 1; i <= textures->how_many_lines; i++)
	{
		printf("Map line %d: %s", i, textures->map[i]);
	}
	printf("\n");
	for (int i = 1; i <= textures->how_many_lines; i++)
	{
		printf("=>%c\n", textures->map[i][0]);
		if(textures->map[i][0] == '\n')
		{
			printf("KUKU\n");
			error_fun();
		}
	}
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
	if(textures->how_many_lines < 3)
	{
		close(fd);		
		error_fun();
	}
	printf("Number of map lines: %d\n", textures->how_many_lines);
	close(fd);
}
