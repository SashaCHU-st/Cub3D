/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:53:02 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/24 12:49:02 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	checking_validity(t_textures *textures, int fd)
{
	if (textures->found == 6)
	{
		textures->how_many_lines = count_map_lines(textures, fd);
	}
	else
		closing(textures, fd, "Not all elements found\n");
}

void	scanning_map(char **argv, t_textures *textures, int fd)
{
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_fun(textures, "Cannot open file\n");
	textures->line = get_next_line(fd);
	if (!textures->line)
		closing(textures, fd, "get_next_line failed\n");
	checking_validity(textures, fd);
	close(fd);
}

void	checking_the_info( t_textures *textures, int i, int fd)
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
		checking_textures(textures, textures->line, fd);
		checking_color(textures, textures->line, fd);
	}
	else
		closing(textures, fd, "Invalid info in the file\n");
}

void	open_first(int fd, char **argv, t_textures *textures)
{
	int	i;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_fun(textures, "Cannot open file\n");
	textures->line = get_next_line(fd);
	while (textures->line != NULL)
	{
		i = 0;
		if (textures->line[i] == '\0' || textures->line[i] == '\n')
		{
			free(textures->line);
			textures->line = get_next_line(fd);
			continue ;
		}
		checking_the_info(textures, i, fd);
		free(textures->line);
		textures->line = NULL;
		textures->line = get_next_line(fd);
	}
	all_found(textures, fd);
	close (fd);
}

void	open_close_file(char **argv, t_textures *textures)
{
	int	fd;

	fd = 0;
	open_first(fd, argv, textures);
	scanning_map(argv, textures, fd);
	open_second(fd, argv, textures);
	uploading_text(textures, fd);
}
