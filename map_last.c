#include "cub3d.h"
void map_last(t_textures *textures, char *line, int fd)
{
	if (textures->found < 6)
	{
		close(fd);
		error_fun();
	}
	textures->map = malloc(sizeof(char*) * (textures->how_many_lines + 1));
	if (!textures->map)
		error_fun();

	int map_index = 0;
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
			textures->map[map_index] = ft_strdup(line);
			if (!textures->map[map_index])
				error_fun();
			map_index++;
		}
		free(line);
		line = get_next_line(fd);
	}
	textures->how_many_lines = map_index;
	for (int i = 0; i < textures->how_many_lines; i++)
	{
		printf("Map line %d: %s", i, textures->map[i]);
	}
	for (int i = 0; i < textures->how_many_lines; i++)
	{
		int length = ft_strlen(textures->map[i]);
		for (int j = 0; j < length; j++)
		{
			if (textures->map[i][j] == 32)
				textures->map[i][j] = '1';
		}
	}
	printf("\n");
	printf("\n");
	for (int i = 0; i < textures->how_many_lines; i++)
	{
		printf("Map line %d: %s", i, textures->map[i]);
	}
	int i = 0;
	while(i < textures->how_many_lines)
	{
		if (textures->map[i][0] == '\n')
			error_fun();
		i++;
	}
}