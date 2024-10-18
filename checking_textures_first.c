/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_textures_first.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:58:13 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/18 15:06:33 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void if_all_6_found(t_textures *textures, int fd)
{
	int line_count;
	int map_started;
	int i;

	i = 0;
	map_started = 0;
	line_count = 0;
	if(textures->found == 6)
	{
		while (textures->line != NULL)
		{
			i = 0;
			if (!map_started && (textures->line [i] == '1' || textures->line [i] == '0'
				 || textures->line[i] == ' '))
				map_started = 1;
			if (map_started)
			{
				if (textures->line [i] != '\0' && textures->line [i] != '\n')
					line_count++;
			}
			free(textures->line );
			textures->line  = NULL;
			textures->line  = get_next_line(fd);
		}
		textures->how_many_lines = line_count;
	}
}

void checking_validity(t_textures *textures, int fd )
{
	if_all_6_found(textures, fd);
	if (textures->found != 6)
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


void checking_the_info( t_textures *textures, int i)
{
	if (ft_strncmp(&textures->line[i], "NO", 2) == 0 || 
	ft_strncmp(&textures->line[i], "SO", 2) == 0 || 
	ft_strncmp(&textures->line[i], "WE", 2) == 0 || 
	ft_strncmp(&textures->line[i], "EA", 2) == 0 || 
	ft_strncmp(&textures->line[i], "F", 1) == 0  || 
	ft_strncmp(&textures->line[i], "1", 1) == 0  ||
	ft_strncmp(&textures->line[i], "0", 1) == 0  ||
	ft_strncmp(&textures->line[i], " ", 1) == 0  ||
	ft_strncmp(&textures->line[i], "C", 1) == 0)
{
	checking_textures(textures, textures->line);
	checking_color(textures, textures->line);
}
else
	error_fun(textures);
}


void open_first(int fd, char **argv, t_textures *textures)
{
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_fun(textures);
	
	textures->line = get_next_line(fd);
	while (textures->line != NULL)
	{
		int i = 0;
		if (textures->line[i] == '\0' || textures->line[i] == '\n')
		{
			free(textures->line);
			textures->line = get_next_line(fd);
			continue;
		}
		checking_the_info(textures, i);
		free(textures->line);
		textures->line = NULL;
		textures->line = get_next_line(fd);
	}
	all_found(textures);
	close (fd);
}