#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **map;               // 2D array of characters representing the map
    int how_many_lines;       // Number of lines in the map
} t_textures;

// Function to print the filled map
void print_filled_map(t_textures *textures) {
    printf("Filled map:\n");
    for (int i = 0; i < textures->how_many_lines; i++) {
        printf("%s\n", textures->map[i]);
    }
}

// Flood fill function
void flood_fill(t_textures *textures, int x, int y) {
    // Ensure the flood fill only proceeds in valid map regions
    if (x < 0 || x >= textures->how_many_lines || y < 0 || y >= strlen(textures->map[x])) {
        return;
    }

    // Stop if we hit a wall ('1') or an already filled spot ('F')
    if (textures->map[x][y] == '1' || textures->map[x][y] == 'F') {
        return;
    }

    // Mark the current position as filled with 'F'
    textures->map[x][y] = 'F';

    // Recursively fill all four directions
    flood_fill(textures, x + 1, y);  // Down
    flood_fill(textures, x - 1, y);  // Up
    flood_fill(textures, x, y + 1);  // Right
    flood_fill(textures, x, y - 1);  // Left
}

// Function to check if the map is closed
int map_closed(t_textures *textures) {
    // Attempt to flood fill from left and right boundaries
    for (int i = 0; i < textures->how_many_lines; i++) {
        int length = strlen(textures->map[i]) - 1;

        // Check the left boundary for '0'
        if (textures->map[i][0] == '0') {
            printf("Found open '0' at left boundary (%d, 0)\n", i);
            return 1; // Map is not closed
        }

        // Check the right boundary for '0'
        if (textures->map[i][length] == '0') {
            printf("Found open '0' at right boundary (%d, %d)\n", i, length);
            return 1; // Map is not closed
        }
    }

    // Attempt to check top and bottom boundaries
    for (int j = 0; j < strlen(textures->map[0]); j++) {
        // Check the top boundary for '0'
        if (textures->map[0][j] == '0') {
            printf("Found open '0' at top boundary (0, %d)\n", j);
            return 1; // Map is not closed
        }

        // Check the bottom boundary for '0'
        if (textures->map[textures->how_many_lines - 1][j] == '0') {
            printf("Found open '0' at bottom boundary (%d, %d)\n", textures->how_many_lines - 1, j);
            return 1; // Map is not closed
        }
    }

    // Check if any '0' is left inside the map (indicating the map is not closed)
    for (int i = 0; i < textures->how_many_lines; i++) {
        for (int j = 0; j < strlen(textures->map[i]); j++) {
            if (textures->map[i][j] == '0') {
                printf("Map is not closed. Found an open '0' at line %d, column %d.\n", i, j);
                return 1;  // Map is not closed
            }
        }
    }

    // If no '0's were found on the borders or in the interior, the map is closed
    printf("Map is properly closed.\n");
    return 0;
}

// Example usage
int main() {
    // Example initialization
    t_textures textures;
    textures.how_many_lines = 5;
    textures.map = malloc(textures.how_many_lines * sizeof(char *));
    textures.map[0] = strdup("11111");
    textures.map[1] = strdup("10001");
    textures.map[2] = strdup("10001");
    textures.map[3] = strdup("10001");
    textures.map[4] = strdup("11111");

    // Call map closed check
    int result = map_closed(&textures);
    
    // Free allocated memory
    for (int i = 0; i < textures.how_many_lines; i++) {
        free(textures.map[i]);
    }
    free(textures.map);
    
    return result;
}

