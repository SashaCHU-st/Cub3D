/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:53:02 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/09 12:21:15 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void	count_lines(char **argv, t_textures *textures, int fd)
{
	int line_count = 0;
	int map_started = 0;
	(void)argv;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_fun(textures);
	textures->line = get_next_line(fd);
	printf("FFFF %d\n",textures->found);
	if(textures->found == 6)
	{
		while (textures->line != NULL)
		{
		printf("HELO\n");
			int i = 0;
			// while (textures->line[i] && check_space(textures->line [i]))
			// 	i++;
			if (!map_started && (textures->line [i] == '1' || textures->line [i] == '0' || textures->line[i] == ' '))
				map_started = 1;
			if (map_started)
			{
				if (textures->line [i] != '\0' && textures->line [i] != '\n')
					line_count++;
			}
			free(textures->line );
			textures->line  = NULL;
			textures->line  = get_next_line(fd);
			printf("line counts%d\n", line_count);
		}
		textures->how_many_lines = line_count;
		printf("Map lines count -> %d\n", textures->how_many_lines);
		printf("FFFF %d\n",textures->found);
	}
	else if (textures->found != 6)
	{
		printf("text %d\n", textures->found);
		close(fd);
		printf("KUKU\n");
		error_fun(textures);
	}
	close(fd);
}

// int	some_rubish_fun(t_textures *textures)
// {
// 	int i = 0;
// 	 if (ft_strncmp(&textures->line[i], "NO", 2) == 0 || 
// 		ft_strncmp(&textures->line[i], "SO", 2) == 0 || 
// 		ft_strncmp(&textures->line[i], "WE", 2) == 0 || 
// 		ft_strncmp(&textures->line[i], "EA", 2) == 0 || 
// 		ft_strncmp(&textures->line[i], "F", 1) == 0  || 
// 		ft_strncmp(&textures->line[i], "C", 1) == 0)  ||
// 		ft_strncmp(&textures->line[i], "1", 1) == 0)  ||
// 		return(0);
// 	else
// 		return(1);
// }

void open_close_file(char **argv, t_textures *textures)
{

	int		fd;
	// char	*line;

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
		{
			printf("TTTTT\n");
			error_fun(textures);
		}
		free(textures->line);
		textures->line = NULL;
		textures->line = get_next_line(fd);
	}
	textures->found = textures->found_no+textures->found_so+textures->found_we+textures->found_ea+textures->found_c + textures->found_f;
	printf("HHHH %d\n", textures->found);
	printf("FFFF %d\n",textures->found);
	all_found(textures);
	// if(textures->found != 6)
	// {
	// 	printf("OOOOOO\n");
	// }
	close (fd);
	// if (textures->found != 6)
	// {
	// 	printf("text %d\n", textures->found);
	// 	close(fd);
	// 	printf("KUKU\n");
	// 	error_fun(textures);
	// }
	// all_found(textures);
	count_lines(argv,textures,fd);
	
	//printf("HYHYHY\n");
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
			//printf("HELLO %d\n", i);
	int j = 0;
	while (textures->line  != NULL)
	{
		int i = 0;
		if (!map_started)
		{
			// while (textures->line[i] && (textures->line[i] == ' ' || textures->line[i] == '\t'))
			// 	i++;
			printf("I %d\n", i);
			if (textures->line[i] == '1' || textures->line[i] == '0' || textures->line[i] == ' ') 
				map_started = 1;
			j++;
			printf("JJJ %d\n", j);
		}
		if (map_started)
		{
			printf("****\n");
			printf("I =>%d\n",i);
			printf("textures->line[i] %c\n",textures->line[i] );
			if (textures->line[i] =='\n')
			{
				printf("IIII\n");
				closing(textures,textures->line, fd);
			}
			if (textures->line[i] != '\n')
			{
				//replacing_spaces_with_one(textures);
				textures->map_valid = checking_map(textures, textures->line, textures->map_index);
				if (!textures->map_valid)
				{
					printf("Not valid\n");
					closing(textures,textures->line, fd);
				}
				printf("textures->map_index %d\n", textures->map_index);
				printf("textures->how_many_lines %d\n", textures->how_many_lines);
				if (textures->map_index > textures->how_many_lines)
				{
					printf("how any lines\n");
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
		free(textures->line);
		textures->line = NULL;
		textures->line = get_next_line(fd);
	}
	replacing_spaces_with_one(textures);
	textures->map[textures->map_index] = NULL;
	if(textures->player_found == 0)
		error_fun(textures);
	textures->how_many_lines = textures->map_index;
	printf("OLD\n");
	for (int i = 0; i < textures->how_many_lines; i++)
		printf("Map line %d: %s", i, textures->map[i]);
	printf("\n");
	//replacing_spaces_with_one(textures);
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
	{
		printf("not closed\n");
		error_fun(textures);
	}
	if (textures->how_many_lines < 3)
	{
		free(textures->line);
		close(fd);
		error_fun(textures);
	}
	free(textures->line);
	close(fd);
	printf("tttt %d\n", textures->floor);
}