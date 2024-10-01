/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:53:02 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/01 13:08:57 by aheinane         ###   ########.fr       */
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
	if (textures->found != 6)
	{
		printf("text %d\n", textures->found);
		close(fd);
		printf("KUKU\n");
		error_fun(textures);
	}
	close(fd);
}

// int flood_fill(char **map, int rows, int cols, int x, int y)
// {
// 	if (x < 0 || x >= rows || y < 0 || y >= cols)
// 		return 0;
// 	if (map[x][y] == '1')
// 		return 1;
// 	if (map[x][y] == 'F')
// 		return 1;

// 	map[x][y] = 'F';
// 	int up = flood_fill(map, rows, cols, x - 1, y);
// 	int down = flood_fill(map, rows, cols, x + 1, y);
// 	int left = flood_fill(map, rows, cols, x, y - 1);
// 	int right = flood_fill(map, rows, cols, x, y + 1);

// 	if (up == 0 || down == 0 || left == 0 || right == 0)
// 		return 0;
// 	return 1;
// }



// int map_closed(t_textures *textures)
// {
// 	int rows = textures->how_many_lines;
// 	int cols = ft_strlen(textures->map[0]);
// 	int j = 0;
// 	int start_x = -1, start_y = -1;

// 	int i =0;
// 	while (i < rows)
// 	{
// 		j = 0;
// 		while( j < cols )
// 		{
// 			if (textures->map[i][j] == 'S' || textures->map[i][j] == 'N' || textures->map[i][j] == 'W' || textures->map[i][j] == 'E')
// 			{
// 				start_x = i;
// 				start_y = j;
// 				break;
// 			}
// 			j++;
// 		}
// 		if (start_x != -1)
// 		break;
// 		i++;
// 	}
// 	if (start_x == -1 || start_y == -1)
// 	{
// 		return 0;
// 	}
// 	if (!flood_fill(textures->map, rows, cols, start_x, start_y))
// 	{
// 		printf("kuku not closed!\n");
// 		return (0);
// 	}
// 	printf("kuku closed!\n");
// 	return (1);
// }

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
	// if (textures->found != 6)
	// {
	// 	printf("text %d\n", textures->found);
	// 	close(fd);
	// 	printf("KUKU\n");
	// 	error_fun(textures);
	// }
	count_lines(argv,textures,fd, textures->line);

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
	while (textures->line  != NULL)
	{
		//printf("line: %s\n", textures->line );
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
				textures->map_valid = checking_map(textures, textures->line, textures->map_index);
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
//	printf("OLD\n");
	//for (int i = 0; i < textures->how_many_lines; i++)
//printf("Map line %d: %s", i, textures->map[i]);
	printf("\n");
	replacing_spaces_with_one(textures);
	// printf("NEW after 1\n");
	// for (int i = 0; i < textures->how_many_lines; i++)
	// 	printf("Map line %d: %s", i, textures->map[i]);
	replacing_nl_with_zero(textures);
	// printf("NEW\n");
	// for (int i = 0; i < textures->how_many_lines; i++)
	// 	printf("Map line %d: %s", i, textures->map[i]);
	//if_new_line_in_middle(textures);
	//printf("Map lines count -> %d\n", textures->how_many_lines);
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
	printf("X %f\n",textures->play.x );
	printf("Y%f\n",textures->play.y );
}