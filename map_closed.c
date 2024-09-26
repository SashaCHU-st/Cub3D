
#include "cub3d.h"
void flood_fill(t_textures *textures, int x, int y)
{
	if (x < 0 || x >= textures->how_many_lines || y < 0 || y >= ft_strlen(textures->map[x]))
		return;
	if (textures->map[x][y] == '1' || textures->map[x][y] == 'F')
		return;
	textures->map[x][y] = 'F';
	flood_fill(textures, x + 1, y);
	flood_fill(textures, x - 1, y);
	flood_fill(textures, x, y + 1);
	flood_fill(textures, x, y - 1);
}

int map_closed(t_textures *textures)
{
	for (int i = 0; i < textures->how_many_lines; i++)
	{
		int length = ft_strlen(textures->map[i]) - 1;
		if (textures->map[i][0] == '0')
			flood_fill(textures, i, 0);
		if (textures->map[i][length] == '0')
			flood_fill(textures, i, ft_strlen(textures->map[i]) - 1);
	}
	for (int j = 0; j < ft_strlen(textures->map[0]); j++)
	{
		if (textures->map[0][j] == '0')
			flood_fill(textures, 0, j);
		if (textures->map[textures->how_many_lines - 1][j] == '0')
			flood_fill(textures, textures->how_many_lines - 1, j);
	}
	for (int i = 0; i < textures->how_many_lines; i++)
	{
		for (int j = 0; j < ft_strlen(textures->map[i]); j++)
		{
			if (textures->map[i][j] == '0')
			{
				printf("Map is fully enclosed.\n");
				return (1);
			}
		}
	}
	printf("Map is not fully enclosed\n");
	return (0);
}