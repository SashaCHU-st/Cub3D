/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:53:02 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/18 17:12:45 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void checking_validity(t_textures *textures, int fd )
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
	textures->found = textures->found_no+textures->found_so+textures->found_we+textures->found_ea+textures->found_c + textures->found_f;
	all_found(textures);
	close (fd);
}

void map_started_fun (int map_started, int i, t_textures *textures, int fd)
{
	if (map_started)
	{
		if (textures->line[i] =='\n')
			closing(textures, fd);
		if (textures->line[i] != '\n')
		{
			textures->map_valid = checking_map(textures, textures->line, textures->map_index);
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

void open_second(int fd, char **argv, t_textures *textures)
{
 	int map_started = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_fun(textures);
	textures->line = get_next_line(fd);
	textures->map = malloc(sizeof(char*) * (textures->how_many_lines + 1));
	if (!textures->map)
	{
		close(fd);
		error_fun(textures);
	}
	for(int i = 0; i < textures->how_many_lines; i++)
		textures->map[i] = NULL;
	int j = 0;
	while (textures->line  != NULL)
	{
		int i = 0;
		if (!map_started)
		{
			if (textures->line[i] == '1' || textures->line[i] == '0' || textures->line[i] == ' ') 
				map_started = 1;
			j++;
		}
		map_started_fun(map_started, i, textures, fd);
		free(textures->line);
		textures->line = NULL;
		textures->line = get_next_line(fd);
	}
	if(!map_started)
		error_fun(textures);
	if(textures->player_found == 0)
		error_fun(textures);

	if_new_line_in_middle(textures);
	replacing_spaces_with_one(textures);
	textures->map[textures->map_index] = NULL;
	textures->how_many_lines = textures->map_index;
	replacing_nl_with_zero(textures);
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

void open_close_file(char **argv, t_textures *textures)
{

	int		fd = 0;
	open_first(fd, argv, textures);
	count_lines(argv,textures,fd);
	open_second(fd, argv, textures);
	//printf("1\n");
	textures->no_side = mlx_load_png(textures->no);  //NEEDS A CHECK FOR TEXTURE DIMENSIONS they need to be all the same (e.g. 64 x 64)
	if(!textures->no_side)
		error_fun(textures);
	//printf("2\n");
	textures->so_side = mlx_load_png(textures->so); //also free the previous pngs
	if(!textures->so_side)
		error_fun(textures);
//	printf("3\n");
	textures->we_side = mlx_load_png(textures->we);
	if(!textures->we_side)
		error_fun(textures);
//	printf("4\n");
	textures->ea_side = mlx_load_png(textures->ea);
	if(!textures->ea_side)
		error_fun(textures);
}
