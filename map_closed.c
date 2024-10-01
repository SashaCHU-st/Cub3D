
#include "cub3d.h"
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
// 	int start_x = -1, start_y = -1;
// 	for (int i = 0; i < rows; i++)
// 	{
// 		for (int j = 0; j < cols; j++)
// 		{
// 			if (textures->map[i][j] == 'S' || textures->map[i][j] == 'N' || textures->map[i][j] == 'W' || textures->map[i][j] == 'E')
// 			{
// 				start_x = i;
// 				start_y = j;
// 				break;
// 			}
// 		}
// 		if (start_x != -1)
// 			break;
// 	}
// 	if (start_x == -1 || start_y == -1)
// 	{
// 		return 0;
// 	}
// 	if (!flood_fill(textures->map, rows, cols, start_x, start_y))
// 	{
// 		printf("kuku not closed!\n");
// 		return 0;
// 	}
// 	start_x = -1;
// 	start_y = -1;
	
// 	for (int i = 0; i < rows; i++)
// 	{
// 		for (int j = 0; j < cols; j++)
// 		{
// 			if (textures->map[i][j] == '0')
// 			{
// 				start_x = i;
// 				start_y = j;
// 				break;
// 			}
// 		}
// 		if (start_x != -1)
// 			break;
// 	}
// 	if (start_x == -1 || start_y == -1)
// 	{
// 		printf("No '0' found for second flood fill!\n");
// 		return 1;
// 	}
// 	if (!flood_fill(textures->map, rows, cols, start_x, start_y))
// 	{
// 		printf("kuku walls not closed!\n");
// 		return 0;
// 	}

// 	printf("kuku walls closed!\n");
// 	return 1;
// }




// int map_closed(t_textures *textures)
// {
// 	int i = 0;
// 	int j;
// 	while (textures->map[0][i])
// 	{
// 		if (textures->map[0][i] != '1')
// 			return 0;
// 		i++;
// 	}
// 	i = 0;
// 	while (textures->map[textures->how_many_lines - 1][i])
// 	{
// 		if (textures->map[textures->how_many_lines - 1][i] != '1')
// 			return 0;
// 		i++;
// 	}
// 	i = 0;
// 	while (i < textures->how_many_lines - 1)
// 	{
// 		int len_i = ft_strlen(textures->map[i]);
// 		int len_i_plus_1 = ft_strlen(textures->map[i + 1]);
// 		if (textures->map[i][0] != '1')
// 			return 0;
// 		if (textures->map[i][len_i - 1] != '1')
// 			return 0;
// 		if (len_i < len_i_plus_1)
// 		{
// 			if (textures->map[i + 1][len_i - 1] != '1')
// 				return 0;
// 			j = len_i;
// 			while (j < len_i_plus_1)
// 			{
// 				if (textures->map[i + 1][j] != '1')
// 					return 0;
// 				j++;
// 			}
// 		}
// 		else if (len_i > len_i_plus_1)
// 		{
// 			if (textures->map[i + 1][len_i_plus_1 - 1] != '1')
// 				return 0;
// 			j = len_i_plus_1;
// 			while (j < len_i)
// 			{
// 				if (textures->map[i][j] != '1')
// 					return 0;
// 				j++;
// 			}
// 		}
		
// 		i++;
// 	}
// 	// int last_row_len = ft_strlen(textures->map[textures->how_many_lines - 1]);
// 	// if (textures->map[textures->how_many_lines - 1][0] != '1' || 
// 	// 	textures->map[textures->how_many_lines - 1][last_row_len - 1] != '1')
// 	// 	return 0;

// 	return 1;
//}