/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_started.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:38:18 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/22 16:44:34 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_started_fun(int map_started, int i, t_textures *textures, int fd)
{
	if (map_started)
	{
		if (textures->line[i] == '\n')
			closing(textures, fd);
		if (textures->line[i] != '\n')
		{
			textures->map_valid = checking_map(textures,
					textures->line, textures->map_index);
			if (!textures->map_valid)
				closing(textures, fd);
			if (textures->map_index > textures->how_many_lines)
			{
				error_fun(textures);
			}
			textures->map[textures->map_index] = ft_strdup(textures->line);
			if (!textures->map[textures->map_index])
			{
				free(textures->line);
				close(fd);
				error_fun(textures); //does it return from this?
			}
			textures->map_index++;
		}
	}
}

void	reading_lines(int fd, t_textures *textures, int i)
{
	textures->line = get_next_line(fd); //what if get_next returns NULL?
	if (!textures->line)
	{
		printf("Failed get_next_line\n");
		error_fun(textures);
	}
	textures->map = malloc(sizeof(char *) * (textures->how_many_lines + 1));
	if (!textures->map)
	{
		close(fd);
		error_fun(textures);
	}
	while (i < textures->how_many_lines)
	{
		textures->map[i] = NULL;
		i++;
	}
}

void	open_second(int fd, char **argv, t_textures *text)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Failed to open\n");
		error_fun(text);
	}
	reading_lines(fd, text, i);
	while (text->line != NULL)
	{
		i = 0;
		if (!text->map_started)
		{
			if (text->line[i] == '1' || text->line[i] == '0'
				|| text->line[i] == ' ')
				text->map_started = 1;
			j++;
		}
		map_started_fun(text->map_started, i, text, fd);
		free(text->line);
		text->line = NULL;
		text->line = get_next_line(fd);
	}
	finilizing(text->map_started, text, fd);
}

int	if_is_map_started(const char *line)
{
	if (line[0] == '1')
		return (1);
	else if (line[0] == '0')
		return (1);
	else if (line[0] == ' ')
		return (1);
	else
		return (0);
}

int	count_map_lines(t_textures *textures, int fd)
{
	int	line_count;
	int	map_started;

	line_count = 0;
	map_started = 0;
	while (textures->line != NULL)
	{
		if (!map_started && if_is_map_started(textures->line))
			map_started = 1;
		if (map_started)
		{
			if (textures->line[0] != '\0' && textures->line[0] != '\n')
				line_count++;
		}
		free(textures->line);
		textures->line = get_next_line(fd);
	}
	if (line_count >= 50)
	{
		printf("Too big map\n");
		error_fun(textures);
	}
	return (line_count);
}
