
#include "cub3d.h"
int flood_fill(char **map, int rows, int cols, int x, int y)
{
    // Boundary check
    if (x < 0 || x >= rows || y < 0 || y >= cols)
        return 1; // Out of bounds, treat as reachable (open)
    if (map[x][y] == '1') // Hit a wall
        return 0; // Wall means we can't go through
    if (map[x][y] == 'F') // Already visited
        return 1; // Treat as already filled (closed)

    // Mark the cell as visited
    map[x][y] = 'F';

    // Recursive calls in all four directions
    int up = flood_fill(map, rows, cols, x - 1, y);
    int down = flood_fill(map, rows, cols, x + 1, y);
    int left = flood_fill(map, rows, cols, x, y - 1);
    int right = flood_fill(map, rows, cols, x, y + 1);

    // Return true if all directions are closed (i.e., no open paths)
    return up && down && left && right; // All must return closed (1)
}




int map_closed(t_textures *textures)
{
    int rows = textures->how_many_lines;
    int cols = ft_strlen(textures->map[0]);

    // Flood fill from all border `0`s
    for (int j = 0; j < cols; j++) {
        if (textures->map[0][j] == '0') // Top border
            flood_fill(textures->map, rows, cols, 0, j);
        if (textures->map[rows - 1][j] == '0') // Bottom border
            flood_fill(textures->map, rows, cols, rows - 1, j);
    }

    for (int i = 0; i < rows; i++) {
        if (textures->map[i][0] == '0') // Left border
            flood_fill(textures->map, rows, cols, i, 0);
        if (textures->map[i][cols - 1] == '0') // Right border
            flood_fill(textures->map, rows, cols, i, cols - 1);
    }

    // After filling, check if any `0`s remain
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (textures->map[i][j] == '0') { // If any `0` remains
                printf("Map is not closed!\n");
                return 0; // Map is not closed
            }
        }
    }

    printf("Map is closed!\n");
    return 1; // Map is closed
}
