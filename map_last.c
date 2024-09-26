#include "cub3d.h"


void	replacing_nl(t_textures *textures)
{
	for (int i = 0; i < textures->how_many_lines; i++)
	{
		int length = ft_strlen(textures->map[i]);
		for (int j = 0; j < length; j++)
		{
			if (textures->map[i][j] == '\n')
				textures->map[i][j] = '\0';
		}
	}
}

void if_new_line_in_middle(t_textures *textures)
{
	int i = 0;
	while(i < textures->how_many_lines)
	{
		if (textures->map[i][0] == '\n')
			error_fun();
		i++;
	}
}

void	can_start_map(t_textures *textures, int fd)
{
	if (textures->found < 6)
	{
		close(fd);
		error_fun();
	}
	textures->map = malloc(sizeof(char*) * (textures->how_many_lines + 1));
	if (!textures->map)
		error_fun();
}


void parsing_map(t_textures *textures, char *line, int fd)
{
	int map_started = 0;
	while (line != NULL)
	{
		if (*line =='\n' && map_started)
			closing(line, fd);
		if (*line !='\n')
		{
			map_started = 1;
			textures->map_valid = checking_map(textures, line);
			if (!textures->map_valid)
				closing(line, fd);
			textures->map[textures->map_index] = ft_strdup(line);
			if (!textures->map[textures->map_index])
				error_fun();
			textures->map_index++;
		}
		free(line);
		line = get_next_line(fd);
	}
}

void map_last(t_textures *textures, char *line, int fd)
{
	can_start_map(textures,fd);
	parsing_map(textures, line, fd);
	textures->how_many_lines = textures->map_index;
	for (int i = 0; i < textures->how_many_lines; i++)
		printf("Map line %d: %s", i, textures->map[i]);
	replacing_nl(textures);
	for (int i = 0; i < textures->how_many_lines; i++)
		printf("Map line %d: %s", i, textures->map[i]);
	if_new_line_in_middle(textures);
}