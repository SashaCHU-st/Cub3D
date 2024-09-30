
#include "cub3d.h"
int flood_fill(char **map, int rows, int cols, int x, int y)
{
	if (x < 0 || x >= rows || y < 0 || y >= cols)
		return 0;
	if (map[x][y] == '1')
		return 1;
	if (map[x][y] == 'F')
		return 1;

	map[x][y] = 'F';
	int up = flood_fill(map, rows, cols, x - 1, y);
	int down = flood_fill(map, rows, cols, x + 1, y);
	int left = flood_fill(map, rows, cols, x, y - 1);
	int right = flood_fill(map, rows, cols, x, y + 1);

	if (up == 0 || down == 0 || left == 0 || right == 0)
		return 0;
	return 1;
}



int map_closed(t_textures *textures)
{
	int rows = textures->how_many_lines;
	int cols = ft_strlen(textures->map[0]);
	int j = 0;
	int start_x = -1, start_y = -1;

	int i =0;
	while (i < rows)
	{
		j = 0;
		while( j < cols )
		{
			if (textures->map[i][j] == 'S' || textures->map[i][j] == 'N' || textures->map[i][j] == 'W' || textures->map[i][j] == 'E')
			{
				start_x = i;
				start_y = j;
				break;
			}
			j++;
		}
		if (start_x != -1)
		break;
		i++;
	}
	if (start_x == -1 || start_y == -1)
	{
		return 0;
	}
	if (!flood_fill(textures->map, rows, cols, start_x, start_y))
	{
		printf("kuku not closed!\n");
		return (0);
	}
	printf("kuku closed!\n");
	return (1);
}