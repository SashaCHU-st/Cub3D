/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:53:02 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/21 09:44:25 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	checking_validity(t_textures *textures, int fd )
{
	int	line_count;
	int	map_started;
	int	i;

	i = 0;
	map_started = 0;
	line_count = 0;
	if (textures->found == 6)
	{
		while (textures->line != NULL)
		{
			i = 0;
			if (!map_started && (textures->line [i] == '1'
					|| textures->line [i] == '0' || textures->line[i] == ' '))
				map_started = 1;
			if (map_started)
			{
				if (textures->line [i] != '\0' && textures->line [i] != '\n')
					line_count++;
			}
			free(textures->line);
			textures->line = NULL;
			textures->line = get_next_line(fd);
		}
		textures->how_many_lines = line_count;
	}
	else if (textures->found != 6)
	{
		close(fd);
		error_fun(textures);
	}
}

void	count_lines(char **argv, t_textures *textures, int fd)
{
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_fun(textures);
	textures->line = get_next_line(fd);
	checking_validity(textures, fd);
	close(fd);
}

void	checking_the_info( t_textures *textures, int i)
{
	if (ft_strncmp(&textures->line[i], "NO", 2) == 0
		|| ft_strncmp(&textures->line[i], "SO", 2) == 0
		|| ft_strncmp(&textures->line[i], "WE", 2) == 0
		|| ft_strncmp(&textures->line[i], "EA", 2) == 0
		|| ft_strncmp(&textures->line[i], "F", 1) == 0
		|| ft_strncmp(&textures->line[i], "1", 1) == 0
		|| ft_strncmp(&textures->line[i], "0", 1) == 0
		|| ft_strncmp(&textures->line[i], " ", 1) == 0
		|| ft_strncmp(&textures->line[i], "C", 1) == 0)
	{
		checking_textures(textures, textures->line);
		checking_color(textures, textures->line);
	}
	else
		error_fun(textures);
}

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
				error_fun(textures);
			}
			textures->map_index++;
		}
	}
}
