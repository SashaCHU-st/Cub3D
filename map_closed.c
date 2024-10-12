
#include "cub3d.h"
// int flood_fill(char **map, int rows, int cols, int x, int y)
// {
//     // Boundary check
//     if (x < 0 || x >= rows || y < 0 || y >= cols)
//         return 1; // Out of bounds, treat as reachable (open)
//     if (map[x][y] == '1') // Hit a wall
//         return 0; // Wall means we can't go through
//     if (map[x][y] == 'F') // Already visited
//         return 1; // Treat as already filled (closed)

//     // Mark the cell as visited
//     map[x][y] = 'F';

//     // Recursive calls in all four directions
//     int up = flood_fill(map, rows, cols, x - 1, y);
//     int down = flood_fill(map, rows, cols, x + 1, y);
//     int left = flood_fill(map, rows, cols, x, y - 1);
//     int right = flood_fill(map, rows, cols, x, y + 1);

//     // Return true if all directions are closed (i.e., no open paths)
//     return up && down && left && right; // All must return closed (1)
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
// 		int first = ft_strlen(textures->map[i]);
// 		int next = ft_strlen(textures->map[i + 1]);
// 		if (textures->map[i][0] != '1')
// 			return 0;
// 		if (textures->map[i][first - 1] != '1')
// 			return 0;
// 		if (first < next)
// 		{
// 			if (textures->map[i + 1][first - 1] != '1')
// 				return 0;
// 			j = first;
// 			while (j < next)
// 			{
// 				if (textures->map[i + 1][j] != '1')
// 					return 0;
// 				j++;
// 			}
// 		}
// 		else if (first > next)
// 		{
// 			if (textures->map[i + 1][next - 1] != '1')
// 				return 0;
// 			j = next;
// 			while (j < first)
// 			{
// 				if (textures->map[i][j] != '1')
// 					return 0;
// 				j++;
// 			}
// 		}
		
// 		i++;
// 	}

// 	return 1;
// }


int	map_closed(t_textures *textures)
{
	int i, j, len_current, len_next;
	int last_index = textures->how_many_lines - 1;
	i = 0;
	while (textures->map[0][i])
	{
		if (textures->map[0][i] != '1')
			return 0;
		i++;
	}
	i = 0;
//	printf("textures->map[13] %s\n", textures->map[13]);
	while (textures->map[last_index][i])
	{
		if (textures->map[last_index][i] != '1')
		{
			printf("kuku from the bottom\n");
			return 0;
		}
		i++;
	}
	i = 0;
	while (i < last_index)
	{
		len_current = ft_strlen(textures->map[i]);
		len_next = ft_strlen(textures->map[i + 1]);
		if (textures->map[i][0] != '1' || textures->map[i][len_current - 1] != '1')
		{
			printf("kukuf from sides\n");
			return 0;
		}
		if (len_current < len_next)
		{
			j = len_current;
			while (j < len_next)
			{
				if (textures->map[i + 1][j] != '1')
				{
					printf("kuku from not perfect rect upper side");
					return 0;
				}
				j++;
			}
		}
		if (len_current < len_next) //kogda i < i+1
		{
			j = len_current;
			while (j < len_next)
			{
				if (textures->map[i + 1][j] != '1')
				{
					printf("kuku from upper(i) is shorter then lower line(i+1)\n"); //kogda i < i+1
					return 0;
				}
				j++;
			}
		}
		else if (len_current > len_next) //kogda i > i+1
		{
			j = len_next;	
			while (j < len_current)
			{
				if (textures->map[i][j] != '1')
				{
					printf("kuku from upper(i) is longer then lower line(i+1)\n"); //kogda i > i+1
					return 0;
				}
				j++;
			}
		}
	i++;
	}
	return 1;
}